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

    /**
	 * \brief Utility class, used to create some sorts of functional object wrappers
	 * Allowed function types are:
	 * - pointer to member function, the object on which the method will be called is also required
	 * - pointer to function or static method
	 * - raw lambda function or functional object (operator() has to be declared)
	 * - std::function<TSignature> objects
	 */
	class function_factory final {
	public:
		function_factory() = delete;
		~function_factory() = delete;

        /**
		 * \brief Creates function object using passed lambda expression or functional object (operator() has to be declared)
		 * \param function object to be used to create function wrapper
		 * \param description Short explanation of reason d'etre of this the registered function
		 * \return pointer to the function wrapper; NOTE: this object has to be manually deallocated 
		 */
		template<typename TFunction> 
		static function* create(TFunction&& function, std::string description = "") {
			using traits_t = hope::function_traits<std::decay_t<TFunction>>; // function has to be decayed, cause native lambda type ([=]{}) has no operators
			auto&& lambda = create_impl(std::forward<TFunction>(function),
				traits_t::arg_types);
			return new lambda_function(std::move(lambda), std::move(description));
		}

        /**
		 * \brief Creates function object using pointer to function or pointer to static method of some class
		 * \param func pointer to function or static method
		 * \param description Short explanation of reason d'etre of this the registered function
		 * \return pointer to the function wrapper; NOTE: this object has to be manually deallocated 
		 */
		template<typename TReturn, typename... Ts>
		static function* create(TReturn(*func)(Ts...), std::string description = "") {
			auto&& lambda = create_impl(func, hope::type_list<Ts...>{});
			return new lambda_function(std::move(lambda), std::move(description));
		}

        /**
		 * \brief Creates function object using pointer to instance of some class and specified method
		 * \param function pointer to method to be called
		 * \param description Short explanation of reason d'etre of this the registered function
		 * \param obj instance of object of specified class
		 * \return pointer to the function wrapper; NOTE: this object has to be manually deallocated 
		 */
		template<typename TFunction, typename TObj>
		static function* create(TObj* obj, TFunction&& function, std::string description = "") {
			using traits_t = hope::function_traits<TFunction>;
			auto&& lambda = create_impl(obj, std::forward<TFunction>(function),
				traits_t::arg_types
			);
			return new lambda_function(std::move(lambda), std::move(description));
		}

        /**
		 * \brief Creates function object using specified std::function instance
		 * \param function functor to be passed to thin wrapper
		 * \param description Short explanation of reason d'etre of this the registered function
		 * \return pointer to the function wrapper; NOTE: this object has to be manually deallocated 
		 */
		template<typename TSignature>
		static function* create(const std::function<TSignature>& function, std::string description = "") {
			return new lambda_function(function, std::move(description));
		}

		/**
	 * \brief Creates function object using specified std::function instance
	 * \param function functor to be passed to thin wrapper
	 * \param description Short explanation of reason d'etre of this the registered function
	 * \return pointer to the function wrapper; NOTE: this object has to be manually deallocated
	 */
		template<typename TSignature>
		static function* create(std::function<TSignature>&& function, std::string description = "") {
			return new lambda_function(std::move(function), std::move(description));
		}

	private:
		template<typename TObj, typename TFunction, typename... Ts>
		static auto create_impl(TObj* obj, TFunction&& function, hope::type_list<Ts...>) {
			return std::function(
				[=](const Ts&... args) { return (*obj.*function)(args...); }
			);
		}

		template<typename TFunction, typename... Ts>
		static auto create_impl(TFunction&& function, hope::type_list<Ts...>) {
			return std::function(
				[=](const Ts&... args) { return function(args...); }
			);
		}
	};

}
