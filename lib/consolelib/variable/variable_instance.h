/* Copyright (C) 2021 Gleb Bezborodov - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the MIT license.
 *
 * You should have received a copy of the MIT license with
 * this file. If not, please write to: bezborodoff.gleb@gmail.com, or visit : https://github.com/glensand/congenial-disco
 */

#pragma once

#include "consolelib/variable/variable.h"
#include "consolelib/generator/parser.h"
#include "consolelib/generator/generator.h"

namespace disco  {

	template<typename TValue>
	class variable_instance final : public variable {
	public:

		using variable::variable;
		using variable::operator=;

		using callback_t = std::function<void(const TValue&)>;

		virtual ~variable_instance() override = default;

		explicit variable_instance(TValue& var,  callback_t&& callback)
	        : m_variable(var)
	        , m_callback(std::move(callback)){} 

		/**
		* \brief Tries to change variable name to given value. If input sequence could not been parsed correctly, threw disco::bad_input
		* Calls registered function if variable were changed successfully, propagate new value to the callback
		* \param arguments Input sequence containing new value of the variable
		*/
		virtual void apply(std::string_view arguments) override {
			auto&& value = parse<TValue>(arguments);
			m_variable = value;

			if (m_callback)
				m_callback(m_variable);
		}

		/**
		* \brief Provide conversion of the internal variable type to its string representation
		* \return String representation of the variable type
		*/
		virtual std::string_view type() const noexcept override {
			return type_name<TValue>();
		}

	private:
		TValue& m_variable;
		callback_t m_callback;
	};

}
