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

	class string_invoker {
	public:
		virtual ~string_invoker() = default;
		string_invoker() = default;

		virtual void invoke(std::string_view arguments) = 0;

		virtual std::vector<std::string_view> complete(std::string_view prefix) = 0;
	};

}
