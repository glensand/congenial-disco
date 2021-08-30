/* Copyright (C) 2021 Gleb Bezborodov - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the MIT license.
 *
 * You should have received a copy of the MIT license with
 * this file. If not, please write to: bezborodoff.gleb@gmail.com, or visit : https://github.com/glensand/congenial-disco
 */

#pragma once

#include "consolelib/function/lambda_function.h"

namespace disco {

	class function_factory final {
	public:
		function_factory() = delete;
		~function_factory() = delete;

		template<typename... Ts>
		static function* create(Ts&&... args) {
			return nullptr;
		}
	};

}
