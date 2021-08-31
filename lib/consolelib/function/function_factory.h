/* Copyright (C) 2021 Gleb Bezborodov - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the MIT license.
 *
 * You should have received a copy of the MIT license with
 * this file. If not, please write to: bezborodoff.gleb@gmail.com, or visit : https://github.com/glensand/congenial-disco
 */

#pragma once

#include "hope/function/function_traits.h"
#include "consolelib/function/lambda_function.h"

namespace disco {

	class function_factory final {
	public:
		function_factory() = delete;
		~function_factory() = delete;

        /**
		 * \brief 
		 * \tparam TFunction 
		 * \param function 
		 * \return 
		 */
		template<typename TFunction> 
		static function* create(TFunction&& function) {
			using traits_t = hope::function_traits<std::decay_t<TFunction>>; // function has to be decayed, cause native lambda type ([=]{})
			// has no operators, but decayed lambda has
			auto&& lambda = create_impl<traits_t::result_t>(std::forward<TFunction>(function),
				traits_t::arg_types);
			return new lambda_function(std::move(lambda));
		}

        /**
		 * \brief 
		 * \tparam TFunction 
		 * \tparam TObj 
		 * \param function 
		 * \param obj 
		 * \return 
		 */
		template<typename TFunction, typename TObj>
		static function* create(TObj* obj, TFunction&& function) {
			using traits_t = hope::function_traits<TFunction>;
			auto&& lambda = create_impl<traits_t::result_t>(obj, std::forward<TFunction>(function),
				traits_t::arg_types
			);
			return new lambda_function(std::move(lambda));
		}

        /**
		 * \brief 
		 * \tparam TSignature 
		 * \param obj 
		 * \return 
		 */
		template<typename TSignature>
		static function* create(const std::function<TSignature>& obj) {
			return new lambda_function(obj);
		}

	private:

		template<typename TReturn, typename TObj, typename TFunction, typename... Ts>
		static auto create_impl(TObj* obj, TFunction&& function, hope::type_list<Ts...>) {
			return std::function<TReturn(Ts...)>(
				[=](const Ts&... args) { (*obj.*function)(args...); }
			);
		}

		template<typename TReturn, typename TFunction, typename... Ts>
		static auto create_impl(TFunction&& function, hope::type_list<Ts...>) {
			return std::function<TReturn(Ts...)>(
				[=](const Ts&... args) { function(args...); }
			);
		}
	};

}
