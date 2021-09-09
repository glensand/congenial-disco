#include "executor_test.h"

TEST_F(ExecutorTest, IntVariableQuery)
{
    int var = 0;

    executor->create_variable("var", var);
    auto&& res = executor->invoke("var");
    ASSERT_TRUE(res == "0");
}

TEST_F(ExecutorTest, StringVariableQuery)
{
    std::string var = "Value";

    executor->create_variable("var", var);
    auto&& res = executor->invoke("var");
    ASSERT_TRUE(res == "Value");
}

TEST_F(ExecutorTest, BoolVariableQuery)
{
    bool var = true;

    executor->create_variable("var", var);
    auto&& res = executor->invoke("var");
    ASSERT_TRUE(res == "1");
}