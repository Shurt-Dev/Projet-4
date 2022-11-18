#pragma once

#include <string>

using namespace std;

struct Products {
	string name_product;
	int amt_product;
};

Products InitProduct(string n, int a);
void DisplayProducts(const Products p);
void ShowList(const vector<Products>& L);
void InitShoppingList(vector<Products>& L);