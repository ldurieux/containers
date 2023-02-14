#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
#include "iterator.hpp"
#include "utils.hpp"
#include "compare.hpp"

namespace ft
{

template<typename T, typename Allocator = std::allocator<T> >
class vector {
public:
	typedef T									value_type;
	typedef Allocator							allocator_type;
	typedef typename Allocator::reference		reference;
	typedef typename Allocator::const_reference	const_reference;
	typedef typename Allocator::pointer			pointer;
	typedef typename Allocator::const_pointer	const_pointer;
	typedef value_type*							iterator;
	typedef const value_type*					const_iterator;
	typedef ft::reverse_iterator<iterator>		reverse_iterator;
	typedef ft::reverse_iterator<const_iterator>const_reverse_iterator;
	typedef typename Allocator::size_type		size_type;
	typedef typename Allocator::difference_type	difference_type;

	vector();
	explicit vector(const Allocator& alloc);
	explicit vector(size_type n);
	vector(size_type n, const T& value, const Allocator& alloc = Allocator());

	template<typename InputIt>
	vector(InputIt first, InputIt last, const Allocator& alloc = Allocator(),
	typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = NULL);

	vector(const vector<T,Allocator>& other);

	~vector();

	vector& operator=(const vector<T, Allocator>& other);

	void assign(size_type count, const T& value);

	template <typename InputIt>
	void assign(InputIt first, InputIt end,
	typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = NULL);

	allocator_type get_allocator() const;

	//Element access
	reference at(size_type pos);
	const_reference at(size_type pos) const;
	reference operator[](size_type pos);
	const_reference operator[](size_type pos) const;
	reference front();
	const_reference front() const;
	reference back();
	const_reference back() const;
	T* data();
	const T* data() const;

	//Iterators
	iterator begin();
	iterator end();
	const_iterator begin() const;
	const_iterator end() const;

	reverse_iterator rbegin();
	reverse_iterator rend();
	const_reverse_iterator rbegin() const;
	const_reverse_iterator rend() const;

	//Capacity
	bool empty() const;
	size_type size() const;
	size_type max_size() const;
	void reserve(size_type new_cap);
	size_type capacity() const;

	//Modifiers
	void clear();
	iterator insert(const_iterator pos, const T& value);
	iterator insert(const_iterator pos, size_type count, const T& value);

	template<class InputIt>
	iterator insert(const_iterator pos, InputIt first, InputIt last,
	typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = NULL);

	iterator erase(iterator pos);
	iterator erase(iterator first, iterator last);

	void push_back(const T& value);
	void pop_back();

	void resize(size_type count, T value = T());
	void swap(vector<T>& other);
};

template<typename T, typename A>
bool operator==(const vector<T, A>& a, const vector<T, A>& b)
{
	if (a.size() != b.size())
		return false;
	return ft::equal(a.begin(), a.end() - 1, b.begin());
}

template<typename T, typename A>
bool operator!=(const vector<T, A>& a, const vector<T, A>& b)
{
	return !(a == b);
}

template<typename T, typename A>
bool operator<(const vector<T, A>& a, const vector<T, A>& b)
{
	return ft::lexicographical_compare(a.begin(), a.end() - 1, b.begin(), b.end() - 1);
}

template<typename T, typename A>
bool operator>(const vector<T, A>& a, const vector<T, A>& b)
{
	return (b < a);
}

template<typename T, typename A>
bool operator<=(const vector<T, A>& a, const vector<T, A>& b)
{
	return !(a > b);
}

template<typename T, typename A>
bool operator>=(const vector<T, A>& a, const vector<T, A>& b)
{
	return !(a < b);
}

} //ft

#endif // VECTOR_HPP
