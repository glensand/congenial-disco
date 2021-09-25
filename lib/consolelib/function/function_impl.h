/* Copyright (C) 2021 Gleb Bezborodov - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the MIT license.
 *
 * You should have received a copy of the MIT license with
 * this file. If not, please write to: bezborodoff.gleb@gmail.com, or visit : https://github.com/glensand/congenial-disco
 */

#pragma once

#include <functional>

#include "consolelib/core/for_each.h"
#include "consolelib/generator/parser.h"
#include "consolelib/generator/generator.h"
#include "consolelib/function/function.h"

namespace disco {

    template<typename R, typename... Ts>
    class function_impl final : public function
    {
        using invoke_args_t = std::tuple<std::decay_t<Ts>...>;
    public:

        function_impl(std::function<R(Ts...)>&& func, std::string description)
            : m_description(std::move(description))
            , m_function(std::move(func)){ }

        function_impl(const std::function<R(Ts...)>& func, std::string description)
            : m_description(std::move(description))
            , m_function(func) { }

        using function::function;

        // function implementation

        /**
        * \brief Tries to invoke internal function with given arguments, throws disco::bad_input if given sequence had not been parsed correctly
        * \param arguments Input sequence with arguments to be parsed
        * \return String representation of the return value of the function, return value has to be convertable to string, if internal function returns nothing,
        * the result of operation is empty string
        */
        virtual std::string invoke(std::string_view arguments) override {
            std::string result;
            auto&& parsed_arguments = parse_arguments(arguments);
            if constexpr (std::is_same_v<R, void>) {
                invoke(parsed_arguments, std::make_index_sequence<sizeof... (Ts)>{});
            } else {
                auto&& call_result = invoke(parsed_arguments, std::make_index_sequence<sizeof... (Ts)>{});
                if constexpr (std::is_convertible_v<R, std::string>)
                    result = call_result;
                else
                    result = std::to_string(call_result);
            }
            return result;
        }

        /**
        * \brief Converts type of return value to string_view
        * \return String representation of the internal function call result
        */
        virtual std::string_view return_type() const noexcept override {
            return type_name<R>();
        }

        /**
        * \brief Collect information of the types which have to be passed to the internal function
        * \return List of the types of function arguments
        */
        virtual std::vector<std::string_view> parameter_types() const override {
            std::vector<std::string_view> types = { type_name<Ts>()... };
            return types;
        }

        /**
        * \brief Returns function description, the description (reason d'etre of the function)
        * \return String with description
        */
        virtual const std::string& description() const noexcept override {
            return m_description;
        }

    private:
        invoke_args_t parse_arguments(std::string_view arguments) const {
            invoke_args_t invoke_args;
            core::for_each(invoke_args, [&](auto&& argument) {
                using argument_t = std::decay_t<decltype(argument)>;
                argument = parse<argument_t>(arguments);
            });
            return invoke_args;
        }

        template<std::size_t... Is>
        auto invoke(const invoke_args_t& args, std::index_sequence<Is...>) {
            return m_function(std::get<Is>(args)...);
        }

        std::string m_description;
        std::function<R(Ts...)> m_function;
    };

}
