/* Copyright (C) 2021 Gleb Bezborodov - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the MIT license.
 *
 * You should have received a copy of the MIT license with
 * this file. If not, please write to: bezborodoff.gleb@gmail.com, or visit : https://github.com/glensand/hope
 */

#include <iostream>

#include "consolelib/invoker.h"
#include "consolelib/parser.h"

int main() {
    //disco::invoker invoker;
    //invoker.create_function("call", [] { std::cout << "call"; });
    //invoker.create_function("invoke", [] { std::cout << "invoke"; });

    //int test_var;
    //invoker.create_variable("test_var", test_var);

    //invoker.invoke("test_var 1");
    //invoker.invoke("call");

    std::string_view string_to_parse = "name 1.0 8";
    auto&& name = disco::parse<std::string_view>(string_to_parse);
    auto&& d_value = disco::parse<double>(string_to_parse);
    auto&& i_value = disco::parse<int>(string_to_parse);

    std::cout << "[" << name << "][" << d_value << "][" << i_value << "]" << std::endl;

	return 0;
} 