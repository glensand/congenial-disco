#include "exception.h"

namespace disco {

    exception::exception(std::string what) noexcept
        : m_what(std::move(what)) {
           
    }

    const std::string& exception::what() const noexcept {
        return m_what;
    }

}

