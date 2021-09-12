#include "executor_test.h"

TEST_F(ExecutorTest, IntVariableQuery)
{
    int var = 0;

    executor->create_variable("var", var);
    auto&& res = executor->invoke("var");
    ASSERT_TRUE(res == "0");
}

TEST_F(ExecutorTest, FloatVariableQuery)
{
    float var = 0.11f;

    executor->create_variable("var", var);
    auto&& res = executor->invoke("var");
    auto res_trimmed = std::string(begin(res), begin(res) + 4); // 0.11
    ASSERT_TRUE(res_trimmed == "0.11");
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

TEST_F(ExecutorTest, IntVariableChange)
{
    int var = 0;

    executor->create_variable("var", var);
    executor->invoke("var = 1;");
    ASSERT_TRUE(var == 1);
}

TEST_F(ExecutorTest, FloatVariableChange)
{
    float var = 0.f;

    executor->create_variable("var", var);
    executor->invoke("var = 1.f;");
    ASSERT_TRUE(var == 1);
}

TEST_F(ExecutorTest, BoolVariableChange)
{
    bool var = false;

    executor->create_variable("var", var);
    executor->invoke("var = True;");
    ASSERT_TRUE(var == true);
}