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
    \brief Implementation of the for_each algorithm, works with standard tuple.
*/

#pragma once

#include <tuple>

namespace disco::core {

    namespace detail {

        /**
         * Implementation of the for_each function, calls given function with each argument of the given tuple
         */
        template<typename TTuple, typename TFunction, std::size_t... Is>
        void for_each(std::index_sequence<Is...>, TTuple&& tuple, TFunction&& func){
            (func(std::get<Is>(tuple)), ...);
        }
    }

    /**
     * Non constant variant of the for_each function
     * @tparam TFunction Type of the function to be called
     * @param tuple The instance of the tuple on which the function will be called
     * @param func The instance of the desired function
     */
    template<typename TFunction, typename... Ts>
    void for_each(std::tuple<Ts...>& tuple, TFunction&& func){
        detail::for_each(std::make_index_sequence<sizeof...(Ts)>(), tuple, func);
    }

    /**
    * Constant variant of the for_each function
    * @tparam TFunction Type of the function to be called
    * @param tuple The instance of the tuple on which the function will be called
    * @param func The instance of the desired function
    */
    template<typename TFunction, typename... Ts>
    void for_each(const std::tuple<Ts...>& tuple, TFunction&& func){
        detail::for_each(std::make_index_sequence<sizeof...(Ts)>(), tuple, func);
    }

}

/*! @} */
