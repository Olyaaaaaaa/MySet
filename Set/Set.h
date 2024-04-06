#pragma once
#include <iostream>
#include <exception>
#include <string>
using namespace std;

template <typename T>
class Set
{
private:
	struct Node
	{
		T value;
		Node* next;
		Node(T val, Node* N = nullptr): value(val), next(N) {}
	};
	Node* head;
	size_t size;
public:
	Set();//� ����
	Set(const Set& S);//� ����
	Set(T* elements, size_t n);//� ����
	Set(T element);//� ���� 
	~Set();
	size_t size_of_set()const;//� ����
	Set<T>& operator=(const Set& S);//� ����
	Set<T>& add_element(T element);//� ����
	Set<T>& add_range(T* elements, size_t n);//� ����
	Set<T> set_union(const Set& S)const;//� ����
	Set<T> set_difference(const Set& S)const;//� ����
	Set<T> set_intersect(const Set& S)const;//� ����
	Set<T> set_sum_diff(const Set& S)const;//� ����
	bool is_valid(const T& x)const;//� ����
	Set<T>& remove(const T& x);//� ����
	void write_to(std::ostream& out)const;//� ����
	T* all_values()const
	{
		T* arr = new T[this->size];
		Node* curr = head;
		int count = 0;
		while (curr != nullptr)
		{
			arr[count] = curr->value;
			++count;
			curr = curr->next;
		}
		return arr;
	}
	
	bool sets_are_equal(const Set<T>& A);
	bool is_empty()const;
};

template<typename T>
std::ostream& operator<<(std::ostream& out, const Set<T>& S)
{
	S.write_to(out); return out;
}

template<typename T>
bool Set<T>::sets_are_equal(const Set<T>& A)
{
	bool equalty = true;
	Node* this_ptr = head;
	Node* A_pointer = A.head;
	while (A_pointer != nullptr && this_ptr != nullptr)
	{
		if (A_pointer->value != this_ptr->value)
		{
			equalty = false;
			break;
		}
		A_pointer = A_pointer->next;
		this_ptr = this_ptr->next;
	}
	if (A_pointer != nullptr || this_ptr != nullptr)
		equalty = false;
	return equalty;
}

template<typename T>
bool Set<T>::is_empty()const
{
	if (head == nullptr)
		return true;
	else
		return false;
}

template<typename T>
void Set<T>::write_to(std::ostream& out)const
{
	Node* curr = head;
	while (curr != nullptr)
	{
		out << curr->value << ' ';
		curr = curr->next;
	}
}

template <typename T>
Set<T>::Set() : head(nullptr), size(0) {}

template<typename T>
Set<T>::Set(const Set& S): size(S.size)
{
	if (S.head == nullptr)
		head = nullptr;
	else
	{
		head = new Node(S.head->value);
		Node* curr = S.head->next;
		Node* temp = head;
		while (curr != nullptr)
		{
			temp->next = new Node(curr->value);
			temp = temp->next;
			curr = curr->next;
		}
	}
}

template<typename T>
Set<T>::Set(T* elements, size_t n): size(0)
{
	for (size_t i = 0; i < n; ++i)
	{
		if (!is_valid(elements[i]))
		{
			add_element(elements[i]);
		}
	}
}

template<typename T>
Set<T>::Set(T element)
{
	head = new Node(element);
	size = 1;
}

template<typename T>
Set<T>::~Set()
{
	while (head != nullptr)
	{
		Node* victom = head;
		head = head->next;
		delete victom;
	}
}

template<typename T>
size_t Set<T>::size_of_set()const
{
	return this->size;
}

template<typename T>
Set<T>& Set<T>::operator=(const Set& S)
{
	if (this != &S)
	{
		this->~Set();
		size = S.size;
		Node* curr = S.head;
		while (curr != nullptr)
		{
			this->add_element(curr->value);
			curr = curr->next;
		}
	}
	return *this;
}

template<typename T>
inline Set<T>& Set<T>::add_element(T element)
{
	if (is_valid(element))
		throw exception("This element is already in the set...Add_element funktion run into problem...");
	else
	{
		if (head == nullptr || element < head->value)
		{
			head = new Node(element, head);
		}
		else
		{
			Node* curr = head;
			while (curr->next != nullptr && curr->next->value < element)
				curr = curr->next;
			curr->next = new Node(element, curr->next);
		}
		++size;
		return *this;
	}
}

template <typename T>
Set<T>& Set<T>::add_range(T* elements, size_t n)
{
	for (size_t i = 0; i < n; ++i)
	{
		if (!is_valid(elements[i]))
		{
			add_element(elements[i]);
		}
	}
	return *this;
}

template<typename T>
Set<T> Set<T>::set_union(const Set& S)const
{
	Set<T> result;
	result.head = new Node(T());
	Node* this_pointer = head;
	Node* S_pointer = S.head;
	Node* result_pointer = result.head;
	while (this_pointer != nullptr && S_pointer != nullptr)
	{
		if (this_pointer->value < S_pointer->value)
		{
			result_pointer->next = new Node(this_pointer->value);
			result_pointer = result_pointer->next;
			++result.size;

			this_pointer = this_pointer->next;
		}
		else if (this_pointer->value == S_pointer->value)
		{
			result_pointer->next = new Node(this_pointer->value);
			result_pointer = result_pointer->next;
			++result.size;

			this_pointer = this_pointer->next;
			S_pointer = S_pointer->next;
		}
		else if (this_pointer->value > S_pointer->value)
		{
			result_pointer->next = new Node(S_pointer->value);
			result_pointer = result_pointer->next;
			++result.size;
			S_pointer = S_pointer->next;
		}
	}
	while (this_pointer != nullptr)
	{
		result_pointer->next = new Node(this_pointer->value);
		result_pointer = result_pointer->next;
		++result.size;
		this_pointer = this_pointer->next;
	}
	while (S_pointer != nullptr)
	{
		result_pointer->next = new Node(S_pointer->value);
		result_pointer = result_pointer->next;
		++result.size;
		S_pointer = S_pointer->next;
	}
	Node* victom = result.head;
	result.head = result.head->next;
	delete victom;
	return result;
}

template<typename T>
Set<T> Set<T>::set_difference(const Set& S)const
{
	Set<T> result;
	result.head = new Node(T());
	Node* result_pointer = result.head;
	Node* this_pointer = head;
	Node* S_pointer = S.head;
	while (this_pointer != nullptr && S_pointer != nullptr)
	{
		if (this_pointer->value < S_pointer->value)
		{
			result_pointer->next = new Node(this_pointer->value);
			result_pointer = result_pointer->next;
			++result.size;
			this_pointer = this_pointer->next;
		}
		else if (this_pointer->value == S_pointer->value)
		{
			this_pointer = this_pointer->next;
			S_pointer = S_pointer->next;
		}
		else if (S_pointer->value < this_pointer->value)
		{
			S_pointer = S_pointer->next;
		}
	}
	while (this_pointer != nullptr)
	{
		result_pointer->next = new Node(this_pointer->value);
		result_pointer = result_pointer->next;
		++result.size;

		this_pointer = this_pointer->next;
	}
	Node* victom = result.head;
	result.head = result.head->next;
	delete victom;
	return result;
}

template <typename T>
Set<T> Set<T>::set_intersect(const Set& S)const
{
	Set<T> result;
	result.head = new Node(T());
	Node* this_pointer = head;
	Node* S_pointer = S.head;
	Node* result_pointer = result.head;
	while (this_pointer != nullptr && S_pointer != nullptr)
	{
		if (this_pointer->value < S_pointer->value)
		{
			this_pointer = this_pointer->next;
		}
		else if (S_pointer->value < this_pointer->value)
		{
			S_pointer = S_pointer->next;
		}
		else if (this_pointer->value == S_pointer->value)
		{
			result_pointer->next = new Node(this_pointer->value);
			result_pointer = result_pointer->next;
			++result.size;

			this_pointer = this_pointer->next;
			S_pointer = S_pointer->next;
		}
	}
	Node* victom = result.head;
	result.head = result.head->next;
	delete victom;
	return result;
}

template<typename T>
Set<T> Set<T>::set_sum_diff(const Set& S)const
{
	Set<T> result;
	result.head = new Node(T());
	Node* this_pointer = head;
	Node* S_pointer = S.head;
	Node* result_pointer = result.head;
	while (this_pointer != nullptr && S_pointer != nullptr)
	{
		if (this_pointer->value < S_pointer->value)
		{
			result_pointer->next = new Node(this_pointer->value);
			result_pointer = result_pointer->next;
			++result.size;

			this_pointer = this_pointer->next;
		}
		else if (S_pointer->value < this_pointer->value)
		{
			result_pointer->next = new Node(S_pointer->value);
			result_pointer = result_pointer->next;
			++result.size;

			S_pointer = S_pointer->next;
		}
		else if (this_pointer->value == S_pointer->value)
		{
			this_pointer = this_pointer->next;
			S_pointer = S_pointer->next;
		}
	}
	while (this_pointer != nullptr)
	{
		result_pointer->next = new Node(this_pointer->value);
		this_pointer = this_pointer->next;
		result_pointer = result_pointer->next;
		++result.size;
	}
	while (S_pointer != nullptr)
	{
		result_pointer->next = new Node(S_pointer->value);
		S_pointer = S_pointer->next;
		result_pointer = result_pointer->next;
		++result.size;
	}
	Node* victom = result.head;
	result.head = result.head->next;
	delete victom;
	return result;
}

template<typename T>
bool Set<T>::is_valid(const T& x)const
{
	Node* curr = head;
	bool validness = false;
	while (curr != nullptr && curr->value <= x)
	{
		if (curr->value == x)
		{
			validness = true;
			break;
		}
		curr = curr->next;
	}
	return validness;
}

template<typename T>
Set<T>& Set<T>::remove(const T& x)
{
	if (is_valid(x))
	{
		if (head->value == x)
		{
			Node* victom = head;
			head = head->next;
			delete victom;
			--size;
		}
		else
		{
			Node* curr = head;
			while (curr->next->value != x)
			{
				curr = curr->next;
			}
			Node* victom = curr->next;
			curr->next = curr->next->next;
			delete victom;
			--size;
		}
		return *this;
	}
	else
		throw exception("This value is not valid. Remove function run into problem...");
}

size_t digits(int number)
{
	string str = to_string(number);
	Set<char> Chars;
	for (char c : str)
	{
		if (!Chars.is_valid(c))
			Chars.add_element(c);
	}
	return Chars.size_of_set();
}
//�������� 3(��� �������, ���� � ���������� ��������)
string first_entering(string& row)
{
	string result;
	Set<char> Chars;
	for (char c : row)
	{
		if (!Chars.is_valid(c))
		{
			Chars.add_element(c);
			result += c;
		}
	}
	return result;
}
size_t number_in_a_row(string& row, char s)
{
	size_t result = 0;
	for (char c : row)
	{
		if (c == s)
			++result;
	}
	return result;
}
Set<char> enter_more_than_twice(string& row)
{
	string all_symbols = first_entering(row);
	Set<char> set;
	for (char c : all_symbols)
	{
		int nof = number_in_a_row(row, c);
		if (nof >= 2)
		{
			set.add_element(c);
		}
	}
	return set;
}
Set<char> more_than_twice(string& row)
{
	Set<char> once;
	Set<char> more;
	for (char c : row)
	{
		if (!once.is_valid(c))
		{
			once.add_element(c);
		}
		else if (once.is_valid(c) && !more.is_valid(c))
		{
			more.add_element(c);
		}
	}
	return more;
}
Set<char> enter_only_once(string& row)
{
	Set<char> result;
	for (char c : row)
	{
		if (!result.is_valid(c) && number_in_a_row(row, c) == 1)
			result.add_element(c);
	}
	return result;
}
Set<char> only_once(string& row)
{
	Set<char> once;
	Set<char> not_once;
	for (char c : row)
	{
		if (!once.is_valid(c) && !not_once.is_valid(c))
		{
			once.add_element(c);
		}
		else
		{
			if (once.is_valid(c))
				once.remove(c);
			if (!not_once.is_valid(c))
				not_once.add_element(c);
		}
	}
	return once;
}

enum Products { bread, butter, milk, cheese, meat, fish, salt, sugar, tea, coffee, water };
Set<Products> in_every_store(Set<Products>* arr, size_t n)
{
	Set<Products> result;
	size_t min = 0;
	for (size_t i = 0; i < n; ++i)
	{
		if (arr[i].size_of_set() < min)
			min = i;
	}
	Products* product_arr = arr[min].all_values();
	size_t arr_size = arr[min].size_of_set();
	for (size_t i = 0; i < arr_size; ++i)
	{
		bool validness = true;
		for (size_t j = 0; j < n; ++j)
		{
			if (!arr[j].is_valid(product_arr[i]))
			{
				validness = false;
				break;
			}
		}
		if (validness)
		{
			result.add_element(product_arr[i]);
		}
	}
	return result;
}