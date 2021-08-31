/* Copyright (C) 2021 Gleb Bezborodov - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the MIT license.
 *
 * You should have received a copy of the MIT license with
 * this file. If not, please write to: bezborodoff.gleb@gmail.com, or visit : https://github.com/glensand/hope
 */

#include <iostream>

#include "consolelib/invoker.h"

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


template<typename TReturn, typename TObj, typename TFunction, typename... Ts>
auto create_impl(TObj* obj, TFunction&& function, hope::type_list<Ts...>) {
    return std::function<TReturn(Ts...)> (
        [=](const Ts&... args) { (*obj.*function)(args...); }
    );
}

template<typename TObj, typename TFunction>
auto create(TObj* obj, TFunction&& function) {
    using traits_t = hope::function_traits<TFunction>;
    return create_impl<traits_t::result_t>(obj, std::forward<TFunction>(function),
        traits_t::arg_types
    );
}

int main() {
    disco::invoker invoker;
    invoker.create_function("call", [] { std::cout << "call" << std::endl; });
    invoker.create_function("invoke", [] { std::cout << "invoke" << std::endl; });
    std::function func = [] {};

    invoker.create_function("empty", func);

    test_class obj;
    invoker.create_function("do_void", &obj, &test_class::do_void);
    invoker.create_function("do_string", &obj, &test_class::do_string);

    int test_var;
    invoker.create_variable("test_var", test_var);

    invoker.invoke("test_var 1");
    invoker.invoke("call");
    invoker.invoke("do_void");
    invoker.invoke("do_string GeorgeSand");

	return 0;
} 