#include "bad_input.h"

namespace disco {

    bad_input::bad_input(const std::string& input)
        : exception("Bad input string {" + input + " }") {

    }
}

