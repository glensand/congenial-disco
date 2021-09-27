# congenial - disco
[![Actions Status](https://github.com/glensand/congenial-disco/workflows/BuildAndTest/badge.svg)](https://github.com/glensand/congenial-disco/actions)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
![GitHub last commit](https://img.shields.io/github/last-commit/glensand/congenial-disco?color=red&style=plastic)
![GitHub stars](https://img.shields.io/github/stars/glensand/congenial-disco?style=social)
![GitHub watchers](https://img.shields.io/github/watchers/glensand/congenial-disco?style=social)
![GitHub followers](https://img.shields.io/github/followers/glensand?style=social)

## Console library
This library gives your the opportunity to call functions by their's registered names, and pass input values as string parameters. You may use it to build the interface of your console application or to build a console system in your game or another GUI project. This library is header only has no external dependencies, it is yeasy to use it as external project of your cmake project.

## Motivating example #0
```c++
#include "consolelib/disco.h"

int main() {
    disco::completer_impl completer;
    disco::string_command_executor invoker(new disco::function_proxy_impl, new disco::variable_proxy_impl,
        [&](auto&& name) {completer.add_name(name); });

    invoker.create_function("call", [] { std::cout << "call" << std::endl; });
    bool debug_mode = false;
    invoker.create_variable("call2", debug_mode);
    
    invoker.invoke("call()"); // call lambda funnction and print call
    invoker.invole("debug_mode = true"); // change debug_mode variable and possible enables application's debug mode
    
    return 0;
}
```

## Motivating example #1
Small sample illustrates how to use console library to build console client to the app.
```c++
#include <iostream>
#include "consolelib/disco.h"
#include "console_client.h" // imagine this header contains console client of the application

int main() {
    disco::completer_impl completer;
    disco::string_command_executor invoker(new disco::function_proxy_impl, new disco::variable_proxy_impl,
            [this](auto&& name) { completer.add_name(name); });
            
    console_client client;
    
    invoker.create_function("register", &client, &console_client::register_client);
    invoker.create_function("send", &client, &console_client::send_message);
    invoker.create_function("update", &console_client::update);
    
    for (;;) {
        std::string query;
        std::getline(std::cin, query);

        try {
            std::cout << invoker.invoke(query) << std::endl;
        }
        catch(const disco::exception& ex) {
            std::cout << "An exception occurred: " << ex.what() << std::endl;
        }
    }
    
    // you may register client with this string: [register "client_name"] or register("client_name")
    // or something like that, but with another delimiters
    return 0;
}
```
In this app you may register client with string: 'register "client_name"' or 'register("client_name")'.
See doccumentation for more details.

## Build
- Clone repository: ``git clone https://github.com/glensand/congenial-disco``
- Generate platform dependent project: ``cmake -S [root_clone/lib] -B [root_clone\install]``
- Go to ``root_clone\install`` and run ``cmake --build . --target install --config [Config]``. The ``Config`` parameter might be Release or Debug

## License
Distributed under the [MIT License](https://github.com/glensand/congenial-disco/blob/main/LICENSE)
