/* Copyright (C) 2021 Gleb Bezborodov - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the MIT license.
 *
 * You should have received a copy of the MIT license with
 * this file. If not, please write to: bezborodoff.gleb@gmail.com, or visit : https://github.com/glensand/congenial-disco
 */

/*! \defgroup <function> Function
    @{
    \file
    \brief File contains interface to the function proxy, proxy intended to help to call function with string
*/

#pragma once

#include "consolelib/common/foundation.h"

#include <string_view>

namespace disco  {

    class function;

    /**
     * \brief Interface for helper class. The only one reason of existence of this interface is input parameters format.
     * Proxy have to prepare input sequence to be processed by lambda wrapper. Proxy trim any of the following symbols: ;,() 
     */
    class function_proxy {
    public:
        virtual ~function_proxy() = default;
        function_proxy() = default;

        /**
         * \brief Prepares passed arguments to the given function call, then tries to call function, throws disco::bad_input if given sequence had not been parsed correctly
         * \param func Function object to be called
         * \param arguments Input sequence with arguments to be parsed
         * \return String representation of the return value of the function, return value has to be convertable to string, if internal function returns nothing,
         * the result of operation is empty string
         */
        virtual std::string apply(function* func, std::string_view arguments) const = 0;

        DECLARE_NON_COPYABLE(function_proxy);
        DECLARE_NON_MOVABLE(function_proxy);
    };

}

/*! @} */
