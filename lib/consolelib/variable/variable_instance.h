/* Copyright (C) 2021 Gleb Bezborodov - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the MIT license.
 *
 * You should have received a copy of the MIT license with
 * this file. If not, please write to: bezborodoff.gleb@gmail.com, or visit : https://github.com/glensand/congenial-disco
 */

#pragma once

#include "consolelib/variable/variable.h"
#include "consolelib/parser.h"

namespace disco  {

	template<typename TValue>
	class variable_instance final : public variable {
	public:

		using callback_t = std::function<void(const TValue&)>;

		virtual ~variable_instance() override = default;
		explicit variable_instance(TValue& var,  callback_t&& callback = callback_t{})
	        : m_variable(var)
	        , m_callback(std::move(callback)){} 

		virtual void apply(std::string_view arguments) override {
			auto&& value = parse<TValue>(arguments);
			m_variable = value;

			if (m_callback)
				m_callback(m_variable);
		}

		variable_instance(const variable_instance&) = delete;
		variable_instance& operator=(const variable_instance&) = delete;

	private:
		TValue& m_variable;
		callback_t m_callback;
	};

}
