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
	Set<T>& clear_set();
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

	Set<int> eratosphene(int start, int end)
	{
		Set<int> our_set;
		for (int i = start; i <= end; ++i)
		{
			our_set.add_element(i);
		}
		Set<int> result(our_set);
		Node* current = result.head;
		while (current != nullptr)
		{
			Node* iterator = current->next;
			while (iterator != nullptr)
			{
				if ((iterator->next != nullptr) && (iterator->next->value % current->value) == 0)
				{
					cout << "dd" << endl;
					Node* victim = iterator->next;
					cout << "deleted val: " << iterator->next->value << endl;
					iterator->next = iterator->next->next;
					delete victim;
					cout << "deleted" << endl;
				}
				iterator = iterator->next;
			}
			current = current->next;
		}
		return result;
	}
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
	this->clear_set();
}

template<typename T>
Set<T>& Set<T>::clear_set()
{
	while (head != nullptr)
	{
		Node* victim = head;
		head = head->next;
		delete victim;
	}
	this->size = 0;
	return *this;
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
		this->clear_set();
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
//Завдання 3(два способи, один з додатковою функцією)
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
Set<char> only_once(string& row)// кращий варіант, оскільки обходимося без додаткових функцій.
//ефективніший, оскільки у попередній функції один рядок обходився кілька разів через функцію, яка рахувала кількість входжень одного символу.
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
	Set<Products> result = arr[0];
	for (size_t i = 1; i < n; ++i)
	{
		result = result.set_intersect(arr[i]);
	}
	return result;
}
Set<Products> at_least_in_one(Set<Products>* arr, size_t n)
{
	Set<Products> result = arr[0];
	for (size_t i = 1; i < n; ++i)
	{
		result = result.set_union(arr[i]);
	}
	return result;
}
Set<Products> unavailable(Set<Products>* arr, size_t n)
{
	Set<Products> all;
	all.add_element(bread).add_element(butter).add_element(milk).add_element(cheese).add_element(meat)
		.add_element(fish).add_element(salt).add_element(sugar).add_element(tea).add_element(coffee)
		.add_element(water);
	for (size_t i = 0; i < n; ++i)
	{
		all = all.set_difference(arr[i]);
	}
	return all;
}

//1 завдання
bool is_number(char symbol)
{
	return ((symbol >= '0') && (symbol <= '9'));
}
bool is_operator(char symbol)
{
	Set<char> operators;
	operators.add_element('+').add_element('-').add_element('*').add_element('/').add_element('^');
	return operators.is_valid(symbol);
}
bool is_bracket(char symbol)
{
	return (symbol == '(' || symbol == ')');
}
size_t number_of_symbols(string expression, bool(*predicate)(char))
{
	size_t count = 0;
	for (char c : expression)
	{
		if (predicate(c))
			++count;
	}
	return count;
}

