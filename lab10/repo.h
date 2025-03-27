#pragma once
#include "produs.h"
#include <vector>
#include <ostream>
#include <map>
using std::ostream;
using std::vector;

class repo_abs
{
public:
	virtual void store(const Prod& p) = 0;
	virtual void del(const Prod& p) = 0;

	//virtual const Prod& find(const Prod& p) const = 0;
	virtual const Prod& find_2(const string& nume) const = 0;
	virtual const vector<Prod>& getAll() = 0;

	virtual void modif(const string& nume, const string& tip, const string& produc, int pret) = 0;
	virtual ~repo_abs() = default;

};

class repo : public repo_abs
{
	vector<Prod> produse;
public:
	repo(const repo& ot) = delete;
	repo() = default;

	void store(const Prod& p) override;

	void del(const Prod& p) override;

	const vector<Prod>& getAll() override
	{
		return produse;
	}

	bool exista(const Prod& p) const;

	const Prod& find(const Prod& p) const ;
	const Prod& find_2(const string& nume) const override;

	void modif(const string& nume, const string& tip, const string& produc, int pret) override;

};

class ProdusRepoException {
	string msg;
public:
	ProdusRepoException(string m) :msg{ m } {}
	//functie friend (I want to use msg private member)
	friend ostream& operator<<(ostream& out, const ProdusRepoException& ex);
	string getMessage() {
		return msg;
	}
};

ostream& operator<<(ostream& out, const ProdusRepoException& ex);

class repo_lab : public repo_abs
{
	double prob;
	std::map<string, Prod> pr;

public:
	repo_lab(double p) : prob{ p } {}
	repo_lab(const repo& ot) = delete;
	repo_lab() = default;

	void store(const Prod& p) override;
	void del(const Prod& p) override;

	const vector<Prod>& getAll() override;

	//const Prod& find(const Prod& p) const override;
	const Prod& find_2(const string& nume) const override;
	void modif(const string& nume, const string& tip, const string& produc, int pret) override;

};

class repo_file : public repo
{
	string fileName;
	void load_from_file();
	void store_in_file();
public:
	repo_file(string file) : repo() , fileName{file} {
		load_from_file();
	};

	void store(const Prod& p) override {
		repo::store(p);
		store_in_file();
	}

	void del(const Prod& p) override {
		repo::del(p);
		store_in_file();
	}

	void modif(const string& nume, const string& tip, const string& produc, int pret) override {
		repo::modif(nume, tip, produc, pret);
		store_in_file();
	}
};

const double generate_rndom();
void testRepo();
void testRepoLab();
void testFileRepo();

