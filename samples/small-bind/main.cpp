/* Copyright (C) 2021 Gleb Bezborodov - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the MIT license.
 *
 * You should have received a copy of the MIT license with
 * this file. If not, please write to: bezborodoff.gleb@gmail.com, or visit : https://github.com/glensand/hope
 */

#include <iostream>

#include "consolelib/disco.h"

struct test_class final
{
    void do_void()
    {
        std::cout << "Do" << std::endl;
    }

    void do_string(std::string_view name)
    {
        std::cout << name << std::endl;
    }
};

struct Functor final
{
    void operator()() const
    {
        
    }
};

void just_empty_function() {
    std::cout << "just_empty_function call" << std::endl;
}

int compute_dummy(int a, int b)
{
    auto result = a + b;
    std::cout << result << std::endl;
    return result;
}

int main() {
    disco::completer_impl completer;
    disco::string_command_executor invoker(new disco::function_proxy_impl, new disco::variable_proxy_impl,
        [&](auto&& name) {completer.add_name(name); });

    invoker.create_function("empty_function", &just_empty_function);
    invoker.create_function("call", [] { std::cout << "call" << std::endl; });
    invoker.create_function("call2", [] { std::cout << "call2" << std::endl; });
    invoker.create_function("call3", [] { std::cout << "call3" << std::endl; });
    invoker.create_function("invoke", [] { std::cout << "invoke" << std::endl; });
    invoker.create_function("invoke_return_value", [] { return "invoke_return_value"; });
    invoker.create_function("compute_dummy", compute_dummy);
    std::function func = [] {};

    invoker.create_function("empty_lambda", func);

    test_class obj;
    invoker.create_function("do_void", &obj, &test_class::do_void);
    invoker.create_function("do_string", &obj, &test_class::do_string);

    int test_var;
    invoker.create_variable("test_var", test_var);

    invoker.invoke("test_var = 1");
    invoker.invoke("call");
    invoker.invoke("do_void");
    invoker.invoke("do_string GeorgeSand");
    invoker.invoke("empty_function");
    invoker.invoke("compute_dummy 12, 1");
    invoker.invoke("compute_dummy 12 1");
    invoker.invoke("compute_dummy (12, 1)");
    std::cout << invoker.invoke("invoke_return_value") << std::endl;

    auto&& descriptions = invoker.signatures();
    for (auto&& description : descriptions)
        std::cout << description << std::endl;

    auto&& call_completion = completer.complete("call");
    for (auto&& name : call_completion)
        std::cout << name << std::endl;

    return 0;  // NOLINT(clang-diagnostic-misleading-indentation)
} 