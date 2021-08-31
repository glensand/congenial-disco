#include "invoker.h"

#include "consolelib/exception/already_exist.h"
#include "consolelib/exception/not_exist.h"

namespace disco {

    invoker::~invoker() {
        for (auto&& [name, function] : m_functions)
            delete function;

        for (auto&& [name, variable] : m_variables)
            delete variable;
    }

    void invoker::invoke(std::string_view arguments) {
        auto&& name_view = parse<std::string_view>(arguments);
        auto name = std::string(name_view.data(), name_view.data() + name_view.size());
        if(auto&& function_it = m_functions.find(name); function_it != end(m_functions)) {
            auto&& function = function_it->second;
            function->invoke(arguments);
        } else if(auto&& var_it = m_variables.find(name); var_it != end(m_variables)) {
            auto&& variable = var_it->second;
            variable->apply(arguments);
        }
    }

    std::vector<std::string_view> invoker::complete(std::string_view prefix) {
        std::string firstAfterPrefix = prefix.data();
        firstAfterPrefix.back() += 1; // next character
        return { m_names.upper_bound(prefix), m_names.lower_bound(firstAfterPrefix) };
    }

    void invoker::assert_variable_unique(std::string_view name) const {
        if (exist(name))
            throw already_exist(name.data());
    }

    void invoker::assert_variable_exist(std::string_view name) const {
        if (!exist(name))
            throw not_exist(name.data());
    }

    bool invoker::exist(std::string_view name) const noexcept {
        return m_names.find(name) != std::cend(m_names);
    }
}
