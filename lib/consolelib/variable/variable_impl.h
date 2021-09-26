/* Copyright (C) 2021 Gleb Bezborodov - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the MIT license.
 *
 * You should have received a copy of the MIT license with
 * this file. If not, please write to: bezborodoff.gleb@gmail.com, or visit : https://github.com/glensand/congenial-disco
 */

/*! \defgroup <variable> Variable
    @{
    \file
    \brief File contains declarations of the implementation of the variable polymorphic object.
*/

#pragma once

#include "consolelib/common/foundation.h"
#include "consolelib/variable/variable.h"
#include "consolelib/generator/parser.h"
#include "consolelib/generator/generator.h"

namespace disco  {

    template<typename TValue>
    class variable_impl final : public variable {
        using clear_t = std::decay_t<TValue>;
    public:

        using variable::variable;
        using variable::operator=;

        using callback_t = std::function<void(const TValue&)>;

        virtual ~variable_impl() override = default;

        explicit variable_impl(TValue& var,  callback_t&& callback)
            : m_variable(var)
            , m_callback(std::move(callback)){} 

        /**
        * \brief Tries to change variable name to given value. If input sequence could not been parsed correctly, threw disco::bad_input
        * Calls registered function if variable were changed successfully, propagate new value to the callback
        * \param arguments Input sequence containing new value of the variable
        */
        virtual void set(std::string_view arguments) override {
            auto&& value = parse<TValue>(arguments);
            m_variable = value;

            if (m_callback)
                m_callback(m_variable);
        }

        /**
        * \brief Converts internal value to the string
        * \return Containing value in string form
        */
        virtual std::string get() const override {
            if constexpr (std::is_convertible_v<TValue, std::string>
                    || std::is_same_v<clear_t , std::string_view>)
                return m_variable.data(); // for some reasons is_convertable falls on string_view
            else
                return std::to_string(m_variable);
        }

        /**
        * \brief Provide conversion of the internal variable type to its string representation
        * \return String representation of the variable type
        */
        virtual std::string_view type() const noexcept override {
            return type_name<TValue>();
        }

        DECLARE_NON_COPYABLE(variable_impl);
        DECLARE_NON_MOVABLE(variable_impl);

    private:

        TValue& m_variable;
        callback_t m_callback;
    };

}

/*! @} */
