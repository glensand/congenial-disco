#include "signature_builder.h"

namespace disco {

    signature_builder signature_builder::create(build_policy policy) noexcept {
        return signature_builder(policy);
    }

    signature_builder& signature_builder::add_return_type(std::string_view return_type) noexcept {
        m_return_type = return_type;
        return *this;
    }

    signature_builder& signature_builder::add_parameters(std::vector<std::string_view>&& parameters) noexcept {
        m_parameter_types = std::move(parameters);
        return *this;
    }

    signature_builder& signature_builder::add_name(std::string_view name) noexcept {
        m_name = name;
        return *this;
    }

    std::string signature_builder::get() {
        std::string signature;
        signature.reserve(compute_result_size());
        signature += m_return_type;
        signature.push_back(' ');
        signature += m_name;
        fill_arguments(signature);
        clear();

        return signature;
    }

    void signature_builder::clear() {
        m_return_type = m_name = "";
        m_parameter_types.clear();
    }

    std::size_t signature_builder::compute_result_size() const noexcept {
        std::size_t parameter_bytes_count = 0u;
        for (auto&& parameter : m_parameter_types)
            parameter_bytes_count += parameter.size() + 2; // size of specified string + 1 byte for ',' and 1 byte for space
        return m_return_type.size() + parameter_bytes_count + m_name.size();
    }

    void signature_builder::fill_arguments(std::string& signature) const {
        if (m_build_policy != build_policy::function)
            return;

        signature.push_back('(');
        if(!m_parameter_types.empty()) {
            for (auto&& name : m_parameter_types) {
                signature += name;
                signature += ", ";
            }
            signature.resize(signature.size() - 2); // delete excessive symbols
        } else {
            signature += "void";
        }
        signature.push_back(')');
    }

    signature_builder::signature_builder(build_policy policy)
        : m_build_policy(policy) {

    }

}
