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
	template <bool B, typename T = void>
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
} // namespace ft

#endif
