/* Copyright (C) 2021 Gleb Bezborodov - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the MIT license.
 *
 * You should have received a copy of the MIT license with
 * this file. If not, please write to: bezborodoff.gleb@gmail.com, or visit : https://github.com/glensand/congenial-disco
 */

#pragma once

#include <string_view>
#include <algorithm>
#include <charconv>

#include "consolelib/exception/bad_input.h"

namespace detail {

    constexpr auto EndLine = std::string_view::npos;

    constexpr
    auto is_delimiter = [](const char c) noexcept {
        return std::string_view(" \t\n\f\r\v,();").find_first_of(c) != EndLine;
    };

    inline
    void trim(std::string_view& arguments) {
        while (is_delimiter(arguments.front()))
            arguments = std::string_view(arguments.data() + 1, arguments.size() - 1);
    }

    inline
    std::size_t delimiter_position(std::string_view string) {
        if (string.empty())
            throw disco::bad_input("Empty string");

        auto&& delimiter_it = std::find_if(begin(string), end(string), is_delimiter);
        return delimiter_it == end(string) ? string.size() - 1 : std::size_t(std::distance(begin(string), delimiter_it));
    }

    template<typename T>
    T parse(std::string_view view) {
        T value;
        std::from_chars(view.data(), view.data() + view.size(), value);
        return value;
    }

    template<>
    inline std::string_view parse<std::string_view> (std::string_view view) {
        return view;
    }

    template<>
    inline std::string parse<std::string>(std::string_view view) {
        return std::string(view.data(), view.size());
    }
}

namespace disco  {

    template<typename T>
    T parse(std::string_view& arguments) {
        detail::trim(arguments);
        auto&& distance = detail::delimiter_position(arguments);
        auto&& value = detail::parse<T>(std::string_view(arguments.data(), distance));
        arguments = std::string_view(arguments.data() + distance + 1, arguments.size() - distance);
        return value;
    }

}
