#include "vector.hpp"
#include "map.hpp"
#include <iostream>

#define ns ft

template<typename T>
void print_vector(const T& vec)
{
	std::cout << vec.size() << ' ' << vec.capacity() << std::endl;
	std::cout << '[';
	typename T::const_iterator it = vec.begin();
	if (it != vec.end())
		std::cout << *(it++);
	for (; it != vec.end(); ++it)
		std::cout << ',' << *it;
	std::cout << ']' << std::endl;
}

void title(const std::string& text, int lvl = 2)
{
	for (int i = 0; i < lvl; i++)
		std::cout << ' ';
	int sep = 5 - lvl * 2;
	for (int i = 0; i < sep; i++)
		std::cout << '-';
	std::cout << ' ' << text << ' ';
	for (int i = 0; i < sep; i++)
		std::cout << '-';
	std::cout << std::endl;
}

void vector()
{
	title("vector", 1);
	{
		title("empty constructor");
		ns::vector<int> v;
		print_vector(v);
	} {
		title("size constructor");
		ns::vector<int> v(5);
		print_vector(v);
	} {
		title("size with value constructor");
		ns::vector<int> v(5, 42);
		print_vector(v);
	} {
		title("range constructor");
		ns::vector<int> t;
		t.push_back(12);
		t.push_back(24);
		t.push_back(42);
		{
			ns::vector<int> v(t.begin(), t.end());
			print_vector(v);
		} {
			ns::vector<int> v(t.begin() + 2, t.end());
			print_vector(v);
		}
	} {
		title("copy constructor");
		ns::vector<int> t;
		t.push_back(12);
		t.push_back(24);
		t.push_back(42);
		ns::vector<int> v(t);
		print_vector(v);
	} {
		title("assignement operator");
		ns::vector<int> t;
		t.push_back(12);
		t.push_back(24);
		t.push_back(42);
		ns::vector<int> v;
		v = t;
		print_vector(v);
	} {
		title("assign size");
		{
			ns::vector<int> v;
			v.assign(5, 0);
			print_vector(v);
		} {
			ns::vector<int> v;
			v.push_back(12);
			v.assign(5, 0);
			print_vector(v);
		} {
			ns::vector<int> v;
			v.push_back(12);
			v.assign(0, 0);
			print_vector(v);
		}
	} {
		title("assign range");
		ns::vector<int> t;
		t.push_back(12);
		t.push_back(24);
		t.push_back(42);
		{
			ns::vector<int> v;
			v.assign(t.begin(), t.end());
			print_vector(v);
		} {
			ns::vector<int> v;
			v.push_back(12);
			v.assign(t.begin() + 2, t.end());
			print_vector(v);
		}
	} {
		title("get_allocator");
		ns::vector<int> v;
		std::cout << (v.get_allocator() == std::allocator<int>()) << std::endl;
	} {
		title("at");
		ns::vector<int> v(3);
		std::cout << v.at(0) << std::endl;
		try {
			v.at(3);
			std::cout << "Error" << std::endl;
		} catch (...) {
			std::cout << "Ok" << std::endl;
		}
		title("const at");
		const ns::vector<int>& t = v;
		std::cout << t.at(0) << std::endl;
		try {
			t.at(3);
			std::cout << "Error" << std::endl;
		} catch (...) {
			std::cout << "Ok" << std::endl;
		}
	} {
		title("bracket operator");
		ns::vector<int> v(3);
		v[2] = 10;
		std::cout << v[0] << std::endl;
		std::cout << v[2] << std::endl;
		title("const bracket operator");
		const ns::vector<int>& t = v;
		std::cout << t[0] << std::endl;
		std::cout << t[2] << std::endl;
	} {
		title("front");
		ns::vector<int> v(3);
		v[0] = 21;
		std::cout << v.front() << std::endl;
		title("const front");
		const ns::vector<int>& t = v;
		std::cout << t.front() << std::endl;
	} {
		title("back");
		ns::vector<int> v(3);
		v[2] = 21;
		std::cout << v.back() << std::endl;
		title("const back");
		const ns::vector<int>& t = v;
		std::cout << t.back() << std::endl;
	} {
		title("data");
		ns::vector<int> v;
		v.push_back(10);
		std::cout << (v.data() != NULL) << std::endl;
	} {
		title("const data");
		ns::vector<int> v;
		const ns::vector<int>& t = v;
		v.push_back(10);
		std::cout << (t.data() != NULL) << std::endl;
	} {
		title("begin and end");
		ns::vector<int> v;
		std::cout << (v.begin() == v.end()) << std::endl;
		v.push_back(10);
		std::cout << (v.begin() == v.end()) << std::endl;
		std::cout << (v.begin() + 1 == v.end()) << std::endl;
		std::cout << *v.begin() << std::endl;
	} {
		title("const begin and const end");
		ns::vector<int> v;
		const ns::vector<int>& t = v;
		std::cout << (t.begin() == t.end()) << std::endl;
		v.push_back(10);
		std::cout << (t.begin() == t.end()) << std::endl;
		std::cout << (t.begin() + 1 == t.end()) << std::endl;
		std::cout << *t.begin() << std::endl;
	} {
		title("rbegin and rend");
		ns::vector<int> v;
		std::cout << (v.rbegin() == v.rend()) << std::endl;
		v.push_back(10);
		std::cout << (v.rbegin() == v.rend()) << std::endl;
		std::cout << (v.rbegin() + 1 == v.rend()) << std::endl;
		std::cout << *v.rbegin() << std::endl;
	} {
		title("const rbegin and const rend");
		ns::vector<int> v;
		const ns::vector<int>& t = v;
		std::cout << (t.rbegin() == t.rend()) << std::endl;
		v.push_back(10);
		std::cout << (t.rbegin() == t.rend()) << std::endl;
		std::cout << (t.rbegin() + 1 == t.rend()) << std::endl;
		std::cout << *t.rbegin() << std::endl;
	} {
		title("empty");
		ns::vector<int> v;
		std::cout << v.empty() << std::endl;
		v.push_back(10);
		std::cout << v.empty() << std::endl;
	} {
		title("size");
		ns::vector<int> v;
		std::cout << v.size() << std::endl;
		v.push_back(10);
		std::cout << v.size() << std::endl;
	} {
		title("max_size");
		{
			ns::vector<int> v;
			std::cout << v.max_size() << std::endl;
		} {
			ns::vector<long> v;
			std::cout << v.max_size() << std::endl;
		}
	} {
		title("reserve and capacity");
		ns::vector<int> v;
		v.push_back(10);
		v.reserve(10);
		print_vector(v);
		v.push_back(20);
		v.reserve(0);
		print_vector(v);
	} {
		title("clear");
		ns::vector<int> v;
		v.push_back(10);
		v.reserve(10);
		v.clear();
		print_vector(v);
		v.push_back(20);
		v.reserve(0);
		v.clear();
		print_vector(v);
	} {
		title("insert single");
		ns::vector<int> v;
		v.insert(v.begin(), 1);
		v.insert(v.end(), 3);
		v.insert(v.begin() + 1, 2);
		print_vector(v);
	} {
		title("insert multiple");
		ns::vector<int> v;
		v.insert(v.begin(), 2, 1);
		v.insert(v.end(), 3, 3);
		v.insert(v.begin() + 2, 4, 2);
		print_vector(v);
	} {
		title("insert range");
		ns::vector<int> t;
		t.insert(t.end(), 2, 1);
		t.insert(t.end(), 4, 2);
		t.insert(t.end(), 3, 3);

		ns::vector<int> v;
		v.insert(v.begin(), t.begin(), t.begin() + 2);
		v.insert(v.end(), t.end() - 3, t.end());
		v.insert(v.begin() + 2, t.begin() + 2, t.end() - 3);
		v.insert(v.begin() + 3, v.begin(), v.end());
		print_vector(v);

		title("erase single");
		v.erase(v.begin());
		v.erase(v.begin() + 3);
		v.erase(v.end() - 1);
		print_vector(v);

		title("erase range");
		v.erase(v.begin(), v.begin() + 2);
		v.erase(v.begin() + 2, v.begin() + 4);
		v.erase(v.begin() + 5, v.end());
		print_vector(v);
	} {
		title("push back");
		ns::vector<int> v;
		for (int i = 0; i < 10; i++)
			v.push_back(i * 2);
		print_vector(v);
		title("pop back");
		for (int i = 0; i < 5; i++)
			v.pop_back();
		print_vector(v);
	} {
		title("resize");
		ns::vector<int> v;
		v.resize(5, 4);
		print_vector(v);
		v.resize(3, 2);
		print_vector(v);
		v.resize(0, 2);
		print_vector(v);
	} {
		title("swap");
		ns::vector<int> v;
		ns::vector<int> t;
		v.push_back(10);
		t.push_back(12);
		t.push_back(45);
		v.swap(t);
		print_vector(v);
		print_vector(t);
	} {
		title("operator equal");
		ns::vector<int> v;
		ns::vector<int> t;
		v.push_back(10);
		t.push_back(10);
		std::cout << (v == t) << std::endl;
		v.push_back(15);
		t.push_back(20);
		std::cout << (v == t) << std::endl;
		title("operator less");
		std::cout << (v < t) << std::endl;
		t[1] = 15;
		std::cout << (v < t) << std::endl;
	}
}

template<typename T>
void print_map(const T& map)
{
	std::cout << map.size() << std::endl;
	std::cout << '[';
	typename T::const_iterator it = map.begin();
	if (it != map.end())
	{
		std::cout << (*it).first << ':' << (*it).second;
		++it;
	}
	for (; it != map.end(); ++it)
		std::cout << ',' << (*it).first << ':' << (*it).second;
	std::cout << ']' << std::endl;
}

void map()
{
	title("map", 1);
	{
		title("empty constructor");
		ns::map<std::string, int> m;
		print_map(m);
	} {
		title("range constructor");
		ns::vector<ns::pair<const int, int> > v;
		v.push_back(ns::make_pair(0, 0));
		v.push_back(ns::make_pair(-2, 0));
		v.push_back(ns::make_pair(1, 0));
		v.push_back(ns::make_pair(-3, 0));
		v.push_back(ns::make_pair(-1, 0));
		v.push_back(ns::make_pair(2, 0));
		ns::map<int, int> m(v.begin(), v.end());
		print_map(m);

		title("copy constructor");
		ns::map<int, int> n(m);
		print_map(n);

		title("assign operator");
		m.insert(ns::make_pair(3, 0));
		n = m;
		print_map(n);
	} {
		title("get_allocator");
		ns::map<int, int> m;
		std::cout << (m.get_allocator() == std::allocator<ns::pair<const int, int> >()) << std::endl;
	} {
		title("at");
		ns::map<int, int> m;
		m.insert(ns::make_pair(0, 7));
		m.insert(ns::make_pair(1, 8));
		m.insert(ns::make_pair(-1, 9));
		std::cout << m.at(1) << std::endl;
		try { std::cout << m.at(2) << std::endl; }
		catch (...) {
			std::cout << "Ok" << std::endl;
		}

		title("const at");
		const ns::map<int, int> &n = m;;
		std::cout << n.at(1) << std::endl;
		try { std::cout << n.at(2) << std::endl; }
		catch (...) {
			std::cout << "Ok" << std::endl;
		}

		title("bracket operator");
		std::cout << m[1] << std::endl;
		std::cout << m[2] << std::endl;
		print_map(m);

		{
			title("begin and end");
			ns::map<int, int>::iterator it = m.begin();
			for (; it != m.end(); ++it)
				std::cout << (*it).first << std::endl;
		} {
			title("const begin and end");
			ns::map<int, int>::const_iterator it = n.begin();
			for (; it != n.end(); ++it)
				std::cout << (*it).first << std::endl;
		} {
			title("rbegin and rend");
			ns::map<int, int>::reverse_iterator it = m.rbegin();
			for (; it != m.rend(); ++it)
				std::cout << (*it).first << std::endl;
		} {
			title("const rbegin and rend");
			ns::map<int, int>::const_reverse_iterator it = n.rbegin();
			for (; it != n.rend(); ++it)
				std::cout << (*it).first << std::endl;
		}
	} {
		title("empty");
		ns::map<int, int> m;
		std::cout << m.empty() << std::endl;
		m.insert(ns::make_pair(1, 1));
		std::cout << m.empty() << std::endl;

		title("size");
		std::cout << m.size() << std::endl;
		m.insert(ns::make_pair(0, 1));
		m.insert(ns::make_pair(-1, 1));
		m.insert(ns::make_pair(-2, 1));
		m.insert(ns::make_pair(2, 1));
		m.insert(ns::make_pair(3, 1));
		m.insert(ns::make_pair(-3, 1));
		std::cout << m.size() << std::endl;

		title("clear");
		m.clear();
		print_map(m);
	} {
		title("insert single");
		ns::map<int, int> m;
		m.insert(ns::make_pair(0, 1));
		print_map(m);
		m.insert(ns::make_pair(1, 1));
		print_map(m);
	} {
		title("insert position");
		ns::map<int, int> m;
		m.insert(ns::make_pair(0, 1));
		print_map(m);
		m.insert(ns::make_pair(1, 1));
		print_map(m);
	} {
		title("insert range");
		ns::vector<ns::pair<const std::string, int> > v;
		v.push_back(ns::make_pair("one", 1));
		v.push_back(ns::make_pair("two", 2));
		v.push_back(ns::make_pair("three", 3));
		v.push_back(ns::make_pair("minus one", -1));
		v.push_back(ns::make_pair("minus two", -2));
		ns::map<std::string, int> m;
		m.insert(v.begin(), v.end());
		print_map(m);

		title("erase key");
		m.erase("one");
		print_map(m);

		title("erase iterator");
		m.erase(m.begin());
		print_map(m);

		title("erase range");
		m.erase(m.begin(), m.end());
		print_map(m);
	} {
		title("swap");
		ns::map<int, int> m;
		ns::map<int, int> n;
		m.insert(ns::make_pair(1, 1));
		m.insert(ns::make_pair(2, 2));
		m.swap(n);
		print_map(m);
		print_map(n);

		title("count");
		std::cout << n.count(1) << std::endl;
		std::cout << n.count(3) << std::endl;

		title("find");
		std::cout << (*n.find(1)).second << std::endl;
		std::cout << (n.find(0) == n.end()) << std::endl;

		title("const find");
		const ns::map<int, int> &o = n;
		std::cout << (*o.find(1)).second << std::endl;
		std::cout << (o.find(0) == o.end()) << std::endl;

		title("lower_bound");
		std::cout << (*n.lower_bound(1)).second << std::endl;
		std::cout << (n.lower_bound(0) == n.end()) << std::endl;

		title("const lower_bound");
		std::cout << (*o.lower_bound(1)).second << std::endl;
		std::cout << (o.lower_bound(0) == o.end()) << std::endl;

		title("upper_bound");
		std::cout << (*n.upper_bound(1)).second << std::endl;
		std::cout << (n.upper_bound(0) == n.end()) << std::endl;

		title("const upper_bound");
		std::cout << (*o.upper_bound(1)).second << std::endl;
		std::cout << (o.upper_bound(0) == o.end()) << std::endl;

		{
			title("equal_range");
			ns::pair<ns::map<int, int>::iterator, ns::map<int, int>::iterator> pair;
			pair = n.equal_range(1);
			std::cout << (pair.first == n.lower_bound(1))
					  << ' ' << (pair.second == n.upper_bound(1)) << std::endl;
			pair = n.equal_range(0);
			std::cout << (pair.first == n.lower_bound(0))
					  << ' ' << (pair.second == n.upper_bound(0)) << std::endl;
		} {
			title("const equal_range");
			ns::pair<ns::map<int, int>::const_iterator, ns::map<int, int>::const_iterator> pair;
			pair = o.equal_range(1);
			std::cout << (pair.first == o.lower_bound(1))
					  << ' ' << (pair.second == o.upper_bound(1)) << std::endl;
			pair = o.equal_range(0);
			std::cout << (pair.first == o.lower_bound(0))
					  << ' ' << (pair.second == o.upper_bound(0)) << std::endl;
		}
	}
}

int main()
{
	vector();
	map();

	return 0;
}
