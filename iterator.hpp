#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <cstddef>

namespace ft
{

struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag : public input_iterator_tag {};
struct bidirectional_iterator_tag : public forward_iterator_tag {};
struct random_access_iterator_tag : public bidirectional_iterator_tag {};

template <typename Iter>
struct iterator_traits
{
	typedef typename Iter::value_type		value_type;
	typedef typename Iter::difference_type	difference_type;
	typedef typename Iter::pointer			pointer;
	typedef typename Iter::reference		reference;
	typedef typename Iter::iterator_category iterator_category;
};

template <typename T>
struct iterator_traits<T*> {
	typedef T value_type;
	typedef ptrdiff_t difference_type;
	typedef T* pointer;
	typedef T& reference;
	typedef random_access_iterator_tag iterator_category;
};

template <class InputIt>
typename iterator_traits<InputIt>::difference_type distance(InputIt first, InputIt last)
{
	typename iterator_traits<InputIt>::difference_type n = 0;
	for (; first != last; ++first)
		++n;
	return n;
}

#define TRAIT iterator_traits<Iter>

template <typename Iter>
class reverse_iterator
{
public:
	typedef typename TRAIT::value_type		value_type;
	typedef typename TRAIT::difference_type difference_type;
	typedef typename TRAIT::pointer			pointer;
	typedef typename TRAIT::reference		reference;
	typedef typename TRAIT::iterator_category iterator_category;

	reverse_iterator() {}
	explicit reverse_iterator(Iter it) : _base(it) {}

	Iter base() const { return _base; }

	reference operator*() const {
		Iter tmp = _base;
		return *--tmp;
	}
	pointer operator->() const {
		return &operator*();
	}
	reference operator[](difference_type n) const {
		return *(*this + n);
	}

	reverse_iterator operator++() {
		_base--;
		return *this;
	}
	reverse_iterator operator++(int) {
		reverse_iterator tmp = *this;
		_base--;
		return tmp;
	}
	reverse_iterator operator--() {
		_base++;
		return *this;
	}
	reverse_iterator operator--(int) {
		reverse_iterator tmp = *this;
		_base++;
		return tmp;
	}

	reverse_iterator operator+(difference_type n) const {
		return reverse_iterator(_base - n);
	}
	reverse_iterator& operator+=(difference_type n) {
		_base -= n;
		return *this;
	}
	reverse_iterator operator-(difference_type n) const {
		return reverse_iterator(_base + n);
	}
	reverse_iterator& operator-=(difference_type n) {
		_base += n;
		return *this;
	}

private:
	Iter _base;
};

template <typename Iter>
inline bool operator==(const reverse_iterator<Iter>& x,
					   const reverse_iterator<Iter>& y) {
	return x.base() == y.base();
}

template <typename Iter>
inline bool operator!=(const reverse_iterator<Iter>& x,
					   const reverse_iterator<Iter>& y) {
	return x.base() != y.base();
}

template <typename Iter>
inline bool operator<(const reverse_iterator<Iter>& x,
					  const reverse_iterator<Iter>& y) {
	return x.base() > y.base();
}

template <typename Iter>
inline bool operator>(const reverse_iterator<Iter>& x,
					  const reverse_iterator<Iter>& y) {
	return x.base() < y.base();
}

template <typename Iter>
inline bool operator<=(const reverse_iterator<Iter>& x,
					   const reverse_iterator<Iter>& y) {
	return x.base() >= y.base();
}

template <typename Iter>
inline bool operator>=(const reverse_iterator<Iter>& x,
					   const reverse_iterator<Iter>& y) {
	return x.base() <= y.base();
}

} //ft

#endif // ITERATOR_HPP
