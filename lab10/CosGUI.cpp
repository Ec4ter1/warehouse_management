#include "CosGUI.h"

void CosGUICuLista::addCosGUI() {
	auto nume = Nume->text();
	try {
		serv.adauga_cos(nume.toStdString());
		loadData(serv.toateDinCos());
		cosulet.notify();
	}
	catch (ProdusRepoException& ex) {
		QMessageBox::warning(this, "warning!", QString::fromStdString(ex.getMessage()));
	}
}

void CosGUICuLista::GolCosGUI() {
	try {
		serv.golesteCos();
		loadData(serv.toateDinCos());
		cosulet.notify();
	}
	catch (ProdusRepoException& ex) {
		QMessageBox::warning(this, "warning!", QString::fromStdString(ex.getMessage()));
	}
	serv.golesteCos();
}

void CosGUICuLista::AddRandCosGUI() {
	auto pret = serv.getAll_s().size();
	try {
		serv.adauga_random(pret); 
		loadData(serv.toateDinCos());
		cosulet.notify();
	}
	catch (ProdusRepoException& ex) {
		QMessageBox::warning(this, "warning!", QString::fromStdString(ex.getMessage()));
	}
}