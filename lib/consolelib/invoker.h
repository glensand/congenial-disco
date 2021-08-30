/* Copyright (C) 2021 Gleb Bezborodov - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the MIT license.
 *
 * You should have received a copy of the MIT license with
 * this file. If not, please write to: bezborodoff.gleb@gmail.com, or visit : https://github.com/glensand/congenial-disco
 */

#pragma once

#include <string>
#include <unordered_map>
#include <memory>
#include <set>

namespace disco {

	class function;
	class variable;

	class invoker final {
	public:
		~invoker() = default;
		invoker() = default;

		void invoke(const std::string& arguments);

		template<typename T>
		void create_function(std::string_view name, T&& functor);

		invoker(const invoker&) = delete;
		invoker& operator=(const invoker&) = delete;

	private:
		using function_ptr_t = std::unique_ptr<function*>;
		using variable_ptr_t = std::unique_ptr<variable*>;

		std::unordered_map<std::string, function_ptr_t> m_functions;
		std::unordered_map<std::string, variable_ptr_t> m_variables;

		std::set<std::string> m_names;
	};

}
