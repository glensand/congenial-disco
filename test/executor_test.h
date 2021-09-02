/* Copyright (C) 2021 Gleb Bezborodov - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the MIT license.
 *
 * You should have received a copy of the MIT license with
 * this file. If not, please write to: bezborodoff.gleb@gmail.com, or visit : https://github.com/glensand/congenial-disco
 */

#pragma once

#include <gtest/gtest.h>

#include "consolelib/string_command_executor.h"
#include "consolelib/completer_impl.h"
#include "consolelib/function/function_proxy_impl.h"
#include "consolelib/variable/variable_proxy_impl.h"

class ExecutorTest : public ::testing::Test {
public:
	virtual void SetUp() override {
#if defined(_WIN32) || defined(_WIN64)
		_CrtMemCheckpoint(&m_startup);
#endif

		completer_instance = new disco::completer_impl;

		executor = new disco::string_command_executor(
		    new disco::function_proxy_impl,
			new disco::variable_proxy_impl,
			[this](auto&& name) {completer_instance->add_name(name); }
		);
	}

	virtual void TearDown() override {
		delete completer_instance;
		delete executor;

#if defined(_WIN32) || defined(_WIN64)
		_CrtMemState teardown{}, diff{};
		_CrtMemCheckpoint(&teardown);
		ASSERT_EQ(0, _CrtMemDifference(&diff, &m_startup, &teardown)) << "Memory leaks detected";
		(void)teardown;
		(void)diff;
#endif
	}

#if defined(_WIN32) || defined(_WIN64)
	_CrtMemState m_startup{ };
#endif

	disco::completer* completer_instance; 
    disco::string_command_executor* executor;
};
