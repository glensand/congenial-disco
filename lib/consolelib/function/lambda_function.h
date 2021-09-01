/* Copyright (C) 2021 Gleb Bezborodov - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the MIT license.
 *
 * You should have received a copy of the MIT license with
 * this file. If not, please write to: bezborodoff.gleb@gmail.com, or visit : https://github.com/glensand/congenial-disco
 */

#pragma once

#include <functional>
#include "hope/tuple/flat_tuple.h"

#include "consolelib/parser.h"
#include "consolelib/function/function.h"

namespace disco {

	template<typename R, typename... Ts>
	class lambda_function final : public function
	{
		using invoke_args_t = hope::flat_tuple<std::decay_t<Ts>...>;
	public:

		lambda_function(std::function<R(Ts...)>&& func, std::string description)
		    : m_description(std::move(description))
	        , m_function(std::move(func)){ }

		lambda_function(const std::function<R(Ts...)>& func, std::string description)
			: m_description(std::move(description))
			, m_function(func) { }

		using function::function;

		virtual std::string invoke(std::string_view arguments) override {
			std::string result;
			auto&& parsed_arguments = parse_arguments(arguments);
			if constexpr (std::is_same_v<R, void>)
			{
				invoke(parsed_arguments, std::make_index_sequence<sizeof... (Ts)>{});
			}
			else
			{
				auto&& call_result = invoke(parsed_arguments, std::make_index_sequence<sizeof... (Ts)>{});
				if constexpr (std::is_convertible_v<R, std::string>)
                    result = call_result;
				else
					result = std::to_string(call_result);
			}
			return result;
		}

		virtual std::string signature() const override {
			std::string result(typeid(R).name());
			result.push_back('(');
			if constexpr (size(hope::type_list<Ts...>{}) > 0)
			{
				const char* names[] = { typeid(Ts).name()... };
				for (auto name : names)
				{
					result += name;
					result += ", ";
				}
				result.resize(result.size() - 2);
			}
			result.push_back(')');
			return result;
		}

		virtual const std::string& description() const override {
			return m_description;
		}

	private:
		invoke_args_t parse_arguments(std::string_view arguments) const {
			invoke_args_t invoke_args;
			hope::for_each(invoke_args, [&](auto&& argument) {
				using argument_t = std::decay_t<decltype(argument)>;
				argument = parse<argument_t>(arguments);
			});
			return invoke_args;
		}

		template<std::size_t... Is>
		auto invoke(const invoke_args_t& args, std::index_sequence<Is...>) {
			return m_function(args.template get<Is>()...);
		}

		std::string m_description;
		std::function<R(Ts...)> m_function;
	};

}
