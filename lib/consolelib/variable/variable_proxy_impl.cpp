#include "variable_proxy_impl.h"

#include "consolelib/variable/variable.h"
#include "consolelib/generator/parser.h"

namespace disco{

    std::string variable_proxy_impl::apply(variable* var, std::string_view arguments) const {
        if (auto&& pos = arguments.find('='); pos != std::string_view::npos) {
            trim(arguments, pos);
            var->set(arguments);
            return {};
        }

        return var->get();
    }

    void variable_proxy_impl::trim(std::string_view& arguments, std::size_t equal_pos) {
        arguments = std::string_view(arguments.data() + equal_pos + 1, arguments.size() - equal_pos - 1);
        while(detail::is_white_space(arguments.front()))
            arguments = std::string_view(arguments.data() + 1, arguments.size() - 1);
    }
}
