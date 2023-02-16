#ifndef MAP_HPP
#define MAP_HPP

#include <memory>
#include <stdexcept>
#include "iterator.hpp"
#include "utils.hpp"
#include "compare.hpp"

namespace ft
{

template <typename Key, typename T, typename Compare = ft::less<Key>, typename Allocator = std::allocator<std::pair<const Key, T> > >
class map
{
public:
	typedef ft::pair<const Key, T>					value_type;
	typedef Compare									key_compare;

	class value_compare
	{
	protected:
		value_compare(Compare c) : comp(c) {}

	public:
		bool operator()(const value_type& lhs, const value_type& rhs) const
		{
			return comp(lhs.first, rhs.first);
		}

	protected:
		Compare comp;
	};

	typedef Key										key_type;
	typedef T										data_type;
	typedef T										mapped_type;
	typedef Allocator								allocator_type;
	typedef typename Allocator::pointer				pointer;
	typedef typename Allocator::const_pointer		const_pointer;
	typedef typename Allocator::reference			reference;
	typedef typename Allocator::const_reference		const_reference;
	typedef size_t									size_type;
	typedef ptrdiff_t								difference_type;

	//TODO
	typedef ft::pair<const Key, T>*					iterator;
	typedef const ft::pair<const Key, T>*			const_iterator;
	//----

	typedef ft::reverse_iterator<iterator>			reverse_iterator;
	typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;

	//constructors
	map();
	explicit map(const key_compare& comp, const allocator_type& alloc = allocator_type());
	template <typename InputIt>
	map(InputIt first, InputIt last, const key_compare& comp = key_compare(),
		const allocator_type& alloc = allocator_type());
	map(const map& other);
	map& operator=(const map& other);

	~map();

	allocator_type get_allocator() const;

	//element access
	T& at(const key_type& key);
	const T& at(const key_type& key) const;
	T& operator[](const key_type& key);

	//iterators
	iterator begin();
	const_iterator begin() const;
	iterator end();
	const_iterator end() const;

	reverse_iterator rbegin();
	const_reverse_iterator rbegin() const;
	reverse_iterator rend();
	const_reverse_iterator rend() const;

	//capacity
	bool empty() const;
	size_type size() const;
	size_type max_size() const;

	//modifiers
	void clear();
	ft::pair<iterator,bool> insert(const value_type& value);
	iterator insert(iterator position, const value_type& value);
	template <typename InputIt>
	void insert(InputIt first, InputIt last);
	void erase(iterator position);
	void erase(iterator first, iterator last);
	size_type erase(const key_type& key);
	void swap(map& other);

	//lookup
	size_type count(const key_type& key) const;
	iterator find(const key_type& key);
	const_iterator find(const key_type& key) const;
	ft::pair<iterator,iterator> equal_range(const key_type& key);
	ft::pair<const_iterator,const_iterator> equal_range(const key_type& key) const;
	iterator lower_bound(const key_type& key);
	const_iterator lower_bound(const key_type& key) const;
	iterator upper_bound(const key_type& key);
	const_iterator upper_bound(const key_type& key) const;

	//observers
	key_compare key_comp() const { return key_compare(); }
	value_compare value_comp() const { return value_compare(); }

};

template< class Key, class T, class Compare, class Alloc >
bool operator==(const map<Key, T, Compare, Alloc>& a, const map<Key, T, Compare, Alloc>& b)
{
	if (a.size() != b.size())
		return false;
	return ft::equal(a.begin(), a.end(), b.begin());
}

template< class Key, class T, class Compare, class Alloc >
bool operator!=(const map<Key, T, Compare, Alloc>& a, const map<Key, T, Compare, Alloc>& b)
{
	return !(a == b);
}

template< class Key, class T, class Compare, class Alloc >
bool operator<(const map<Key, T, Compare, Alloc>& a, const map<Key, T, Compare, Alloc>& b)
{
	return ft::lexicographical_compare(a.begin(), a.end(), b.begin(), b.end());
}

template< class Key, class T, class Compare, class Alloc >
bool operator>(const map<Key, T, Compare, Alloc>& a, const map<Key, T, Compare, Alloc>& b)
{
	return (b < a);
}

template< class Key, class T, class Compare, class Alloc >
bool operator<=(const map<Key, T, Compare, Alloc>& a, const map<Key, T, Compare, Alloc>& b)
{
	return !(a > b);
}

template< class Key, class T, class Compare, class Alloc >
bool operator>=(const map<Key, T, Compare, Alloc>& a, const map<Key, T, Compare, Alloc>& b)
{
	return !(a < b);
}

} //ft

#endif // MAP_HPP
