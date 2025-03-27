#pragma once
#include <string>
#include <iostream>
using std::string;
using std::cout;

class Prod
{
	string nume;
	string tip;
	int pret;
	string producator;

public:

	Prod(const string nume, const string tip, int pret, string produc) :nume{ nume }, tip{ tip }, pret{ pret }, producator { produc }{}
	Prod() = default;
	
	string get_nume() const;

	string get_tip() const;

	int get_pret() const;

	string get_produc() const;

	Prod(const Prod& p) : nume{ p.nume }, tip{ p.tip }, pret{ p.pret }, producator{ p.producator } { cout << "Copie!!!!";  }

	void set_nume(string new_value);

	void set_tip(string new_value);

	void set_pret(int new_value);

	void set_produc(string new_value);

};
bool cmpName(const Prod& p1, const Prod& p2);
bool cmpPret(const Prod& p1, const Prod& p2);
void testProd();

