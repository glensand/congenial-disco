/* Copyright (C) 2021 Gleb Bezborodov - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the MIT license.
 *
 * You should have received a copy of the MIT license with
 * this file. If not, please write to: bezborodoff.gleb@gmail.com, or visit : https://github.com/glensand/congenial-disco
 */

#pragma once

#include "consolelib/common/foundation.h"

#include <string_view>
#include <string>
#include <vector>

namespace disco {

    /**
     * \brief Helper class to build signature of functions and variables
     */
    class signature_builder final {
    public:

        enum class build_policy : uint8_t {
            function,
            variable,

            count,
        };

        /**
         * \brief Creates empty builder, this method is intended to be called on very beginning of the signature building 
         * \return Empty builder instance
         */
        static signature_builder create(build_policy policy = build_policy::function) noexcept;

        /**
         * \brief Adds string with return type name, or with name of the variable's type
         * \param return_type String to be added to the signature
         * \return Self
         */
        signature_builder& add_return_type(std::string_view return_type) noexcept;

        /**
         * \brief Add types of the parameters
         * \param parameters List with types, empty list is allowed but for what... ()_()
         * \return Self
         */
        signature_builder& add_parameters(std::vector<std::string_view>&& parameters) noexcept;

        /**
         * \brief Add function or variable name
         * \param name String with name to be added
         * \return Self
         */
        signature_builder& add_name(std::string_view name) noexcept;

        /**
         * \brief Finalization method of the building procedure. After calling this method, each operation on builder object causes UB 
         * \return Final signature
         */
        std::string get();

        ~signature_builder() = default;

        DECLARE_NON_COPYABLE(signature_builder);
        DECLARE_NON_MOVABLE(signature_builder);

    private:

        void clear();
        std::size_t compute_result_size() const noexcept;
        void fill_arguments(std::string& signature) const;

        explicit signature_builder(build_policy policy);
        build_policy m_build_policy;
        std::string_view m_name;
        std::string_view m_return_type;
        std::vector<std::string_view> m_parameter_types;
    };

}
