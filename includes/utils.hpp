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
		// Can't take address of nullptr
		void operator&() const;
	} ft_nullptr = {};
} // namespace ft

#endif
