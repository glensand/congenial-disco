#include "executor_test.h"

namespace {

    int empty_function_int_changed_value = 0;
    void int_function(int new_value) {
        empty_function_int_changed_value = new_value;
    }

    int int_int_function_val1_changed = 0;
    int int_int_function_val2_changed = 0;
    void int_int_function(int val1, int val2) {
        int_int_function_val1_changed = val1;
        int_int_function_val2_changed = val2;
    }

    class test_class_no_virtual_functions final{
    public:
        void void_function() const {}

        void int_function(int val) {
            int_function_value = val;
        }

        void string_function(const std::string& val) {
            string_function_val = val;
        }

        std::string string_function_val;
        int int_function_value = 0;
    };

}

TEST_F(ExecutorTest, IntFunctionCallWithoutBraces) {
    executor->create_function("call", int_function);

    executor->invoke("call 1");
    ASSERT_TRUE(empty_function_int_changed_value == 1);

    executor->invoke("call 14    ");
    ASSERT_TRUE(empty_function_int_changed_value == 14);

    executor->invoke("call     17");
    ASSERT_TRUE(empty_function_int_changed_value == 17);
}

TEST_F(ExecutorTest, IntFunctionCall2Braces) {
    executor->create_function("call", int_function);

    executor->invoke("call(2)");
    ASSERT_TRUE(empty_function_int_changed_value == 2);

    executor->invoke("call( 3 )");
    ASSERT_TRUE(empty_function_int_changed_value == 3);

    executor->invoke("call(4 )");
    ASSERT_TRUE(empty_function_int_changed_value == 4);

    executor->invoke("call( 5)");
    ASSERT_TRUE(empty_function_int_changed_value == 5);

    executor->invoke("call     (    8    )");
    ASSERT_TRUE(empty_function_int_changed_value == 8);
}

TEST_F(ExecutorTest, IntFunctionCallOpenBrace) {
    executor->create_function("call", int_function);

    executor->invoke("call (2");
    ASSERT_TRUE(empty_function_int_changed_value == 2);

    executor->invoke("call ( 3");
    ASSERT_TRUE(empty_function_int_changed_value == 3);

    executor->invoke("call  (  4   ");
    ASSERT_TRUE(empty_function_int_changed_value == 4);
}

TEST_F(ExecutorTest, IntFunctionCallCloseBrace) {
    executor->create_function("call", int_function);

    executor->invoke("call   6 )");
    ASSERT_TRUE(empty_function_int_changed_value == 6);

    executor->invoke("call    7     )");
    ASSERT_TRUE(empty_function_int_changed_value == 7);

    executor->invoke("call    1345345  )   ");
    ASSERT_TRUE(empty_function_int_changed_value == 1345345);
}

TEST_F(ExecutorTest, IntIntFunction) {
    executor->create_function("call", int_int_function);

    executor->invoke("call 1 1 ");
    ASSERT_TRUE(int_int_function_val1_changed == 1);
    ASSERT_TRUE(int_int_function_val2_changed == 1);

    executor->invoke("call(2, 3)");
    ASSERT_TRUE(int_int_function_val1_changed == 2);
    ASSERT_TRUE(int_int_function_val2_changed == 3);

    executor->invoke("call(11 12)");
    ASSERT_TRUE(int_int_function_val1_changed == 11);
    ASSERT_TRUE(int_int_function_val2_changed == 12);
}

TEST_F(ExecutorTest, StringFunction) {
    std::string string_function_val_changed;
    auto string_function = [&](const std::string& val) {
        string_function_val_changed = val;
    };

    executor->create_function("call", string_function);

    executor->invoke("call new_value");
    const auto res_equal1 = string_function_val_changed == "new_value";
    ASSERT_TRUE(res_equal1);

    executor->invoke("call(new_value3)");
    const auto res_equal2 = string_function_val_changed == "new_value3";
    ASSERT_TRUE(res_equal2);

    executor->invoke("call new_value2;;");
    const auto res_equal3 = string_function_val_changed == "new_value2";
    ASSERT_TRUE(res_equal3);
}
