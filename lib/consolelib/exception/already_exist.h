/* Copyright (C) 2021 Gleb Bezborodov - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the MIT license.
 *
 * You should have received a copy of the MIT license with
 * this file. If not, please write to: bezborodoff.gleb@gmail.com, or visit : https://github.com/glensand/congenial-disco
 */

#pragma once

#include "consolelib/exception/exception.h"

namespace disco {

    class already_exist final : public exception {
    public:
        already_exist(const std::string& variable_name)
        : exception("Variable or function with name {" + variable_name + " } already exists")
        {}
    };

}
