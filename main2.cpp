#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
//#include "header.h"
//#include "shopping_list.h"


int main2() {
    std::ifstream filein("monchemin/monfichier.txt");
    int nb = 0;
    std::vector<std::string> name_product;
    std::vector<int> amt_product;
    std::string ligne;
    while (std::getline(filein, ligne)) {
        size_t posit = ligne.find(" ");
        std::string nprod = ligne.substr(0, posit);
        int aprod;
        std::stringstream ss;
        ss << ligne.substr(posit);
        ss >> aprod;
        std::cout << nprod << "  " << aprod << std::endl;
        name_product.push_back(nprod);
        amt_product.push_back(aprod);
        ++nb;
    }
    return 0;
}


/*int main(int argc, char* argv[]) {
	vector<Products> newShopping;
	InitShoppingList(newShopping);

	return 0;
}*/

/*
	window_init(SCREEN_WIDTH, SCREEN_HEIGHT);
*/