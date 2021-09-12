#include "executor_test.h"

template<typename TValue>
void test_var_signature(std::string_view expected_signature,
                    disco::string_command_executor* executor){
    auto&& var = TValue{};
    executor->create_variable("var", var);
    auto&& signatures = executor->signatures();
    auto&& var_signature = signatures.front();
    ASSERT_TRUE(var_signature == expected_signature);
}

TEST_F(ExecutorTest, IntVariableSignature)
{
    test_var_signature<int>("int var", executor);
}

TEST_F(ExecutorTest, FloatVariableSignature)
{
    test_var_signature<float>("float var", executor);
}

TEST_F(ExecutorTest, DoubleVariableSignature)
{
    test_var_signature<double>("double var", executor);
}

TEST_F(ExecutorTest, BoolVariableSignature)
{
    test_var_signature<bool>("bool var", executor);
}

TEST_F(ExecutorTest, StringVariableSignature)
{
    test_var_signature<std::string>("string var", executor);
}

TEST_F(ExecutorTest, StringViewVariableSignature)
{
    test_var_signature<std::string_view>("string_view var", executor);
}

TEST_F(ExecutorTest, VoidFunctionSignature)
{

}

TEST_F(ExecutorTest, IntFunctionSignature)
{

}