#include "already_exist.h"

namespace disco {

    already_exist::already_exist(const std::string& variable_name)
        : exception("Variable or function with name {" + variable_name + " } already exists") {

    }

}

