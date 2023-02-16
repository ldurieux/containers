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

	class value_compare : ft::binary_function<value_type, value_type, bool>
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
	typedef typename Allocator::size_type			size_type;
	typedef typename Allocator::difference_type		difference_type;

	//TODO
	typedef ft::pair<const Key, T>*					iterator;
	typedef const ft::pair<const Key, T>*			const_iterator;
	//----

	typedef ft::reverse_iterator<iterator>			reverse_iterator;
	typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;

	struct Node
	{
	private:

	public:
		Node(const key_type& key, const data_type& data) :
			parent(NULL),
			left(NULL),
			right(NULL),
			height(0),
			value(ft::make_pair(key, data))
		{
		}
		const key_type& key() const { return value.first; }
		data_type& data() { return value.second; }

		Node*								parent;
		Node*								left;
		Node*								right;
		size_type							height;
		ft::pair<const key_type, data_type> value;
	};

	//constructors
	map() :
		_root(NULL),
		_size(0),
		_comp(Compare()),
		_alloc(Allocator())
	{
	}
	explicit map(const key_compare& comp, const allocator_type& alloc = allocator_type()) :
		_root(NULL),
		_size(0),
		_comp(comp),
		_alloc(alloc)
	{
	}
	template <typename InputIt>
	map(InputIt first, InputIt last, const key_compare& comp = key_compare(),
		const allocator_type& alloc = allocator_type(),
	typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = NULL) :
		_root(NULL),
		_size(0),
		_comp(comp),
		_alloc(alloc)
	{
		for (; first != last; ++first)
			insert(*inputIt);
	}
	map(const map& other)
	{
		*this = other;
	}
	map& operator=(const map& other)
	{
		if (this == &other)
			return *this;
		clear();

		_comp = other._comp;
		_alloc = other._alloc;
		for (const_iterator it = other.begin(); it != other.end(); ++it)
			insert(*it);
		return *this;
	}

	~map()
	{
		clear();
	}

	allocator_type get_allocator() const { return _alloc; }

	//element access
	T& at(const key_type& key)
	{
		iterator it = find(key);
		if (it == end())
			throw std::out_of_range("map::at");
		return it->second;
	}
	const T& at(const key_type& key) const
	{
		const_iterator it = find(key);
		if (it == end())
			throw std::out_of_range("map::at");
		return it->second;
	}
	T& operator[](const key_type& key)
	{
		iterator it = find(key);
		if (it == end())
			it = insert(key).second;
		return it->second;
	}

	//iterators
	iterator begin() { iterator(this, smallest()); }
	const_iterator begin() const { const_iterator(this, smallest()); }
	iterator end() { iterator(this, NULL); }
	const_iterator end() const { const_iterator(this, NULL); }

	reverse_iterator rbegin() { reverse_iterator(this, NULL); }
	const_reverse_iterator rbegin() const { const_reverse_iterator(this, NULL); }
	reverse_iterator rend() { reverse_iterator(this, smallest()); }
	const_reverse_iterator rend() const { const_reverse_iterator(this, smallest()); }

	//capacity
	bool empty() const { return _size == 0; }
	size_type size() const { return _size; }
	size_type max_size() const { return _alloc.max_size(); }

	//modifiers
	void clear()
	{
		if (_root)
			deleteNodeAndChild(_root);
		_root = NULL;
		_size = 0;
	}

	ft::pair<iterator,bool> insert(const value_type& value);
	iterator insert(iterator position, const value_type& value)
	{
		(void)position;
		return insert(value).first;
	}
	template <typename InputIt>
	void insert(InputIt first, InputIt last,
	typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = NULL)
	{
		map cpy(first, last, _comp, _alloc);

		iterator it = cpy.begin();
		for (; it != cpy.end(); ++it)
			insert(*it);
	}

	void erase(iterator position)
	{
		if (position != end())
			erase(position->first);
	}
	void erase(iterator first, iterator last)
	{
		map cpy(first, last, _comp, _alloc);

		iterator it = cpy.begin();
		for (; it != cpy.end(); ++it)
			erase(it->first);
	}
	size_type erase(const key_type& key);

	void swap(map& other)
	{
		ft::swap(_root, other._root);
		ft::swap(_size, other._size);
		ft::swap(_comp, other._comp);
		ft::swap(_alloc, other._alloc);
	}

	//lookup
	size_type count(const key_type& key) const { return find(key) != end(); }
	iterator find(const key_type& key)
	{
		Node* node = _root;
		if (!node)
			return NULL;
		while (node)
		{
			if (node->key() == key)
				return iterator(this, node);
			if (_comp(key, node->key()))
				node = node->left;
			else
				node = node->right;
		}
		return iterator(this, NULL);
	}
	const_iterator find(const key_type& key) const
	{
		Node* node = _root;
		if (!node)
			return NULL;
		while (node)
		{
			if (node->key() == key)
				return const_iterator(this, node);
			if (_comp(key, node->key()))
				node = node->left;
			else
				node = node->right;
		}
		return const_iterator(this, NULL);
	}
	ft::pair<iterator,iterator> equal_range(const key_type& key)
	{
		iterator it = find(key);
		if (it == end())
			return ft::make_pair(it, it);
		iterator next = it;
		++next;
		return ft::make_pair(it, next);
	}
	ft::pair<const_iterator,const_iterator> equal_range(const key_type& key) const
	{
		const_iterator it = find(key);
		if (it == end())
			return ft::make_pair(it, it);
		const_iterator next = it;
		++next;
		return ft::make_pair(it, next);
	}
	iterator lower_bound(const key_type& key) { return find(key); }
	const_iterator lower_bound(const key_type& key) const { return find(key); }
	iterator upper_bound(const key_type& key)
	{
		iterator it = find(key);
		return (it == end()) ? it : ++it;
	}
	const_iterator upper_bound(const key_type& key) const
	{
		iterator it = find(key);
		return (it == end()) ? it : ++it;
	}

	//observers
	key_compare key_comp() const { return _comp; }
	value_compare value_comp() const { return value_compare(); }

private:
	Node* smallest()
	{
		Node* node = _root;
		if (!node)
			return NULL;
		while (node->left)
			node = node->left;
		return node;
	}
	Node* biggest()
	{
		Node* node = _root;
		if (!node)
			return NULL;
		while (node->right)
			node = node->right;
		return node;
	}

	void deleteNodeAndChild(Node *node)
	{
		if (node->left)
			deleteNodeAndChild(node->left);
		if (node->right)
			deleteNodeAndChild(node->right);
		delete node;
	}

private:
	Node*			_root;
	size_type		_size;
	key_compare		_comp;
	allocator_type	_alloc;
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
