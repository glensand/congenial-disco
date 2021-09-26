/* Copyright (C) 2021 Gleb Bezborodov - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the MIT license.
 *
 * You should have received a copy of the MIT license with
 * this file. If not, please write to: bezborodoff.gleb@gmail.com, or visit : https://github.com/glensand/congenial-disco
 */

/*! \defgroup <core> Core
    @{
*/

#pragma once

namespace disco::core {

    /**
     * Naive implementation of the type_list;
     * @tparam Ts
     */
    template<typename... Ts>
    struct type_list final {};

}

/*! @} */
