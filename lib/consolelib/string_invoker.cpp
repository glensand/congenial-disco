// ReSharper disable CppClangTidyHicppExceptionBaseclass
#include "string_invoker.h"

#include "consolelib/exception/already_exist.h"
#include "consolelib/exception/not_exist.h"
#include "consolelib/generator/signature_builder.h"
#include "consolelib/function/fuinction_proxy.h"
#include "consolelib/variable/variable_proxy.h"

namespace disco {

    // disable resharper's shitty lightning ()_()
    string_invoker::~string_invoker() {  // NOLINT(modernize-use-equals-default)
        for (auto&& [name, function] : m_functions)
            delete function;

        for (auto&& [name, variable] : m_variables)
            delete variable;

        delete m_function_proxy;
        delete m_variable_proxy;
    }

    string_invoker::string_invoker(function_proxy* f_proxy, variable_proxy* v_proxy, 
        on_new_name_added_callback_t&& callback) // NOLINT(cppcoreguidelines-pro-type-member-init)
        : m_new_name_added_callback(std::move(callback))
        , m_function_proxy(f_proxy)
        , m_variable_proxy(v_proxy) {

    }

    std::string string_invoker::invoke(std::string_view arguments) {
        std::string result;
        auto&& name_view = parse<std::string_view>(arguments);
        auto&& name = std::string(name_view.data(), name_view.data() + name_view.size());
        if (auto&& function_it = m_functions.find(name); function_it != end(m_functions))
            result = m_function_proxy->apply(function_it->second, arguments);
        else if (auto&& var_it = m_variables.find(name); var_it != end(m_variables))
            result = m_variable_proxy->apply(var_it->second, arguments);

        return result;
    }

    std::vector<std::string> string_invoker::signatures() const {
        std::vector<std::string> signature_list;

        // collect information about registered functions
        for(auto&& [name, function] : m_functions) {
            signature_list.emplace_back(
               function_signature(name, function)
            );
        }

        // collect information about registered variables
        for(auto&& [name, variable] : m_variables) {
            signature_list.emplace_back(
               variable_signature(name, variable)
            );
        }
        return signature_list;
    }

    void string_invoker::fire_variable_added(std::string_view name) const {
        if (m_new_name_added_callback)
            m_new_name_added_callback(name);
    }

    void string_invoker::assert_variable_unique(std::string_view name) const {
        if (exist(name))
            throw already_exist(name.data());
    }

    void string_invoker::assert_variable_exist(std::string_view name) const {
        if (!exist(name))
            throw not_exist(name.data());
    }

    bool string_invoker::exist(std::string_view name) const noexcept {
        return exist_in_storage(name, m_functions)
            || exist_in_storage(name, m_variables);
    }

    std::string string_invoker::function_signature(const std::string& name, function* func) {
        return signature_builder::create()
            .add_name(name)
            .add_parameters(func->parameter_types())
            .add_return_type(func->return_type())
            .get();
    }

    std::string string_invoker::variable_signature(const std::string& name, variable* var) {
        return signature_builder::create(signature_builder::build_policy::variable)
            .add_return_type(var->type())
            .add_name(name)
            .get();
    }

    template <typename TStorage>
    bool string_invoker::exist_in_storage(std::string_view name, const TStorage& storage) {
        auto&& it = std::find_if(begin(storage), end(storage), [=](auto&& record) {
            return name == record.first;
        });
        return end(storage) != it;
    }
}
