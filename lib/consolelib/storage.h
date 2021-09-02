/* Copyright (C) 2021 Gleb Bezborodov - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the MIT license.
 *
 * You should have received a copy of the MIT license with
 * this file. If not, please write to: bezborodoff.gleb@gmail.com, or visit : https://github.com/glensand/congenial-disco
 */

#pragma once

#include "consolelib/common/foundation.h"

#include <string>
#include <vector>

namespace disco {

    /**
     * \brief Interface for function and variable storage 
     */
    class storage {
    public:
        virtual ~storage() = default;
        storage() = default;

        /**
         * \brief Creates list of descriptions of the registered functions and variables. Description format:
         * [name] : [signature]
         * signature format is : [return_type][(parameter types)]
         * Variable format is: [variable_type] [variable_name]
         * \return List with descriptions of all registered functions
         */
        virtual std::vector<std::string> signatures() const = 0;

        DECLARE_NON_COPYABLE(storage);
        DECLARE_NON_MOVABLE(storage);
    };

}
