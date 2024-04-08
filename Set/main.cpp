#include "Set.h"
using namespace std;
int main()
{
	/*int arr[] = { 11,56,78,9,3,44,56,7,9,5,1,21 };
	size_t n = sizeof arr / sizeof arr[0];
	Set<int> T(arr,n);
	cout <<"Set T: "<< T << endl;
	int arr1[] = { 21,34,56,78,2,6,7,8,9 };
	size_t n1 = sizeof arr1 / sizeof arr1[0];
	Set<int> T1(arr1,n1);
	cout <<"Set T1: "<< T1 << endl;
	cout << endl;
	cout << "Union: " << T.set_union(T1) << endl;
	cout << "Size: " << T.set_union(T1).size_of_set() << endl;
	cout << "Difference: " << T.set_difference(T1) << endl;
	cout << "Size: " << T.set_difference(T1).size_of_set() << endl;
	cout << "Intersection: " << T.set_intersect(T1) << endl;
	cout << "Size: " << T.set_intersect(T1).size_of_set() << endl;
	cout << "Symmetrical difference: " << T.set_sum_diff(T1) << endl;
	cout << "Size: " << T.set_sum_diff(T1).size_of_set() << endl;
	T1.remove(21).remove(56).remove(2);
	cout << "Set T1 after removing several elements: " << T1 << endl;
	T.add_element(111).add_element(222).add_element(333).add_element(55);
	cout << "Set T after adding several elements: " << T << endl;
	string expression;*/
	string expression;
	cout << "Enter expression: "; 
	getline(cin, expression, '\n');
	cout << "Amount of numbers: " << number_of_symbols(expression, is_number) << endl;
	cout << "Amount of operators: " << number_of_symbols(expression, is_operator) << endl;
	cout << "Amount of brackets: " << number_of_symbols(expression, is_bracket) << endl;
	cout << endl;

	int value;
	cout << "Enter your value: "; cin >> value;
	cout << "Number of different numbers: " << digits(value) << endl;
	cout << endl;
	string row;
	cout << "Enter your row: "; cin >> row;
	cout << "First entering: " << first_entering(row) << endl;
	cout << "All symbols that enter the row more than twice: " << enter_more_than_twice(row) << endl;
	cout << "All symbols that enter the row more than twice(another way): " << more_than_twice(row) << endl;
	cout << "All symbols that enter the row only once: " << enter_only_once(row) << endl;
	cout << "All symbols that enter the row only once(another way): " << only_once(row) << endl;
	cout << endl;
	Set<Products> Shops[4];
	Shops[0].add_element(milk).add_element(water).add_element(butter).add_element(salt);
	Shops[1].add_element(milk).add_element(cheese).add_element(butter).add_element(sugar).add_element(salt);
	Shops[2].add_element(milk).add_element(bread).add_element(butter).add_element(coffee).add_element(salt);
	Shops[3].add_element(milk).add_element(tea).add_element(butter).add_element(bread).add_element(salt);
	for (size_t i = 0; i < 4; ++i)
	{
		cout << "Shop #" << i << ": " << Shops[i] << endl;
	}
	cout << endl;
	cout << "Products available everywhere: " << in_every_store(Shops, 4) << endl;
	cout << "Products available at least in one shop: " << at_least_in_one(Shops, 4) << endl;
	cout << "Products unavailable everywhere: " << unavailable(Shops, 4) << endl;
	cout << endl;
	cin.clear();
	/*Set<int> set;
	cout << "Simple numbers: " << set.eratosphene(2, 1254) << endl;*/
	
	return 0;
}