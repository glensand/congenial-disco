/* Copyright (C) 2021 Gleb Bezborodov - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the MIT license.
 *
 * You should have received a copy of the MIT license with
 * this file. If not, please write to: bezborodoff.gleb@gmail.com, or visit : https://github.com/glensand/congenial-disco
 */

#pragma once

#include <string>

#include "consolelib/common/foundation.h"

namespace disco {

    /**
     * \brief Interface to string function invoker
     */
    class invoker {
    public:
        virtual ~invoker() = default;
        invoker() = default;

        /**
        * \brief Invokes function or change variable using given string.
        * Function or variable will be found by name. The name is the first parameter in given string.
        * Call parameters might be separated with any known space separator.
        * To change variable call this function using this patter: [variable_name] [new_value].
        * To invoke registered function call it using this patter: [function_name] [arg1 arg2 arg3 ...].
        * If no one handler had not been found, function throws: not_exist exception.
        * On bad input throws bad_input.
         * \throws disco::not_exist
        * \param arguments string to be processed
        */
        virtual std::string invoke(std::string_view arguments) = 0;

        DECLARE_NON_COPYABLE(invoker);
        DECLARE_NON_MOVABLE(invoker);
    };

}
