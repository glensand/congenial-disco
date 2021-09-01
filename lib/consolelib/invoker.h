/* Copyright (C) 2021 Gleb Bezborodov - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the MIT license.
 *
 * You should have received a copy of the MIT license with
 * this file. If not, please write to: bezborodoff.gleb@gmail.com, or visit : https://github.com/glensand/congenial-disco
 */

#pragma once

#include <functional>
#include <string_view>
#include <map>
#include <memory>
#include <set>

#include "consolelib/string_invoker.h"
#include "consolelib/function/function_factory.h"
#include "consolelib/variable/variable_instance.h"

namespace disco {

    /**
	 * \brief Implementation of general invoker interface with additional functions to add executor of function or value changer
	 */
	class invoker final : public string_invoker {
	public:

		virtual ~invoker() override;
		invoker() = default;

		/**
		* \brief Invokes function or change variable using given string.
		* Function or variable will be found by name. The name is the first parameter in given string.
		* Call parameters might be separated with any known space separator.
		* To change variable call this function using this pattern: [variable_name] [new_value].
		* To invoke registered function call it using this pattern: [function_name] [arg1 arg2 arg3 ...].
		* If no one handler had not been found, function throws: not_exist exception.
		* On bad input throws bad_input.
		* \param arguments string to be processed
		*/
		virtual std::string invoke(std::string_view arguments) override;

		/**
		* \brief This method should be used such as "auto completion"
		* \param prefix Prefix of the variable or function which has to be completed
		* \return List of functions and variables which names has specified prefix
		*/
		virtual std::vector<std::string_view> complete(std::string_view prefix) override;

        /**
		 * \brief Adds function with specified parameters to the internal functions map
		 * \param name The name of the function which should be use to call registered function
		 * The name has to be unique
		 * \param args Set of variables required for function creation
		 */
		template<typename... Ts>
		void create_function(std::string_view name, Ts&&... args) {
			assert_variable_unique(name);
			auto&& funcIt = m_functions.emplace(name.data(),
				    function_factory::create(std::forward<Ts>(args)...));

			m_names.emplace(funcIt.first->first);
		}

        /**
		 * \brief Adds variable changer to the inner variables map 
		 * \param name The name of the variable, the name has to be unique
		 * \param variable Reference to the variable
		 * \param callback Function will be called on each variable update, new value will be passed to the callie
		 */
		template<typename T, typename TFunction = std::function<void(const T&)>>
		void create_variable(std::string_view name, T& variable, TFunction&& callback = TFunction{ }) {
			assert_variable_unique(name);
			auto&& varIt = m_variables.emplace(name.data(), 
				    new variable_instance(variable, std::move(callback)));

			m_names.emplace(varIt.first->first);
		}

		/**
		* \brief Creates list of descriptions of the registered functions. Description format:
		* [name] : [signature]
		* signature format is : [return_type][(parameter types)]
		* \return List with descriptions of all registered functions
		*/
		virtual std::vector<std::string> signatures() const override {
			std::vector<std::string> description_list;
			description_list.reserve(m_functions.size());
			for(auto&& [name, function] : m_functions) {
				description_list.emplace_back(
					name + " : " + function->signature()
				);
			}
			return description_list;
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
