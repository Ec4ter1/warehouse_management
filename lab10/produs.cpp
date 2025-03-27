#include "produs.h"
#include "assert.h"

string Prod::get_nume() const
{
	return nume;
}

string Prod::get_tip() const
{
	return tip;
}

int Prod::get_pret() const
{
	return pret;
}

string Prod::get_produc() const
{
	return producator;
}

void Prod::set_nume(string new_value) {
	nume = new_value;
}

void Prod::set_tip(string new_value) {
	tip = new_value;
}

void Prod::set_pret(int new_value) {
	pret = new_value;
}

void Prod::set_produc(string new_value) {
	producator = new_value;
}

bool cmpName(const Prod& p1, const Prod& p2) {
	return p1.get_nume() < p2.get_nume();
}

bool cmpPret(const Prod& p1, const Prod& p2) {
	return p1.get_pret() < p2.get_pret();
}

void testProd()
{
	Prod p{ "Cafea", "Nesq", 123, "Nescuiq" };
	assert(p.get_nume() == "Cafea");
	assert(p.get_tip() == "Nesq");
	assert(p.get_pret() == 123);
	assert(p.get_produc() == "Nescuiq");
	p.set_nume("Aba");
	p.set_tip("k");
	p.set_pret(12);
	p.set_produc("Olaf");
	assert(p.get_nume() == "Aba");
	assert(p.get_tip() == "k");
	assert(p.get_pret() == 12);
	assert(p.get_produc() == "Olaf");
	Prod p2{ "A","j",12,"l" };
	assert(cmpName(p, p2) == 0);
	assert(cmpPret(p, p2) == 0);
}