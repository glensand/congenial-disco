/* Copyright (C) 2021 Gleb Bezborodov - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the MIT license.
 *
 * You should have received a copy of the MIT license with
 * this file. If not, please write to: bezborodoff.gleb@gmail.com, or visit : https://github.com/glensand/congenial-disco
 */

#pragma once

#include <set>

#include "consolelib/completer.h"

namespace disco {

	/**
	 * \brief Represent interface to word auto completer
	 */
	class name_completer final : completer {
	public:
		virtual ~name_completer() override = default;
		name_completer() = default;

		/**
		 * \brief This method should be used such as "auto completion"
		 * \param prefix Prefix of the variable or function which has to be completed
		 * \return List of functions and variables which names has specified prefix
		 */
		virtual std::vector<std::string_view> complete(std::string_view prefix) override;

		/**
		 * \brief Adds given name to the internal storage. Throes disco::already_exist exception if name had been added recently
		 * \param name The name to be added to the storage
		 */
		virtual void add_name(std::string_view name) override;

		DECLARE_NON_COPYABLE(name_completer);
		DECLARE_NON_MOVABLE(name_completer);

	private:
		std::set<std::string_view> m_names;
	};

}