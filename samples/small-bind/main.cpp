/* Copyright (C) 2021 Gleb Bezborodov - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the MIT license.
 *
 * You should have received a copy of the MIT license with
 * this file. If not, please write to: bezborodoff.gleb@gmail.com, or visit : https://github.com/glensand/hope
 */

#include <iostream>

#include "consolelib/invoker.h"

int main() {
    disco::invoker invoker;
    invoker.create_function("call", [] { std::cout << "call"; });
    invoker.create_function("invoke", [] { std::cout << "invoke"; });

    int test_var;
    invoker.create_variable("test_var", test_var);

    invoker.invoke("test_var 1");
    invoker.invoke("call");

	return 0;
} 