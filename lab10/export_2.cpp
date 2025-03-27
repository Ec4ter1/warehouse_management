#include "export_2.h"
#include "produs.h"
#include "repo.h"
#include <fstream>
#include <string>
#include <vector>

void exportToCVS(const std::string& fName, const std::vector<Prod>& produse) {
	std::ofstream out(fName, std::ios::trunc);
	if (!out.is_open()) {
		throw ProdusRepoException("Unable to open file:" + fName);
	}
	for (const auto& p : produse) {
		out << p.get_nume() << ",";
		out << p.get_tip() << ",";
		out << p.get_pret() << ",";
		out << p.get_produc() << std::endl;
	}
	out.close();
}

void exportToHTML(const std::string& fName, const std::vector<Prod>& pets) {
	std::ofstream out(fName, std::ios::trunc);
	if (!out.is_open()) {
		throw ProdusRepoException("Unable to open file:" + fName);
	}
	out << "<html><body>" << std::endl;
	out << "<table border=\"1\" style=\"width:100 % \">" << std::endl;
	for (const auto& p : pets) {
		out << "<tr>" << std::endl;
		out << "<td>" << p.get_nume() << "</td>" << std::endl;
		out << "<td>" << p.get_tip() << "</td>" << std::endl;
		out << "<td>" << p.get_pret() << "</td>" << std::endl;
		out << "<td>" << p.get_produc() << "</td>" << std::endl;
		out << "</tr>" << std::endl;
	}
	out << "</table>" << std::endl;
	out << "</body></html>" << std::endl;
	out.close();
}