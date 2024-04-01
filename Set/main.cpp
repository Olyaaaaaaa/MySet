#include "Set.h"
using namespace std;
int main()
{
	int arr[] = { 11,56,78,9,3,44,56,7,9,5,1,21 };
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


	return 0;
}