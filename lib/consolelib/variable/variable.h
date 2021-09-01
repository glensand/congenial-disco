/* Copyright (C) 2021 Gleb Bezborodov - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the MIT license.
 *
 * You should have received a copy of the MIT license with
 * this file. If not, please write to: bezborodoff.gleb@gmail.com, or visit : https://github.com/glensand/congenial-disco
 */

#pragma once

#include <string_view>
#include "consolelib/common/foundation.h"

namespace disco  {

	class variable {
	public:

		virtual ~variable() = default;
		variable() = default;

        /**
		 * \brief Tries to change variable name to given value. If input sequence could not been parsed correctly, threw disco::bad_input
		 * Calls registered function if variable were changed successfully, propagate new value to the callback 
		 * \param arguments Input sequence containing new value of the variable
		 */
		virtual void apply(std::string_view arguments) = 0;

        /**
		 * \brief Provide conversion of the internal variable type to its string representation
		 * \return String representation of the variable type
		 */
		virtual std::string_view type() const noexcept = 0;

		DECLARE_NON_COPYABLE(variable);
		DECLARE_NON_MOVABLE(variable);
	};

}
