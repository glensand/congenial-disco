/* Copyright (C) 2021 Gleb Bezborodov - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the MIT license.
 *
 * You should have received a copy of the MIT license with
 * this file. If not, please write to: bezborodoff.gleb@gmail.com, or visit : https://github.com/glensand/congenial-disco
 */

#pragma once

#include <string>

namespace disco {

    class exception {
    public:
        virtual ~exception() = default;
        exception(std::string what) noexcept;

        const std::string& what() const noexcept;

    private:
        std::string m_what;
    };

}
