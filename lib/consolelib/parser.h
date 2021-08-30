/* Copyright (C) 2021 Gleb Bezborodov - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the MIT license.
 *
 * You should have received a copy of the MIT license with
 * this file. If not, please write to: bezborodoff.gleb@gmail.com, or visit : https://github.com/glensand/congenial-disco
 */

#pragma once

#include <string_view>

#include "consolelib/exception/bad_input.h"

namespace detail {

    constexpr auto EndLine = std::string_view::npos;

    constexpr
    auto is_white_space = [](const char c) noexcept {
        return std::string_view(" \t\n\f\r\v").find_first_of(c) != EndLine;
    };

}

namespace disco  {

    template<typename T>
    T parse(std::string_view& arguments) {
        return { };
    }

    template<>
    inline std::string_view parse<std::string_view>(std::string_view& arguments) {
        auto&& delimiterIt = std::find_if(begin(arguments), end(arguments), detail::is_white_space);
        if (delimiterIt != std::end(arguments))
            throw bad_input(arguments.data());

    }

}
