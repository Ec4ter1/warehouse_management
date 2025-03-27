#include "repo.h"
#include "assert.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <random>   
#include <chrono>
#include <fstream>
#include <sstream>
using std::cout;
using std::cin;

ostream& operator<<(ostream& out, const ProdusRepoException& ex) {
	out << ex.msg;
	return out;
}

void repo::store(const Prod& p)
{
	if (exista(p)) {
		throw ProdusRepoException("Exista deja produsul: " + p.get_nume());
	}
	if (p.get_nume() == "" || p.get_pret() == 0)
	{
		throw ProdusRepoException("Produs invalid");
	}
	produse.push_back(p);
}

void repo::del(const Prod& p)
{
	if (!exista(p)) {
		throw ProdusRepoException("Nu exista produsul: " + p.get_nume() + " tip: " + p.get_tip() + " producator: " + p.get_produc());
	}
	auto found = std::find_if(produse.begin(), produse.end(), [p](const Prod& pp) {
		return pp.get_nume() == p.get_nume() && pp.get_tip() == p.get_tip();
		});
	
	auto rez = produse.erase(found);
}

bool repo::exista(const Prod& p) const {
	try {
		find(p);
		return true;
	}
	catch (ProdusRepoException&) {
		return false;}
}

void repo::modif(const string& nume, const string& tip, const string& produc, int pret)
{
	if (!exista(find_2(nume))) {
		throw ProdusRepoException("Nu exista produsul");
	}
	for (auto& prod : produse)
		if (prod.get_nume() == nume)
		{
			prod.set_tip(tip);
			prod.set_pret(pret);
			prod.set_produc(produc);
		}
}


const Prod& repo::find(const Prod& p) const {
	for (auto& prod : produse)
		if (prod.get_nume() == p.get_nume())
			return prod;
	throw ProdusRepoException("Nu exista produsul: " + p.get_nume() + " tip: " + p.get_tip() + " producator: " + p.get_produc());
}

const Prod& repo::find_2(const string& nume) const {
	for (auto& prod:produse)
		if (prod.get_nume() == nume)
			return prod;
	throw ProdusRepoException("Nu exista produsul: " + nume);
}

const double generate_rndom() {
	std::uniform_real_distribution<double> distribution(0, 1.0);
	std::random_device rd;
	std::default_random_engine generator(rd());
	return distribution(generator);
}

void repo_lab::store(const Prod& p)
{
	const double random = generate_rndom();
	if (random < prob) {
		throw ProdusRepoException("Nuhuh");
	}
	pr[p.get_nume()] = p;
}

void repo_lab::del(const Prod& p)
{
	const double random = generate_rndom();
	if (random < prob) {
		throw ProdusRepoException("Nuhuh");
	}
	pr.erase(p.get_nume());
}

void repo_lab::modif(const string& nume, const string& tip, const string& produc, int pret)
{
	const double random = generate_rndom();
	if (random < prob) {
		throw ProdusRepoException("Nuhuh");
	}
	Prod p2{ nume, tip, pret, produc };
	pr[nume] = p2;
}

vector<Prod> all;
const vector<Prod>& repo_lab::getAll()
{
	all.clear();
	for (auto& it : pr) {
		all.push_back(it.second);
	}
	return all;
}

const Prod& repo_lab::find_2(const string& nume) const {
	for (auto& prod : pr)
		if (prod.second.get_nume() == nume)
			return prod.second;
	throw ProdusRepoException("Nu exista produsul: " + nume);
}

void repo_file::load_from_file() {
	std::ifstream fin(fileName);
	string str;
	while (getline(fin, str)) {
		std::stringstream ss(str);

		string word;
		vector<string> produ;
		while (getline(ss, word, ';')) {
			produ.push_back(word);
		}
		repo::store(Prod{ produ[0], produ[1], stoi(produ[2]), produ[3]});
	}
	fin.close();
}

void repo_file::store_in_file() {
	std::ofstream fout(fileName);
	for (auto& it : repo::getAll()) {
		fout << it.get_nume() << ";" << it.get_tip() << ";" << it.get_pret() << ";" << it.get_produc() << "\n";
	}
	fout.close();
}




void testRepo()
{
	//adaugare
	repo rep;
	Prod p{ "e", "f", 23, "s" };
	rep.store(p);
	const auto& produse = rep.getAll();
	assert(produse.size() == 1);
	Prod p2{ "r", "d", 23, "s" };
	rep.store(p2);
	try {
		rep.store(p2);
	}
	catch (ProdusRepoException)
	{
		assert(true);
	}
	//assert(rep.getAll().size() == 2);
	try {
		rep.store(p);
	}
	catch (ProdusRepoException&)
	{
		assert(true);
	}
	//stergere
	rep.del(p2);
	assert(rep.getAll().size() == 1);
	try {
		rep.del(p2);
	}
	catch (ProdusRepoException&)
	{
		assert(true);
	}
	//find
	Prod p3 = rep.find(p);
	assert(p3.get_nume() == "e");
	p3 = rep.find_2("e");
	assert(p3.get_nume() == "e");
	try {
		rep.find(p2);
	}
	catch (ProdusRepoException&)
	{
		assert(true);
	}
	try {
		rep.find_2("www");
	}
	catch (ProdusRepoException&)
	{
		assert(true);
	}
	//exista
	assert(rep.exista(p) == 1);
	assert(rep.exista(p2) == 0);
	//modifica
	try {
		rep.modif("r", "aa","a",1);
	}
	catch (ProdusRepoException&)
	{
		assert(true);
	}
	rep.modif("e", "aa", "a", 1);
	const auto& produse2 = rep.getAll();
	assert(produse2[0].get_tip() == "aa");
	
}

void testRepoLab()
{
	//adaugare
	repo_lab rep{ 0 };
	Prod p{ "e", "f", 23, "s" };
	rep.store(p);
	assert(rep.getAll().size() == 1);
	rep.del(p);
	assert(rep.getAll().size() == 0);
	rep.store(p);
	rep.modif("e", "p", "p", 8);
	vector<Prod> mapi = rep.getAll();
	assert(mapi[0].get_pret() == 8);
	repo_lab rep2{ 1 };
	try {
		rep.store(p);
	}
	catch (ProdusRepoException){
		assert(true);}
}

void testFileRepo() {
	std::ofstream out("test_prod.txt", std::ios::trunc);
	out.close();
	//adauga
	Prod p1 = Prod{ "aaa","bbb", 12 , "l" };
	repo_file repF{ "test_prod.txt" };
	repF.store(p1);

	repo_file repF2{ "test_prod.txt" };
	auto p = repF2.find(p1);
	assert(p.get_pret() == 12);
	try {
		repF2.find(Prod{ "aaa2","bbb2",12 , "l" });
	}
	catch (ProdusRepoException&) {
	}
	//sterge
	repF2.del(p1);
	assert(repF2.getAll().size() == 0);
	try {
		repF2.del(Prod{ "aaa2","bbb2",12 , "l" });
		}
	catch (ProdusRepoException&) {
	}
	//modifica
	try {
		repF2.modif("aaa2", "z", "z", 1);
	}
	catch (ProdusRepoException&) {
	}
	Prod p2 = Prod{ "k","k",2,"k" };
	repF.store(p2);
	repF.modif("k", "z", "z", 1);
	assert(repF.getAll()[1].get_tip()=="z");

	repo_file repF3{ "test_prod.txt" };
	assert(repF3.getAll().size() == 2);
	assert(repF2.getAll().size() == 0);

}