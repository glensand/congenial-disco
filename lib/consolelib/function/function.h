/* Copyright (C) 2021 Gleb Bezborodov - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the MIT license.
 *
 * You should have received a copy of the MIT license with
 * this file. If not, please write to: bezborodoff.gleb@gmail.com, or visit : https://github.com/glensand/congenial-disco
 */

#pragma once

#include <string_view>

namespace disco  {

	class function {
	public:
		virtual ~function() = default;
		function() = default;

		virtual std::string invoke(std::string_view arguments) = 0;

		function(const function&) = delete;
		function& operator=(const function&) = delete;
	};

}
