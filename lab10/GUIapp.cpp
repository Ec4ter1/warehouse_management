#include "GUIapp.h"

void GUIapp::addGUI() {
    auto nume = Nume->text();
    auto tip = Tip->text();
    auto pret = Pret->text();
    auto produc = Produc->text();
	try {
		serv.add(nume.toStdString(), tip.toStdString(), pret.toInt(), produc.toStdString());
		loadData(serv.getAll_s());
	}
	catch (ProdusRepoException& ex) {
		QMessageBox::warning(this, "warning!", QString::fromStdString(ex.getMessage()));
	}
}

void GUIapp::StergeGUI() {
	auto nume = Nume->text();
	auto tip = Tip->text();
	auto pret = Pret->text();
	auto produc = Produc->text();
	try {
		serv.remove(nume.toStdString(), tip.toStdString(), pret.toInt(), produc.toStdString());
		loadData(serv.getAll_s());
	}
	catch (ProdusRepoException& ex) {
		QMessageBox::warning(this, "warning!", QString::fromStdString(ex.getMessage()));
	}
}

void GUIapp::ModifGUI() {
	auto nume = Nume->text();
	auto tip = Tip->text();
	auto pret = Pret->text();
	auto produc = Produc->text();
	try {
		serv.update(nume.toStdString(), tip.toStdString(), pret.toInt(), produc.toStdString());
		loadData(serv.getAll_s());
	}
	catch (ProdusRepoException& ex) {
		QMessageBox::warning(this, "warning!", QString::fromStdString(ex.getMessage()));
	}
}

void GUIapp::FilNumeGUI() {
	auto nume = Nume->text();
	vector<Prod> fil = serv.filtrare_nume_2(nume.toStdString());
	loadData(fil);
}

void GUIapp::FilPretGUI() {
	auto nume = Pret->text();
	vector<Prod> fil = serv.filtrare_pret_2(0, nume.toInt());
	loadData(fil);
}

void GUIapp::FilProducGUI() {
	auto nume = Produc->text();
	vector<Prod> fil = serv.filtrare_producator_2(nume.toStdString());
	loadData(fil);
}

void GUIapp::RaportGUI() {
	loadTable(serv.generate_map());
}

void GUIapp::addCosGUI() {
	auto nume = Nume->text();
	try {
		serv.adauga_cos(nume.toStdString());
		serv.notifyy();
	}
	catch (ProdusRepoException& ex) {
		QMessageBox::warning(this, "warning!", QString::fromStdString(ex.getMessage()));
	}
}

void GUIapp::GolCosGUI() {
	try {
		serv.golesteCos();
		serv.notifyy();
	}
	catch (ProdusRepoException& ex) {
		QMessageBox::warning(this, "warning!", QString::fromStdString(ex.getMessage()));
	}
	serv.golesteCos();
}

void GUIapp::AddRandCosGUI() {
	auto pret = Pret->text();
	try {
		serv.adauga_random(pret.toInt()); 
		//loadData(serv.toateDinCos(), lista2);
		serv.notifyy();
	}
	catch (ProdusRepoException& ex) {
		QMessageBox::warning(this, "warning!", QString::fromStdString(ex.getMessage()));
	}
}

void GUIapp::ExportCVSGUI() {
	serv.exportaCosCVS("testExport2.cvs", serv.get_All_cos());
}

void GUIapp::ExportHTMLGUI() {
	//qDebug()<<
	serv.exportaCosHTML("testExport2.html", serv.get_All_cos());
}

void GUIapp::undoGUI() {
	try {
		serv.undo_a();
		loadData(serv.getAll_s());
	}
	catch (ProdusRepoException& ex) {
		QMessageBox::warning(this, "warning!", QString::fromStdString(ex.getMessage()));
	}
}

void GUIapp::CosGUI() {
	try {
		qDebug("cos creat\n");
		CosGUICuLista* cosGUI = new CosGUICuLista{ serv, serv.getCart()};
		cosGUI->show();
	}
	catch (ProdusRepoException& ex) {
		QMessageBox::warning(this, "warning!", QString::fromStdString(ex.getMessage()));
	}
}

void GUIapp::CosReadGUI() {
	try {
		qDebug("cos creat\n");
		CosDesen* cosGUI = new CosDesen{ serv.getCart() };
		cosGUI->show();
	}
	catch (ProdusRepoException& ex) {
		QMessageBox::warning(this, "warning!", QString::fromStdString(ex.getMessage()));
	}
}