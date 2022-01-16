#ifndef UTILS_HPP
#define UTILS_HPP

namespace ft
{
	const class nullptr_t{
	public:
		// convertible to any type of null non-member pointer...
		template<class T>
		operator T*() const { return 0; }

		// or any type of null member pointer...
		template<class C, class T>	// any type T for any class type C
		operator T C::*() const { return 0; }

	private:
		void operator&() const;	// Can't take address of nullptr
	} ft_nullptr = {};

	/**
	 * @brief enable_if
	 * At this time, we pass the condition we want to check to part B.
	 * If B is evaluated as true, the type of enable_if::value becomes T.
	 * And if B is false, value does not exist in enable_if.
	 * 
	 * @tparam B is_bool
	 * @tparam T type
	 */
	template <bool Cond, typename T = void>
	struct enable_if {};

	/**
	 * @brief enable_if
	 * 
	 * When B is true, type is defined in the specialized version.
	 * And in other cases, nothing is defined inside it.
	 * 
	 * @tparam T type
	 */
	template <typename T>
	struct enable_if<true, T> { typedef T type; };

	/**
	 * @brief integral_traits
	 * 
	 * @tparam Cond is_integral
	 * @tparam T type
	 */
	template <bool Cond, typename T>
	struct integral_traits {
		static const bool Cond = is_integral;
		typedef T type;
	};

	/**
	 * @brief is_integral_type
	 * 
	 */
	template <typename>
	struct is_integral_type : public integral_traits<false, bool> {};

	template <>
	struct is_integral_type<bool> : public integral_traits<true, bool> {};

	template <>
	struct is_integral_type<char> : public integral_traits<true, char> {};

	template <>
	struct is_integral_type<signed char> : public integral_traits<true, signed char> {};

	template <>
	struct is_integral_type<signed char> : public integral_traits<true, signed char> {};

	template <>
	struct is_integral_type<short int> : public integral_traits<true, short int> {};

	template <>
	struct is_integral_type<int> : public integral_traits<true, int> {};

	template <>
	struct is_integral_type<long int> : public integral_traits<true, long int> {};

	template <>
	struct is_integral_type<long long int> : public integral_traits<true, long long int> {};

	template <>
	struct is_integral_type<unsigned char> : public integral_traits<true, unsigned char> {};

	template <>
	struct is_integral_type<unsigned short int> : public integral_traits<true, unsigned short int> {};

	template <>
	struct is_integral_type<unsigned int> : public integral_traits<true, unsigned int> {};

	template <>
	struct is_integral_type<unsigned long int> : public integral_traits<true, unsigned long int> {};

	template <>
	struct is_integral_type<unsigned long long int> : public integral_traits<true, unsigned long long int> {};

/**
 * @brief is_integral
 * Identifies whether T is an integral type.
 * It inherits is_integral_type<T> and has a different type according to T.
 * 
 * @tparam T type
 */
	template <typename T>
	struct is_integral : public is_integral_type<T> {};

} // namespace ft

#endif
