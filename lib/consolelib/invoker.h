/* Copyright (C) 2021 Gleb Bezborodov - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the MIT license.
 *
 * You should have received a copy of the MIT license with
 * this file. If not, please write to: bezborodoff.gleb@gmail.com, or visit : https://github.com/glensand/congenial-disco
 */

#pragma once

#include <functional>
#include <string>
#include <string_view>
#include <map>
#include <memory>
#include <set>

#include "consolelib/function/function_factory.h"
#include "consolelib/variable/variable_instance.h"

namespace disco {

	class function;
	class variable;

	class invoker final {
	public:
		~invoker();
		invoker() = default;

		void invoke(std::string_view arguments);

		template<typename... Ts>
		void create_function(std::string_view name, Ts&&... args) {
			assert_variable_unique(name);
			auto&& funcIt = m_functions.emplace(name.data(),
				    function_factory::create(std::forward<Ts>(args)...));

			m_names.emplace(funcIt.first->first);
		}

		template<typename T>
		void create_variable(std::string_view name, T& variable) {
			assert_variable_unique(name);
			auto&& varIt = m_variables.emplace(name.data(), 
				    new variable_instance(variable));

			m_names.emplace(varIt.first->first);
		}

		invoker(const invoker&) = delete;
		invoker& operator=(const invoker&) = delete;

	private:
        void assert_variable_unique(std::string_view name) const;
        void assert_variable_exist(std::string_view name) const;
        bool exist(std::string_view name) const noexcept;

		std::map<std::string, function*> m_functions;
		std::map<std::string, variable*> m_variables;

		std::set<std::string_view> m_names;
	};

}
