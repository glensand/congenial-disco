// ReSharper disable CppClangTidyHicppExceptionBaseclass
#include "completer_impl.h"
#include "consolelib/exception/already_exist.h"

namespace disco {

    inline
    std::vector<std::string_view> completer_impl::complete(std::string_view prefix) {
        std::string firstAfterPrefix = prefix.data();
        firstAfterPrefix.back() += 1; // next character
        std::vector<std::string_view> completions;
        if (auto && self_it = m_names.find(prefix); self_it != end(m_names))
            completions.emplace_back(prefix);
        completions.insert(end(completions), m_names.upper_bound(prefix), m_names.lower_bound(firstAfterPrefix));
        return completions;
    }

    inline
    void completer_impl::add_name(std::string_view name) {
        if (auto&& [_, added] = m_names.emplace(name); !added)
            throw already_exist(name.data());
    }
}
