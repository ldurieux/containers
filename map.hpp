#ifndef MAP_HPP
#define MAP_HPP

#include <iostream>
#include <iomanip>
#include <memory>
#include <stdexcept>
#include "iterator.hpp"
#include "utils.hpp"
#include "compare.hpp"

namespace ft
{

template <class Key, class T, class Compare>
class map_value_compare : ft::binary_function<std::pair<const Key, T>, std::pair<const Key, T>, bool>
{
public:
	map_value_compare(Compare c) : comp(c) {}

	bool operator()(const std::pair<const Key, T>& lhs, const std::pair<const Key, T>& rhs) const {
		return comp(lhs.second, rhs.second);
	}

protected:
	Compare comp;
};

template <typename Key, typename T, typename Compare = ft::less<Key>, typename Allocator = std::allocator<ft::pair<const Key, T> > >
class map
{
private:
	struct Node;

public:
	typedef Allocator								allocator_type;
	typedef typename Allocator::value_type			value_type;
	typedef Compare									key_compare;
	typedef map_value_compare<Key, T, key_compare>	value_compare;
	typedef Key										key_type;
	typedef T										data_type;
	typedef T										mapped_type;
	typedef typename Allocator::pointer				pointer;
	typedef typename Allocator::const_pointer		const_pointer;
	typedef typename Allocator::reference			reference;
	typedef typename Allocator::const_reference		const_reference;
	typedef typename Allocator::size_type			size_type;
	typedef typename Allocator::difference_type		difference_type;

	template<typename DataType>
	class MapIterator
	{
	public:
		typedef DataType							value_type;
		typedef DataType*							pointer;
		typedef ft::bidirectional_iterator_tag		iterator_category;
		typedef typename Allocator::difference_type	difference_type;
		typedef typename Allocator::reference		reference;

		MapIterator() :
			_map(NULL),
			_node(NULL)
		{}
		MapIterator(const ft::map<Key, T, Compare, Allocator>* map, Node* node) :
			_map(map),
			_node(node)
		{}
		MapIterator(const MapIterator& other) :
			_map(other._map),
			_node(other._node)
		{}

		MapIterator& operator=(const MapIterator& other)
		{
			_map = other._map;
			_node = other._node;
			return *this;
		}

		reference operator*() const { return _node->value; }
		pointer operator->() const { return &operator*(); }

		MapIterator& operator++() {
			if (_node)
				_node = _node->nextNode();
			return *this;
		}
		MapIterator operator++(int)
		{
			MapIterator tmp = *this;
			if (_node)
				_node = _node->nextNode();
			return tmp;
		}

		MapIterator& operator--() {
			if (_node)
				_node = _node->prevNode();
			else if (_map)
			{
				_node = _map->_root;
				while (_node && _node->right)
					_node = _node->right;
			}
			return *this;
		}
		MapIterator operator--(int)
		{
			MapIterator tmp = *this;
			if (_node)
				_node = _node->prevNode();
			else if (_map)
			{
				_node = _map->_root;
				while (_node && _node->right)
					_node = _node->right;
			}
			return tmp;
		}

		bool operator==(const MapIterator& other) { return _node == other.node(); }
		bool operator!=(const MapIterator& other) { return _node != other.node(); }

		const Node* node() const { return _node; }

	private:
		const ft::map<Key, T, Compare, Allocator>*	_map;
		Node*										_node;
	};

	typedef MapIterator<ft::pair<const Key, T>* >			iterator;
	typedef MapIterator<const ft::pair<const Key, T>* >		const_iterator;
	typedef ft::reverse_iterator<iterator>					reverse_iterator;
	typedef ft::reverse_iterator<const_iterator>			const_reverse_iterator;

private:
	struct Node
	{
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

		bool isImbalanced() const
		{
			const size_type hLeft = leftHeight();
			const size_type hRight = rightHeight();
			if (hLeft > hRight)
				return (hLeft - hRight) > 1;
			return (hRight - hLeft) > 1;
		}

		void updateHeight()
		{
			const size_type hLeft = leftHeight();
			const size_type hRight = rightHeight();
			height = ft::max(hLeft, hRight) + 1;
		}

		void replaceChild(Node* old, Node* by)
		{
			if (left == old)
				left = by;
			else
				right = by;
		}

		Node* nextNode()
		{
			Node *node = NULL;

			if (right)
			{
				node = right;
				while (node->left)
					node = node->left;
				return node;
			}
			else if (!parent)
				return NULL;
			else if (parent->left == this)
				return parent;
			else
			{
				Node* grand = parent->parent;

				if (!grand)
					return NULL;
				if (grand->right == parent)
					return NULL;
				return grand;
			}
		}

		Node* prevNode()
		{
			Node *node = NULL;

			if (left)
			{
				node = left;
				while (node->right)
					node = node->right;
				return node;
			}
			else if (!parent)
				return NULL;
			else if (parent->right == this)
				return parent;
			else
			{
				Node* grand = parent->parent;

				if (!grand)
					return NULL;
				if (grand->left == parent)
					return NULL;
				return grand;
			}
		}

		size_type leftHeight() const { return (left) ? left->height : 0; }
		size_type rightHeight() const { return (right) ? right->height : 0; }

		Node*								parent;
		Node*								left;
		Node*								right;
		size_type							height;
		ft::pair<const key_type, data_type> value;
	};

public:
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
			insert(*first);
	}
	map(const map& other) :
		_root(NULL),
		_size(0),
		_comp(other._comp),
		_alloc(other._alloc)
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
		return (*it).second;
	}
	const T& at(const key_type& key) const
	{
		const_iterator it = find(key);
		if (it == end())
			throw std::out_of_range("map::at");
		return (*it).second;
	}
	T& operator[](const key_type& key)
	{
		iterator it = find(key);
		if (it == end())
			it = insert(ft::make_pair(key, data_type())).first;
		return (*it).second;
	}

	//iterators
	iterator begin() { return iterator(this, smallest(_root)); }
	const_iterator begin() const { return const_iterator(this, smallest(_root)); }
	iterator end() { return iterator(this, NULL); }
	const_iterator end() const { return const_iterator(this, NULL); }

	reverse_iterator rbegin() { return reverse_iterator(end()); }
	const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
	reverse_iterator rend() { return reverse_iterator(begin()); }
	const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }

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

	ft::pair<iterator,bool> insert(const value_type& value)
	{
		iterator it = find(value.first);
		if (it != end())
			return ft::make_pair(it, false);

		const key_type& key = value.first;
		Node* node = _root;
		while (node)
		{
			if (node->key() == key)
				break;
			if (_comp(key, node->key()))
			{
				if (!node->left)
					break;
				node = node->left;
			}
			else
			{
				if (!node->right)
					break;
				node = node->right;
			}
		}
		Node* child = new Node(value.first, value.second);
		child->height = 1;
		if (!node)
		{
			_root = child;
			_size = 1;
			return ft::make_pair(iterator(this, _root), true);
		}
		child->parent = node;
		if (_comp(key, node->key()))
			node->left = child;
		else
			node->right = child;
		recount(node);
		rebalance(node);
		_size++;
		return ft::make_pair(iterator(this, child), true);
	}
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
			erase((*position).first);
	}
	void erase(iterator first, iterator last)
	{
		map cpy(first, last, _comp, _alloc);

		iterator it = cpy.begin();
		for (; it != cpy.end(); ++it)
			erase((*it).first);
	}
	size_type erase(const key_type& key)
	{
		Node* node = _root;
		while (node)
		{
			if (node->key() == key)
				break;
			if (_comp(key, node->key()))
				node = node->left;
			else
				node = node->right;
		}
		if (!node)
			return 0;

		Node* parent = node->parent;
		if (node->height == 1)
		{
			if (parent)
				parent->replaceChild(node, NULL);
			else
				_root = NULL;
		}
		else if (node->left && node->right)
		{
			Node* newNode = smallest(node);
			Node* newNodeParent = newNode->parent;

			newNodeParent->replaceChild(newNode, NULL);
			if (parent)
				parent->replaceChild(node, newNode);
			newNode->parent = parent;
			newNode->left = node->left;
			newNode->right = node->right;
			if (newNode->left)
				newNode->left->parent = newNode;
			if (newNode->right)
				newNode->right->parent = newNode;
			newNode->height = node->height;
		}
		else
		{
			Node* newNode = node->right;
			if (node->left)
				newNode = node->left;

			newNode->parent = parent;
			if (parent)
				parent->replaceChild(node, newNode);
			else
				_root = newNode;
		}
		if (parent)
		{
			recount(parent->left);
			recount(parent->right);
			rebalance(parent->left);
			rebalance(parent->right);
		}

		_size--;
		delete node;
		return 1;
	}

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
	ft::pair<iterator,iterator> equal_range(const key_type& key) {
		return ft::make_pair(lower_bound(key), upper_bound(key));
	}
	ft::pair<const_iterator,const_iterator> equal_range(const key_type& key) const {
		return ft::make_pair(lower_bound(key), upper_bound(key));
	}

	iterator lower_bound(const key_type& key) {
		return iterator(this, lower(key));
	}
	const_iterator lower_bound(const key_type& key) const {
		return const_iterator(this, lower(key));
	}

	iterator upper_bound(const key_type& key) {
		return iterator(this, higher(key));
	}
	const_iterator upper_bound(const key_type& key) const {
		return const_iterator(this, higher(key));
	}

	//observers
	key_compare key_comp() const { return _comp; }
	value_compare value_comp() const { return value_compare(_comp); }

private:
	Node* smallest(Node* node) const
	{
		if (!node)
			return NULL;
		while (node->left)
			node = node->left;
		return node;
	}
	Node* biggest(Node* node) const
	{
		if (!node)
			return NULL;
		while (node->right)
			node = node->right;
		return node;
	}

	Node* lower(const key_type& key) const
	{
		Node* current = _root;
		Node* res = NULL;

		while (current)
		{
			if (_comp(key, current->key()))
			{
				res = current;
				current = current->left;
			}
			else if (_comp(current->key(), key))
				current = current->right;
			else
				return current;
		}
		return res;
	}
	Node* higher(const key_type& key) const
	{
		Node* current = _root;
		Node* res = NULL;

		while (current)
		{
			if (_comp(key, current->key()))
			{
				res = current;
				current = current->left;
			}
			else
				current = current->right;
		}
		return res;
	}

	void deleteNodeAndChild(Node *node)
	{
		if (node->left)
			deleteNodeAndChild(node->left);
		if (node->right)
			deleteNodeAndChild(node->right);
		delete node;
	}

	void recount(Node* from)
	{
		for (; from; from = from->parent)
			from->updateHeight();
	}

	void rebalance(Node* from)
	{
		Node* tmp;

		for (; from; from = from->parent)
		{
			if (!from->isImbalanced())
				continue;
			if (from->rightHeight() > from->leftHeight())
			{
				tmp = from->right;
				if (tmp->rightHeight() < tmp->leftHeight())
					rotateRight(tmp);
				from = rotateLeft(from);
			}
			else
			{
				tmp = from->left;
				if (tmp->rightHeight() > tmp->leftHeight())
					rotateLeft(tmp);
				from = rotateRight(from);
			}
		}
	}

	Node* rotateLeft(Node* node)
	{
		Node* newNode = node->right;
		Node* tmp = newNode->left;
		Node* parent = node->parent;

		node->right = tmp;
		if (tmp)
			tmp->parent = node;
		newNode->parent = node->parent;
		node->parent = newNode;
		newNode->left = node;

		node->updateHeight();
		newNode->updateHeight();

		if(!parent)
			_root = newNode;
		else
			parent->replaceChild(node, newNode);
		return newNode;
	}

	Node* rotateRight(Node* node)
	{
		Node* newNode = node->left;
		Node* tmp = newNode->right;
		Node* parent = node->parent;

		node->left = tmp;
		if (tmp)
			tmp->parent = node;
		newNode->parent = node->parent;
		node->parent = newNode;
		newNode->right = node;

		node->updateHeight();
		newNode->updateHeight();

		if(!parent)
			_root = newNode;
		else
			parent->replaceChild(node, newNode);
		return newNode;
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
