#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
#include <stdexcept>
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

	vector() :
		_data(NULL),
		_size(0),
		_capacity(0),
		_alloc(Allocator())
	{}
	explicit vector(const Allocator& alloc) :
		_data(NULL),
		_size(0),
		_capacity(0),
		_alloc(alloc)
	{}
	explicit vector(size_type n) :
		_data(NULL),
		_size(0),
		_capacity(0),
		_alloc(Allocator())
	{
		reserve(n);
		for (size_type i = 0; i < n; i++)
			_alloc.construct(_data + i, value_type());
		_size = n;
	}
	vector(size_type n, const T& value, const Allocator& alloc = Allocator()) :
		_data(NULL),
		_size(0),
		_capacity(0),
		_alloc(alloc)
	{
		reserve(n);
		for (size_type i = 0; i < n; i++)
			_alloc.construct(_data + i, value);
		_size = n;
	}

	template<typename InputIt>
	vector(InputIt first, InputIt last, const Allocator& alloc = Allocator(),
	typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = NULL) :
		_data(NULL),
		_size(0),
		_capacity(0),
		_alloc(alloc)
	{
		size_type n = distance(first, last);
		reserve(n);
		for (size_type i = 0; i < n; ++i)
			_alloc.construct(_data + i, *(first++));
		_size = n;
	}

	vector(const vector<T,Allocator>& other) :
		_data(NULL),
		_size(0),
		_capacity(0),
		_alloc(Allocator())
	{
		reserve(other.size());
		for(size_type i = 0; i < other.size(); ++i)
			_alloc.construct(_data + i, other[i]);
		_size(other.size());
	}

	~vector()
	{
		if (_capacity <= 0)
			return;
		for(size_type i = 0; i < _size; ++i)
			_alloc.destroy(_data + i);
		_alloc.deallocate(_data, _capacity);
	}

	vector& operator=(const vector<T, Allocator>& other)
	{
		if (&other == this)
			return *this;
		clear();
		if (other.size() > _capacity)
			reserve(other.size());
		for(size_type i = 0; i < other.size(); ++i)
			_alloc.construct(_data + i, other[i]);
		_size(other.size());
		return *this;
	}

	void assign(size_type count, const T& value)
	{
		clear();
		if (count > _capacity)
			reserve(count);
		for(size_type i = 0; i < count; ++i)
			_alloc.construct(_data + i, value);
		_size(count);
	}

	template <typename InputIt>
	void assign(InputIt first, InputIt end,
	typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = NULL)
	{
		vector<value_type> cpy(first, end);
		clear();
		if (cpy.size() > _capacity)
			reserve(cpy.size());
		for(size_type i = 0; i < cpy.size(); ++i)
			_alloc.construct(_data + i, cpy[i]);
		_size(cpy.count());
	}

	allocator_type get_allocator() const {
		return _alloc;
	}

	//Element access
	reference at(size_type pos)
	{
		if (pos >= _size)
			throw std::out_of_range("vector::at");
		return _data[pos];
	}
	const_reference at(size_type pos) const
	{
		if (pos >= _size)
			throw std::out_of_range("vector::at");
		return _data[pos];
	}
	reference operator[](size_type pos) { return _data[pos]; }
	const_reference operator[](size_type pos) const { return _data[pos]; }
	reference front() { return *_data; }
	const_reference front() const { return *_data; }
	reference back() { return _data[_size - 1]; }
	const_reference back() const { return _data[_size - 1]; }
	T* data() { return _data; }
	const T* data() const { return _data; }

	//Iterators
	iterator begin() { return _data; }
	iterator end() { return _data + _size; }
	const_iterator begin() const { return _data; }
	const_iterator end() const { return _data + _size; }

	reverse_iterator rbegin() { return reverse_iterator(end()); }
	reverse_iterator rend() { return reverse_iterator(begin()); }
	const_reverse_iterator rbegin() const { return reverse_iterator(end()); }
	const_reverse_iterator rend() const { return reverse_iterator(begin()); }

	//Capacity
	bool empty() const { return _size == 0; }
	size_type size() const { return _size; }
	size_type max_size() const { return allocator_type::max_size(); }
	void reserve(size_type new_cap)
	{
		if (new_cap < _capacity)
			return;
		pointer res = _alloc.allocate(new_cap);

		for (size_type i = 0; i < _size; ++i)
		{
			_alloc.construct(res + i, _data[i]);
			_alloc.destroy(_data + i);
		}
		_data = res;
		_capacity = new_cap;
	}
	size_type capacity() const { return _capacity; }

	//Modifiers
	void clear()
	{
		for (size_type i = 0; i < _size; i++)
			_alloc.destroy(_data + i);
		_size = 0;
	}

	iterator insert(const_iterator pos, const T& value)
	{
		if (_size > _capacity - 1)
			reserve(max(1, _capacity * 2));
		size_type idx = distance(begin(), pos);
		for (size_type i = _size; i > idx; --i)
		{
			_alloc.construct(_data + i, _data + i - 1);
			_alloc.destruct(_data + i - 1);
		}
		_alloc.construct(_data + idx, value);
		++_size;
		return begin() + idx;
	}
	iterator insert(const_iterator pos, size_type count, const T& value)
	{
		if (_size > _capacity - count)
			reserve(max(count, _capacity * 2));
		size_type idx = distance(begin(), pos);
		for (size_type i = _size; i > idx; --i)
		{
			_alloc.construct(_data + i, _data + i - count);
			_alloc.destruct(_data + i - count);
		}
		for (size_type i = idx; i < idx + count; ++i)
			_alloc.construct(_data + i, value);
		_size += count;
		return begin() + idx;
	}

	template<class InputIt>
	iterator insert(const_iterator pos, InputIt first, InputIt last,
	typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = NULL);

	iterator erase(iterator pos)
	{
		size_type idx = distance(begin(), pos);
		_alloc.destruct(_data + idx);
		for (size_type i = idx; i < _size - 1; ++i)
		{
			_alloc.construct(_data + i, _data[i + 1]);
			_alloc.destruct(_data + i + 1);
		}
		--_size;
		return begin() + idx;
	}
	iterator erase(iterator first, iterator last)
	{
		size_type idx = distance(begin(), first);
		size_type count = distance(first, last);
		for(size_type i = idx; i < count + idx; ++i)
			_alloc.destruct(_data + i);
		for (size_type i = idx; i < _size - count; ++i)
		{
			_alloc.construct(_data + i, _data[i + count]);
			_alloc.destruct(_data + i + count);
		}
		return begin() + idx;
	}

	void push_back(const T& value)
	{
		if (_size > _capacity - 1)
			reserve(max(1, _capacity * 2));
		_alloc.construct(_data + _size, value);
		++_size;
	}

	void pop_back()
	{
		--_size;
		_alloc.destroy(_data + _size);
	}

	void resize(size_type count, T value = T())
	{
		clear();
		if (count > _capacity)
			reserve(max(count, _capacity * 2));
		for (size_type i = 0; i < count; i++)
			_alloc.constuct(_data + i, value);
	}

	void swap(vector<T>& other)
	{
		if (&other == this)
			return;
		vector<T> cpy(other);
		other = *this;
		*this = cpy;
	}

private:
	pointer			_data;
	size_type		_size;
	size_type		_capacity;
	allocator_type	_alloc;
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
