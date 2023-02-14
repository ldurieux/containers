#include "vector.hpp"
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

int main()
{
	title("FT", 0);
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
		std::cout << (v.data() != NULL) << std::endl;
		v.push_back(10);
		std::cout << (v.data() != NULL) << std::endl;
	} {
		title("const data");
		ns::vector<int> v;
		const ns::vector<int>& t = v;
		std::cout << (t.data() != NULL) << std::endl;
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
	}

	return 0;
}
