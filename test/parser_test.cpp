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

template<typename TValue>
void test_value_parsing(TValue&& expected, std::string_view expected_in_string) {
    using value_t = std::decay_t<TValue>;
    auto&& arguments = {
                std::string(expected_in_string) + "; ",
                std::string(expected_in_string) + ", ",
                std::string(expected_in_string) + ") ",
        "   " + std::string(expected_in_string) + "(",
        "\t\n " + std::string(expected_in_string),
        "   " + std::string(expected_in_string) + " another one value",
        "   " + std::string(expected_in_string) + " another one value, comma value",
    };
    for(auto&& arg_string : arguments) {
        std::string_view argument_view(arg_string);
        auto&& parsed = disco::parse<value_t>(argument_view);
        ASSERT_TRUE(parsed == expected);
    }
}

TEST(ParserTest, ParseStringView)
{
    auto&& to_parse = std::string_view("\"very long value string with strange symbols.;,\"");
    auto&& result = std::string_view("very long value string with strange symbols.;,");

    test_value_parsing(result, to_parse);
}

TEST(ParserTest, ParseString)
{
    auto&& to_parse = std::string_view("\"very long value string with strange symbols.;,\"");
    auto&& result = std::string("very long value string with strange symbols.;,");

    test_value_parsing(result, to_parse);
}

TEST(ParserTest, ParseInt)
{
    auto&& to_parse = std::string_view("1337");
    auto&& result = int(1337);
    test_value_parsing(result, to_parse);
}

TEST(ParserTest, ParseFloat)
{
    auto&& to_parse = std::string_view("1337.14");
    auto&& result = float(1337.14f);
    test_value_parsing(result, to_parse);
}

TEST(ParserTest, ParseDouble)
{
    auto&& to_parse = std::string_view("1337.14");
    auto&& result = double(1337.14);
    test_value_parsing(result, to_parse);
}

TEST(ParserTest, ParseBoolAsInt)
{
    auto&& to_parse_true = std::string_view("1");
    test_value_parsing(true, to_parse_true);

    auto&& to_parse_false = std::string_view("0");
    test_value_parsing(false, to_parse_false);
}

TEST(ParserTest, ParseBoolAsBoolean)
{
    auto&& to_parse_true_lower = std::string_view("true");
    test_value_parsing(true, to_parse_true_lower);

    auto&& to_parse_true_upper = std::string_view("TRUE");
    test_value_parsing(true, to_parse_true_upper);

    auto&& to_parse_false_lower = std::string_view("false");
    test_value_parsing(false, to_parse_false_lower);

    auto&& to_parse_false_upper = std::string_view("FALSE");
    test_value_parsing(false, to_parse_false_upper);
}