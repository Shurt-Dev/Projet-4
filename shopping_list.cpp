#include <iostream>
#include <vector>
#include <string>
#include "shopping_list.h"

using namespace std;

vector<Products> shopping;

Products InitProduct(string n, int a) {
	Products p;
	p.name_product = n;
	p.amt_product = a;
	return p;
}

void InitShoppingList(vector<Products>& L) {
	string n;
	int a;
	char r = 'y';
	
	do {
		cout << "Wich item would you like to add to your list ?" << endl;
		cin >> n;
		cout << "In what quantity ?" << endl;
		cin >> a;
		L.resize(L.size() + 1);
		L[L.size() - 1] = InitProduct(n, a);
		cout << "" << endl;
		ShowList(L);
		cout << "" << endl;

		cout << "Would you like to add another item ? (y/n)" << endl;
		cin >> r;
	} while (r == 'y');
}

void DisplayProducts(const Products p) {
	cout << p.amt_product << ' ' << p.amt_product << endl;
}

void ShowList(const vector<Products>& L) {
	for (Products p : L) {
		DisplayProducts(p);
	}
}