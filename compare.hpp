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

template<typename T>
struct less
{
	bool operator() (const T& x, const T& y) const {
		return x < y;
	}
};

//#include <functional>
//std::less<int, double> a;

template <typename InputIt1, typename InputIt2>
bool lexicographical_compare(InputIt1 it1, InputIt1 last1, InputIt2 it2, InputIt2 last2)
{
	for (;it1 != last1 && it2 != last2; ++it1, ++it2) {
		if (*it1 < *it2)
			return true;
		if (*it2 < *it1)
			return false;
	}
	return it1 == last1 && it2 != last2;
}

} //ft

#endif // COMPARE_HPP
