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
#include <array>
#include <algorithm>

#include "consolelib/exception/bad_input.h"

namespace detail {

    constexpr auto EndLine = std::string_view::npos;

    constexpr
    auto is_delimiter = [](const char c) noexcept {
        return std::string_view(" \t\n\f\r\v,();").find_first_of(c) != EndLine;
    };

    constexpr
    auto is_string_delimiter = [](const char c) noexcept {
        return std::string_view("\"").find_first_of(c) != EndLine;
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
        return std::size_t(std::distance(begin(string), delimiter_it));
    }

    template<typename T>
    T parse(std::string_view view) {
        T value;
#if defined _MSC_VER
        if (auto && [ptr, ec] = std::from_chars((const char*)view.data(), (const char*)view.data() + view.size(), value); ec != std::errc())
            throw disco::bad_input(view.data());
#else
        if constexpr(std::is_same_v<int, T>)
        {
            if (auto && [ptr, ec] = std::from_chars((const char*)view.data(), (const char*)view.data() + view.size(), value); ec != std::errc())
                throw disco::bad_input(view.data());
        }
        else
        {
            value = (T)atof(view.data());
        }
#endif
        return value;
    }

    template<>
    inline std::string_view parse<std::string_view>(std::string_view view) {
        return view;
    }

    template<>
    inline std::string parse<std::string>(std::string_view view) {
        return std::string(view.data(), view.size());
    }

    template<>
    inline bool parse<bool>(std::string_view view) {
        std::array<char, 10> lower_case; // assumed 10 chars is enough
        std::transform(begin(view), end(view), begin(lower_case),
            [](unsigned char c) { return std::tolower(c); }
        );
        auto&& view_lower_case = std::string_view(lower_case.data(), view.size());
        return view_lower_case == "1" || view_lower_case == "true";
    }

    template<typename T> 
    T parse_value(std::string_view& arguments) {
        auto&& distance = delimiter_position(arguments);
        auto&& value = detail::parse<T>(std::string_view(arguments.data(), distance));
        arguments = std::string_view(arguments.data() + distance + 1, arguments.size() - distance);
        return value;
    }

    template<typename T>
    T parse_string(std::string_view& arguments) {
        if (arguments.empty() || arguments.front() != '"')
            throw disco::bad_input("String has to have braces, like this \"You string\"");

        auto&& delimiter_it = std::find_if(begin(arguments) + 1, end(arguments), is_string_delimiter);
        if (delimiter_it == end(arguments))
            throw disco::bad_input("String has to have braces, like this \"You string\"");

        auto&& distance = std::distance(begin(arguments), delimiter_it);
        auto value = T(arguments.data() + 1, distance - 1);
        arguments = std::string_view(arguments.data() + distance + 1, arguments.size() - distance);
        return value;
    }
}

namespace disco  {

    inline
    std::string_view parse_name(std::string_view& arguments) {
        detail::trim(arguments);
        return detail::parse_value<std::string_view>(arguments);
    }

    template<typename T>
    T parse(std::string_view& arguments) {
        detail::trim(arguments);
        if constexpr (!std::is_same_v<std::string, T> && !std::is_same_v<std::string_view, T>) {
            return detail::parse_value<T>(arguments);
        }
        else {
            return detail::parse_string<T>(arguments);
        }
    }

}
