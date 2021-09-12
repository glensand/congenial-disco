#include "executor_test.h"

TEST_F(ExecutorTest, FunctionInsertation)
{
    executor->create_function("call", []{});
    executor->invoke("call");
    EXPECT_ANY_THROW(executor->create_function("call", []{}));
}