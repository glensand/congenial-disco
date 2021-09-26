/* Copyright (C) 2021 Gleb Bezborodov - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the MIT license.
 *
 * You should have received a copy of the MIT license with
 * this file. If not, please write to: bezborodoff.gleb@gmail.com, or visit : https://github.com/glensand/congenial-disco
 */

/*! \defgroup <generator> Generator
    @{
    \file
    \brief File contains various generators fot different types.
*/

#pragma once

#include <string_view>

namespace disco  {

    template<typename T>
    std::string_view type_name() noexcept {
        return typeid(T).name();
    }

    template<>
    inline
    std::string_view type_name<int>() noexcept{
        return "int";
    }

    template<>
    inline
    std::string_view type_name<float>() noexcept{
        return "float";
    }

    template<>
    inline
    std::string_view type_name<bool>() noexcept{
        return "bool";
    }

    template<>
    inline
    std::string_view type_name<double>() noexcept{
        return "double";
    }

    template<>
    inline
    std::string_view type_name<std::string>() noexcept {
        return "string";
    }

    template<>
    inline
    std::string_view type_name<std::string_view>() noexcept {
        return "string_view";
    }

}

/*! @} */
