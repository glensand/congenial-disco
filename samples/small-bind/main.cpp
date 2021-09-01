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

void just_empty_function() {
    std::cout << "just_empty_function call" << std::endl;
}

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

template<typename R, typename... Ts>
void deduce(R(Ts...))
{
    std::function<R(Ts...)> func(just_empty_function);
}

template<typename TReturn, typename TFunction, typename... Ts>
auto create_impl(TFunction&& function, hope::type_list<Ts...>) {
    return std::function(
        [=](const Ts&... args) { function(args...); }
    );
}

template<typename TFunction>
auto create(TFunction&& function) {
    using traits_t = hope::function_traits<std::decay_t<TFunction>>;
    traits_t trait;
    auto arity = trait.arity;
    traits_t::result_t return_v = "    ";
    return create_impl<traits_t::result_t>(std::forward<TFunction>(function),
        traits_t::arg_types
        );
}

int compute_dummy(int a, int b)
{
    auto result = a + b;
    std::cout << result << std::endl;
    return result;
}

int main() {
    disco::invoker invoker;
    invoker.create_function("empty_function", &just_empty_function);
    invoker.create_function("call", [] { std::cout << "call" << std::endl; });
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

    invoker.invoke("test_var 1");
    invoker.invoke("call");
    invoker.invoke("do_void");
    invoker.invoke("do_string GeorgeSand");
    invoker.invoke("empty_function");
    std::cout << invoker.invoke("compute_dummy 12, 1") << std::endl;
    std::cout << invoker.invoke("invoke_return_value") << std::endl;

	return 0;
} 