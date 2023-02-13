#ifndef COMPARE_HPP
#define COMPARE_HPP

namespace ft
{

template<class InputIt1, class InputIt2>
bool equal(InputIt1 it1, InputIt1 last1, InputIt2 it2)
{
	for (; it1 != last1; ++it1, ++it2)
		if (!(*it1 == *it2))
			return false;
	return true;
}

template <typename InputIt1, typename InputIt2, typename Compare>
bool lexicographical_compare(InputIt1 it1, InputIt1 last1, InputIt2 it2, InputIt2 last2, Compare comp)
{
	for (;it1 != last1 && it2 != last2; ++it1, ++it2) {
		if (comp(*it1, *it2))
			return true;
		if (comp(*it2, *it1))
			return false;
	}
	return it1 == last1 && it2 != last2;
}

template <typename T, typename U>
struct less
{
	bool operator() (const T& x, const U& y) const {
		return x < y;
	}
};

template <typename InputIt1, typename InputIt2>
bool lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2)
{
	return lexicographical_compare(first1, last1, first2, last2,
		less<typename InputIt1::value_type, typename InputIt2::value_type>());
}

} //ft

#endif // COMPARE_HPP