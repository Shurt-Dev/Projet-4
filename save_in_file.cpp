#include <iostream>
#include <string>
#include <fstream>

struct ListData {
	std::string name_product;
	int amt_product;
};

std::ostream& operator<< (std::ostream& os, const ListData& d) {
	os << d.name_product << " " << d.amt_product << std::endl;
	return os; // permet de chaîner les appels
}

std::fstream f("monchemin/monfichier.txt");
f << myData; // en effet fstream est un ostream
f.close();