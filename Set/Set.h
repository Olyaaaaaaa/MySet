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
	Set();//є тест
	Set(const Set& S);//є тест
	Set(T* elements, size_t n);//є тест
	Set(T element);//є тест 
	~Set();
	size_t size_of_set()const;//є тест
	Set<T>& operator=(const Set& S);//є тест
	Set<T>& add_element(T element);//е тест
	Set<T>& add_range(T* elements, size_t n);//є тест
	Set<T> set_union(const Set& S)const;//є тест
	Set<T> set_difference(const Set& S)const;//є тест
	Set<T> set_intersect(const Set& S)const;//є тест
	Set<T> set_sum_diff(const Set& S)const;//є тест
	bool is_valid(const T& x)const;//є тест
	Set<T>& remove(const T& x);//є тест
	void write_to(std::ostream& out)const;//є тест
	
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
Set<T>::Set() : head(new Node(T ())), size(0) {}

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



