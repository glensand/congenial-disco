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

#include "consolelib/invoker.h"
#include "consolelib/storage.h"
#include "consolelib/function/function_factory.h"
#include "consolelib/variable/variable_impl.h"

namespace disco {

	class function_proxy;
	class variable_proxy;

    /**
	 * \brief Implementation of general invoker interface with additional functions to add executor of function or value changer
	 */
	class string_command_executor final : public invoker, public storage {
	public:

		using on_new_name_added_callback_t = std::function<void(std::string_view)>;

	    DECLARE_NON_COPYABLE(string_command_executor);
		DECLARE_NON_MOVABLE(string_command_executor);

		virtual ~string_command_executor() override;
        explicit string_command_executor(function_proxy* f_proxy, variable_proxy* v_proxy,
			on_new_name_added_callback_t&& callback = on_new_name_added_callback_t{ });

		// invoker implementation

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

		// storage implementation

		/**
		* \brief Creates list of descriptions of the registered functions. Description format:
		* [name] : [signature]
		* signature format is : [return_type][(parameter types)]
		* \return List with descriptions of all registered functions
		*/
		virtual std::vector<std::string> signatures() const override;

		// own section

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

			fire_variable_added(funcIt.first->first);
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
				    new variable_impl(variable, std::move(callback)));
			
			fire_variable_added(varIt.first->first);
		}

	private:
		void fire_variable_added(std::string_view name) const;
        void assert_variable_unique(std::string_view name) const;
        void assert_variable_exist(std::string_view name) const;
        bool exist(std::string_view name) const noexcept;

        static std::string function_signature(const std::string& name, function* func);
        static std::string variable_signature(const std::string& name, variable* var);

		template<typename TStorage>
		static bool exist_in_storage(std::string_view name, const TStorage& storage);

		on_new_name_added_callback_t m_new_name_added_callback;
		std::map<std::string, function*> m_functions;
		std::map<std::string, variable*> m_variables;

		function_proxy* m_function_proxy;
		variable_proxy* m_variable_proxy;
	};

}
