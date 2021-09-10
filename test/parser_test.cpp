#include "gtest/gtest.h"
#include <string_view>

#include "consolelib/generator/parser.h"

TEST(ParserTest, ParseName)
{
    auto&& result_name = std::string_view("value_name");
    auto&& names = { "value_name", " value_name",  "value_name ",
        "    value_name ", "    value_name     ", "value_name  value_imitator" };

    for(auto&& name : names) {
        std::string_view argument(name);
        auto&& parsed_name = disco::parse_name(argument);
        ASSERT_TRUE(result_name == parsed_name);
    }
}

TEST(ParserTest, ParseString)
{
    auto&& to_parse = std::string_view("\"very long value string with strange symbols.;,\"");
    auto&& result = std::string_view("very long value string with strange symbols.;,");

    auto&& names = {
                std::string(to_parse) + " ",
        "   " + std::string(to_parse) + " ",
        "   " + std::string(to_parse),
        "   " + std::string(to_parse) + " another one value",
        "   " + std::string(to_parse) + " another one value, comma value",
    };

    for (auto&& name : names) {
        std::string_view argument(name);
        auto&& parsed_name = disco::parse<std::string_view>(argument);
        ASSERT_TRUE(result == parsed_name);
    }
}

