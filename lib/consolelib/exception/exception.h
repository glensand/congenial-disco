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

    class exception {
    public:

        DECLARE_NON_COPYABLE(exception);
        DECLARE_EXPLICIT_DEFAULT_MOVABLE(exception);

        virtual ~exception() = default;
        exception(std::string what) noexcept;

        const std::string& what() const noexcept;

    private:
        std::string m_what;
    };

}
