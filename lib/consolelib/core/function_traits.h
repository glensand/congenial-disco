/* Copyright (C) 2021 Gleb Bezborodov - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the MIT license.
 *
 * You should have received a copy of the MIT license with
 * this file. If not, please write to: bezborodoff.gleb@gmail.com, or visit : https://github.com/glensand/congenial-disco
 */

/*! \defgroup <core> Core
    @{
    \file
    \brief Extension point of the stl's type_traits, these structures might be used to extract any function
    or method return type and types of the "in" arguments.
*/

#pragma once

#include "consolelib/core/typelist.h"

namespace disco::core {

    namespace detail{

        template <typename TClass, typename TReturn, typename... Ts>
        struct function_traits {
            using result_t = TReturn; ///! Return type of the desired function
            static constexpr type_list<Ts...> arg_types{}; ///! Types of the function input parameters
            static constexpr auto arity = sizeof...(Ts); ///! Count of the function input parameters
        };

    }

    /**
     * \breaf  Special trait for functors and lambdas, extract all specific information of the given class
     * @tparam T Type of the lambda expression or functional object.
     *
     * Sample of usage:
     * Assumed that TFunction is the type of the lambda expression of class with operator() override.
     * using traits_t = core::function_traits<TFunction>;
     * static constexpr arg_type_list = traits_t::arg_types;
     */
    template <typename T>
    struct function_traits final : function_traits<decltype(&T::operator())> {};

    /**
     * \breaf Traits for constant member function, extracts return type, types of the input parameters,
     * count of the input parameters
     *
     * Usage:
     * using class_trait_t = disco::function_traits<&class::operator>;
     *
     * @tparam TClass Class which owns this member function
     * @tparam TReturn Type of the return values
     * @tparam Ts Types of the input parameters
     */
    template <typename TClass, typename TReturn, typename... Ts>
    struct function_traits<TReturn(TClass::*)(Ts...) const>
            : detail::function_traits<TClass, TReturn, Ts...>{};

    /**
    * \breaf Traits for member function, extracts return type, types of the input parameters,
    * count of the input parameters
    *
    * Usage:
    * using class_trait_t = disco::function_traits<&class::operator>;
    *
    * @tparam TClass Class which owns this member function
    * @tparam TReturn Type of the return values
    * @tparam Ts Types of the input parameters
    */
    template <typename TClass, typename TReturn, typename... Ts>
    struct function_traits<TReturn(TClass::*)(Ts...)>
            : detail::function_traits<TClass, TReturn, Ts...>{};
}

/*! @} */

