#pragma once

#include "produs.h"
#include "repo.h"
#include <string>
#include <vector>
#include <functional>
#include "cos.h"
#include <map>
#include "DTO.h"
#include "undo.h"

using std::unique_ptr;
using std::function;

class service
{
	repo_abs& repoo;

	Cos cosulet;

	std::vector<unique_ptr<Undo>> undo;

public:
	service(repo_abs& rep) :repoo{ rep } {}

	service(const service& s) = delete;
	service() = default;

	std::map<string,DTO> generate_map();

	const vector<Prod>& getAll_s() 
	{
		return repoo.getAll();
	}

	Cos& getCart() {
		return cosulet;
	}

	vector<Prod> get_All_cos() {
		return cosulet.lista();
	}

	vector<Prod>filtreaza(function<bool(const Prod&)> fct);
	vector<Prod> generalSort(bool(*fct)(const Prod&, const Prod&));

	void add(const string& nume, const string& tip, int price, const string& produc);

	void remove(const string& nume, const string& tip, int price, const string& produc);

	void update(const string& nume, const string& tip_nou, int price_nou, const string& produc_nou);

	vector<Prod> filtrare_nume(const string& type);
	vector<Prod> filtrare_nume_2(const string& type);

	vector<Prod> filtrare_pret(int pretMin, int pretMax);
	vector<Prod> filtrare_pret_2(int pretMin, int pretMax) const;

	vector<Prod> filtrare_producator(const string& producer);
	vector<Prod> filtrare_producator_2(const string& producer);

	vector<Prod> sortByNameType();
	vector<Prod> sortByNameType_2();

	vector<Prod> sortPrice();
	vector<Prod> SortName() const;

	int adauga_cos(const string& nume);

	int golesteCos();

	int adauga_random(int cate);

	const std::vector<Prod>& toateDinCos();

	void exportaCosCVS(std::string fName, std::vector<Prod> p) const;

	void exportaCosHTML(std::string fName, std::vector<Prod> p)const;

	void undo_a();

	void notifyy() {
		cosulet.notify();
	}
};


void testService();
void testExporta();
void testUndo();
