#include "function_proxy_impl.h"

#include <string>
#include "consolelib/function/function.h"

namespace disco {

    inline
    std::string function_proxy_impl::apply(function* func, std::string_view arguments) const {
        return func->invoke(arguments);
    }

}
