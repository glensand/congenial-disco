/* Copyright (C) 2021 Gleb Bezborodov - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the MIT license.
 *
 * You should have received a copy of the MIT license with
 * this file. If not, please write to: bezborodoff.gleb@gmail.com, or visit : https://github.com/glensand/congenial-disco
 */

#pragma once

#include <string>
#include <vector>

namespace disco {

    /**
	 * \brief Interface to string function invoker
	 */
	class string_invoker {
	public:
		virtual ~string_invoker() = default;
		string_invoker() = default;

        /**
		 * \brief Invokes function or change variable using given string
		 * Function or variable will be found by name. The name is the first parameter in given string;
		 * Call parameters might be separated with any known space separator
		 * To change variable call this function using this pattern: [variable_name] [new_value]
		 * To invoke registered function call it using this pattern: [function_name] [arg1 arg2 arg3 ...]
		 * If no one handler had not been found, function throws: not_exist exception
		 * On bad input throws bad_input
		 * \param arguments string to be processed
		 */
		virtual void invoke(std::string_view arguments) = 0;

        /**
		 * \brief This method should be used such as "auto completion" 
		 * \param prefix Prefix of the variable or function which has to be completed
		 * \return List of functions and variables which names has specified prefix
		 */
		virtual std::vector<std::string_view> complete(std::string_view prefix) = 0;

		string_invoker(const string_invoker&) = delete;
		string_invoker& operator=(const string_invoker&) = delete;
		string_invoker(string_invoker&&) = delete;
		string_invoker& operator=(string_invoker&&) = delete;
	};

}
