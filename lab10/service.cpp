#include "service.h"
#include "assert.h"
#include <iostream>
#include <string>
#include <random>   
#include <chrono>
#include <ctime>
#include <cstdlib>
#include "export_2.h"
#include "undo.h"

using std::cout;
using std::cin;

std::map<string,DTO> service::generate_map() {
	std::map<string, DTO> mp;
	for (auto& prod : repoo.getAll())
	{
		if (mp.find(prod.get_produc()) == mp.end())
		{
			DTO d{ prod.get_produc() };
			mp[prod.get_produc()] = d;
		}
		else
		{
			mp[prod.get_produc()].inc_count();
		}
	}
	return mp;
}

void service::undo_a() {
	if (undo.empty()) {
		throw ProdusRepoException{ "Nu mai exista operatii" };
	}
				
	undo.back()->doUndo();
	undo.pop_back();
}

void service::add(const string& nume, const string& tip, int price, const string& produc) {
	Prod p{ nume, tip, price, produc };
	repoo.store(p);
	undo.push_back(std::make_unique<UndoAdd>(repoo, p));
}

void service::remove(const string& nume, const string& tip, int price, const string& produc) {
	Prod p{ nume, tip, price, produc };
	repoo.del(p);
	undo.push_back(std::make_unique<UndoDel>(repoo, p));
}

void service::update(const string& nume, const string& tip_nou, int price_nou, const string& produc_nou) {
	Prod p2 = repoo.find_2(nume);
	repoo.modif(nume, tip_nou, produc_nou, price_nou);
	undo.push_back(std::make_unique<UndoModif>(repoo, p2));
}

/*Return a filtered list*/
vector<Prod> service::filtreaza(function<bool(const Prod&)> fct) {
	vector<Prod> rez;
	for (const auto& Produs : repoo.getAll()) {
		if (fct(Produs)) {
			rez.push_back(Produs);
		}
	}
	return rez;
}

vector<Prod> service::filtrare_nume(const string& nume) {
	return filtreaza([=](const Prod& p) {
		return p.get_nume() == nume;
		});
}

vector<Prod> service::filtrare_nume_2(const string& nume) {
	std::vector<Prod> rez;
	auto& all = repoo.getAll();
	std::copy_if(all.begin(), all.end(), back_inserter(rez), [=](const Prod& p) {return p.get_nume() == nume; });
	return rez;
}

vector<Prod> service::filtrare_pret(int pretMin, int pretMax) {
	return filtreaza([=](const Prod& p) {
		return p.get_pret() >= pretMin && p.get_pret() <= pretMax;
		});
}

vector<Prod> service::filtrare_pret_2(int pretMin, int pretMax) const {
	std::vector<Prod> rez;
	auto& all = repoo.getAll();
	std::copy_if(all.begin(), all.end(), back_inserter(rez), [=](const Prod& p) {return p.get_pret() >= pretMin && p.get_pret() <= pretMax; });
	return rez;
}

vector<Prod> service::filtrare_producator(const string& producer) {
	return filtreaza([=](const Prod& p) {
		return p.get_produc() == producer;
		});
}

vector<Prod> service::filtrare_producator_2(const string& producer) {
	std::vector<Prod> rez;
	auto& all = repoo.getAll();
	std::copy_if(all.begin(), all.end(), back_inserter(rez), [=](const Prod& p) {return p.get_produc() == producer; });
	return rez;
}

vector<Prod> service::generalSort(bool(*fct)(const Prod&, const Prod&)) {
	vector<Prod> v{ repoo.getAll() };//fac o copie	
	for (int i = 0; i < v.size(); i++) {
		for (int j = i + 1; j < v.size(); j++) {
			if (!fct(v[i], v[j])) {
				Prod aux = v[i];
				v[i] = v[j];
				v[j] = aux;
			}
		}
	}
	return v;
}

vector<Prod> service::sortPrice() {
	auto v = repoo.getAll();
	std::sort(v.begin(), v.end(), [](const Prod& p1, const Prod& p2) {return cmpPret(p1, p2); });
	return v;
}

vector<Prod> service::SortName() const {
	auto v = repoo.getAll();
	std::sort(v.begin(), v.end(), [](const Prod& p1, const Prod& p2) {
		return cmpName(p1, p2);
		});
	return v;
}

vector<Prod> service::sortByNameType() {
	return generalSort([](const Prod& p1, const Prod& p2) {
		if (p1.get_nume() == p2.get_nume()) {
			return p1.get_tip() < p2.get_tip();
		}
		return p1.get_nume() < p2.get_nume();
		});
}

vector<Prod> service::sortByNameType_2() {
	auto v = repoo.getAll();
	std::sort(v.begin(), v.end(), [](const Prod& p1, const Prod& p2) {
		if (p1.get_nume() == p2.get_nume()) {
			return p1.get_tip() < p2.get_tip();
		}
		return p1.get_nume() < p2.get_nume();
		});
	return v;
}

int service::adauga_cos(const string& nume)
{
	Prod p = repoo.find_2(nume);
	cosulet.adauga(p);
	return cosulet.get_total();
}

int service::golesteCos() {
	cosulet.goleste();
	return cosulet.get_total();
}

const std::vector<Prod>& service::toateDinCos() {
	return cosulet.lista();
}

int service::adauga_random(int cate) {
	cosulet.umple(cate, repoo.getAll());
	return cosulet.get_total();
}

void service::exportaCosCVS(std::string fName, std::vector<Prod> p) const {
	exportToCVS(fName, p);
}

void service::exportaCosHTML(std::string fName, std::vector<Prod> p)const {
	exportToHTML(fName, p);
}

void testService()
{
	//add
	repo rep;
	service serv{ rep };
	serv.add("f", "f", 23, "h");
	const auto& produse = serv.getAll_s();
	assert(produse.size() == 1);
	serv.add("aaa", "h", 78, "k");
	assert(serv.getAll_s().size() == 2);
	//remove
	serv.remove("f", "f", 23, "h");
	assert(serv.getAll_s().size() == 1);
	//update
	serv.update("aaa", "aaa", 12, "a");
	assert(serv.getAll_s()[0].get_tip() == "aaa");
	//filtrare
	serv.add("aaa2", "l", 7, "er");
	assert(serv.filtrare_nume("aaa2").size() == 1);
	assert(serv.filtrare_pret(2, 8).size() == 1);
	assert(serv.filtrare_producator("er").size() == 1);
	//filtrare_2
	assert(serv.filtrare_nume_2("aaa2").size() == 1);
	assert(serv.filtrare_pret_2(6,10).size() == 1);
	assert(serv.filtrare_producator_2("er").size() == 1);
	//sort
	serv.add("ddd", "k", 9, "o");
	serv.add("c", "k", 8, "o");
	assert(serv.generalSort(cmpName)[2].get_nume() == "c");
	assert(serv.generalSort(cmpPret)[1].get_nume() == "c");
	assert(serv.sortByNameType()[0].get_tip() == "aaa");
	//sort_2
	assert(serv.SortName()[2].get_nume() == "c");
	assert(serv.sortPrice()[1].get_nume() == "c");
	assert(serv.sortByNameType_2()[0].get_tip() == "aaa");
	//cos
	assert(serv.toateDinCos().size() == 0);
	serv.adauga_cos("aaa");
	assert(serv.toateDinCos().size() == 1);
	assert(serv.toateDinCos()[0].get_nume() == "aaa");
	serv.golesteCos();
	assert(serv.toateDinCos().size() == 0);
	serv.adauga_random(2);
	assert(serv.toateDinCos().size() == 2);
	//map
	std::map<string, DTO> m = serv.generate_map();
	assert(m["o"].get_count() == 2);

}

void testUndo() {
	repo rep;
	service serv{ rep };
	serv.add("aaa", "bbb", 3, "l");
	serv.add("ccc", "bbb", 2, "j");
	serv.add("bbb", "bbb", 1, "k");
	serv.undo_a();
	assert(serv.getAll_s().size() == 2);
	serv.remove("ccc", "bbb", 2, "j");
	serv.undo_a();
	assert(serv.getAll_s().size() == 2);
	serv.update("ccc", "p", 55, "e");
	serv.undo_a();
	assert(serv.getAll_s()[1].get_nume() == "ccc");
	serv.undo_a();
	serv.undo_a();
	assert(serv.getAll_s().size() == 0);
	try {
		serv.undo_a();
	}
	catch (ProdusRepoException& ) {
		assert(true);
	}
}

#include <fstream>
void testExporta() {
	repo rep;
	service serv{ rep };
	serv.add("aaa", "bbb", 3, "l");
	serv.add("ccc", "bbb", 2, "k");
	serv.add("bbb", "bbb", 1, "p");
	serv.adauga_random(3);
	serv.exportaCosCVS("testExport.cvs", serv.get_All_cos());
	std::ifstream in("testExport.cvs");
	assert(in.is_open());
	int countLines = 0;
	while (!in.eof()) {
		string line;
		in >> line;
		countLines++;
	}
	in.close();
	assert(countLines == 4);
	serv.exportaCosHTML("testExport.html", serv.get_All_cos());
	in.open("testExport.html");
	assert(in.is_open());

	//daca se da un nume de fisier invalid se arunca exceptie
	try {
		serv.exportaCosCVS("test/Export.cvs", serv.get_All_cos());
	}
	catch (ProdusRepoException&) {
		assert(true);
	}
	try {
		serv.exportaCosHTML("a/b/c/Export.html", serv.get_All_cos());
	}
	catch (ProdusRepoException&) {
		assert(true);
	}
}