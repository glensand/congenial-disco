/* Copyright (C) 2021 Gleb Bezborodov - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the MIT license.
 *
 * You should have received a copy of the MIT license with
 * this file. If not, please write to: bezborodoff.gleb@gmail.com, or visit : https://github.com/glensand/congenial-disco
 */

/*! \defgroup <variable> Variable
    @{
    \file
    \brief Interface of the variable proxy, this interface is intended to make variable value change and variable
    value query easier.
*/

#pragma once

#include <string_view>
#include "consolelib/common/foundation.h"

namespace disco  {

    class variable;

    /**
     * \brief Provides safe operations on variable and input sequence, dispatch desired operation
     */
    class variable_proxy {
    public:

        virtual ~variable_proxy() = default;
        variable_proxy() = default;

        /**
         * \brief Tries to find out whether this operation get or set, trim input sequence and call desired method.
         * \param var Desired variable
         * \param arguments Input sequence, if there is '=' present, the operation is set if there is no '=' the operation is get
         * \return Returns current value of the variable on get and empty string on set
         */
        virtual std::string apply(variable* var, std::string_view arguments) const = 0;

        DECLARE_NON_COPYABLE(variable_proxy);
        DECLARE_NON_MOVABLE(variable_proxy);
    };

}

/*! @} */
