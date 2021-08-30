#include "not_exist.h"

namespace disco {

    not_exist::not_exist(const std::string& variable_name)
        : exception("Variable or function with name {" + variable_name + " } not exists") {

    }
}

