/* Copyright (C) 2021 Gleb Bezborodov - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the MIT license.
 *
 * You should have received a copy of the MIT license with
 * this file. If not, please write to: bezborodoff.gleb@gmail.com, or visit : https://github.com/glensand/congenial-disco
 */

#pragma once

#include "consolelib/common/foundation.h"

#include <string_view>
#include <vector>

namespace disco  {

    /**
	 * \brief General interface to function wrappers, provides easy ways to call function with string parameters. And accessor to
	 * internal function's signature elements (such as return's value type, parameters types)
	 */
	class function {
	public:
		virtual ~function() = default;
		function() = default;

        /**
		 * \brief Tries to invoke internal function with given arguments, throws disco::bad_input if given sequence had not been parsed correctly
		 * \param arguments Input sequence with arguments to be parsed
		 * \return String representation of the return value of the function, return value has to be convertable to string, if internal function returns nothing,
		 * the result of operation is empty string
		 */
		virtual std::string invoke(std::string_view arguments) = 0;

        /**
		 * \brief Converts type of return value to string_view
		 * \return String representation of the internal function call result
		 */
		virtual std::string_view return_type() const noexcept = 0;

        /**
		 * \brief Collect information of the types which have to be passed to the internal function 
		 * \return List of the types of function arguments
		 */
		virtual std::vector<std::string_view> parameter_types() const = 0;

        /**
		 * \brief Returns function description, the description (reason d'etre of the function)
		 * \return String with description
		 */
		virtual const std::string& description() const noexcept = 0;

		DECLARE_NON_COPYABLE(function);
		DECLARE_NON_MOVABLE(function);
	};

}
