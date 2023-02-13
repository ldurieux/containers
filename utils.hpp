#ifndef UTILS_HPP
#define UTILS_HPP

namespace ft
{

namespace internal {

template<typename T>
struct enabled {
	typedef T type;
};
struct not_enabled {};

struct integral {
	static const bool value = true;
};
struct not_integral {
	static const bool value = false;
};

} //internal

template <bool, typename T = void> struct enable_if : public internal::not_enabled {};
template <typename T> struct enable_if<true, T> : public internal::enabled<T> {};

template<typename T> struct is_integral : public internal::not_integral {};
template<> struct is_integral<char> : public internal::integral {};
template<> struct is_integral<unsigned char> : public internal::integral {};
template<> struct is_integral<short> : public internal::integral {};
template<> struct is_integral<unsigned short> : public internal::integral {};
template<> struct is_integral<int> : public internal::integral {};
template<> struct is_integral<unsigned int> : public internal::integral {};
template<> struct is_integral<long> : public internal::integral {};
template<> struct is_integral<unsigned long> : public internal::integral {};
template<> struct is_integral<long long> : public internal::integral {};
template<> struct is_integral<unsigned long long> : public internal::integral {};

#define PAIR template<typename T, typename U>
PAIR
class pair
{
public:
	pair() :
		first(T()),
		second(U())
	{}
	pair(const T& x, const U& y) :
		first(x),
		second(y)
	{}
	template<typename T2, typename U2>
	pair(const pair<T2, U2>& other) :
		first(other.first),
		second(other.second)
	{}
	pair(const pair<T, U>& other) :
		first(other.first),
		second(other.second)
	{}
	~pair() {}

	pair& operator=(const pair& other)
	{
		first = other.first;
		second = other.second;
		return *this;
	}

	T first;
	U second;
};

PAIR bool operator==(const pair<T, U>& lhs, const pair<T, U>& rhs){
	return lhs.first == rhs.first && lhs.second == rhs.second;
}
PAIR bool operator!=(const pair<T, U>& lhs, const pair<T, U>& rhs){
	return !(lhs == rhs);
}
PAIR bool operator<(const pair<T, U>& lhs, const pair<T, U>& rhs){
	if (lhs.first < rhs.first)
		return true;
	if (lhs.first == rhs.first)
		return false;
	return lhs.second < rhs.second;
}
PAIR bool operator>(const pair<T, U>& lhs, const pair<T, U>& rhs){
	return rhs < lhs;
}
PAIR bool operator<=(const pair<T, U>& lhs, const pair<T, U>& rhs){
	return !(lhs > rhs);
}
PAIR bool operator>=(const pair<T, U>& lhs, const pair<T, U>& rhs){
	return !(lhs < rhs);
}

PAIR pair<T, U> make_pair(T x, T y) {
	return pair(x, y);
}

} //ft

#endif // UTILS_HPP
