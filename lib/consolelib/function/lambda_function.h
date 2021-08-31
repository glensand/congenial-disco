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
		using invoke_args_t = hope::flat_tuple<Ts...>;
	public:

		lambda_function(std::function<R(Ts...)>&& func)
		    : m_function(std::move(func)){ }

		lambda_function(const std::function<R(Ts...)>& func)
			: m_function(func) { }

		using function::function;

		virtual void invoke(std::string_view arguments) const override {
			auto&& parsed_arguments = parse_arguments(arguments);
			invoke(parsed_arguments, std::make_index_sequence<sizeof... (Ts)>{});
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
		void invoke(const invoke_args_t& args, std::index_sequence<Is...>) const {
			(void)m_function(args.template get<Is>()...);
		}

		std::function<R(Ts...)> m_function;
	};

}
