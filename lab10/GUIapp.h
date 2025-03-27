#pragma once
#include "CosGUI.h"
#include "CosRD_ONLY.h"
#include "TableModel.h"
#include <QtWidgets/qwidget.h>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qformlayout.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qlistwidget.h>
#include <QtWidgets/qtablewidget.h>
#include <QtWidgets/qmainwindow.h>
#include <qstring.h>
#include <qmessagebox.h>
#include <qdebug.h>
#include <vector>
#include "produs.h"
#include "service.h"
#include "string.h"
using std::vector;

class GUIapp : public QWidget
{
public:
    GUIapp(service& serv) : serv{ serv } {
		initGUI();
        loadData(serv.getAll_s());
        initConnect();
	}
private:
    service& serv;
    TableModel* modelTabel;
    QListView* lstV = new QListView;
    QTableView* tblV = new QTableView;

    QListWidget* lista = new QListWidget;
    QListWidget* lista2 = new QListWidget;
    int col = serv.generate_map().size();
    QTableWidget* tabel = new QTableWidget{ 2, col};
    QLineEdit* Nume = new QLineEdit;
    QLineEdit* Tip = new QLineEdit;
    QLineEdit* Pret = new QLineEdit;
    QLineEdit* Produc = new QLineEdit;
    QPushButton* Exit = new QPushButton{ "Exit" };
    QPushButton* Add = new QPushButton{ "Add" };
    QPushButton* Sterge = new QPushButton{ "Sterge" };
    QPushButton* Modif = new QPushButton{ "Modifica" };
    QPushButton* FilNume = new QPushButton{ "Filtrare nume" };
    QPushButton* FilPret = new QPushButton{ "Filtrare pret" };
    QPushButton* FilProd = new QPushButton{ "Filtrare producator" };
    QPushButton* ExportHTML = new QPushButton{ "Exporta html" };
    QPushButton* ExportCVS = new QPushButton{ "Exporta CVS" };
    QPushButton* Cos = new QPushButton{ "Cos" };
    QPushButton* CosRDONLY = new QPushButton{ "Cos Read only" };
    QPushButton* AddCos = new QPushButton{ "Adauga cos" };
    QPushButton* GolCos = new QPushButton{ "Goleste cos" };
    QPushButton* AddRandCos = new QPushButton{ "Adauga random cos" };
    QPushButton* AfisCos = new QPushButton{ "Afis cos" };
    QPushButton* Raport = new QPushButton{ "Raport" };
    QPushButton* Undo = new QPushButton{ "Undo" };

    void addGUI();
    void StergeGUI();
    void ModifGUI();
    void FilNumeGUI();
    void FilPretGUI();
    void FilProducGUI();
    void ExportHTMLGUI();
    void ExportCVSGUI();
    void RaportGUI();
    void addCosGUI();
    void GolCosGUI();
    void AddRandCosGUI();
    void undoGUI();
    void CosGUI();
    void CosReadGUI();

    void initConnect() {
        QObject::connect(Exit, &QPushButton::clicked, [&]() {
            qDebug() << "Exit apasat";
            QMessageBox::information(nullptr, "Info", "Exit apasat");
            close();
            });

        QObject::connect(Add, &QPushButton::clicked, [&]() {
            addGUI();
            });

        QObject::connect(Sterge, &QPushButton::clicked, [&]() {
            StergeGUI();
            });

        QObject::connect(Modif, &QPushButton::clicked, [&]() {
            ModifGUI();
            });

        QObject::connect(FilNume, &QPushButton::clicked, [&]() {
            FilNumeGUI();
            });

        QObject::connect(FilPret, &QPushButton::clicked, [&]() {
            FilPretGUI();
            });

        QObject::connect(FilProd, &QPushButton::clicked, [&]() {
            FilProducGUI();
            });

        QObject::connect(ExportHTML, &QPushButton::clicked, [&]() {
            ExportHTMLGUI();
            });

        QObject::connect(ExportCVS, &QPushButton::clicked, [&]() {
            ExportCVSGUI();
            });

        QObject::connect(Raport, &QPushButton::clicked, [&]() {
            RaportGUI();
            });

        QObject::connect(AddCos, &QPushButton::clicked, [&]() {
            addCosGUI();
            });

        QObject::connect(GolCos, &QPushButton::clicked, [&]() {
            GolCosGUI();
            });

        QObject::connect(AddRandCos, &QPushButton::clicked, [&]() {
            AddRandCosGUI();
            });

        QObject::connect(Undo, &QPushButton::clicked, [&]() {
            undoGUI();
            });

        QObject::connect(Cos, &QPushButton::clicked, [&]() {
            CosGUI();
            });

        QObject::connect(CosRDONLY, &QPushButton::clicked, [&]() {
            CosReadGUI();
            });

    }

	void initGUI() {
        QHBoxLayout* lymain = new QHBoxLayout{};
        setLayout(lymain);

        auto st = new QVBoxLayout{};
        //auto lista = new QListWidget;
        auto ly1 = new QFormLayout;
        //////////ly1->addWidget(lista);
        ly1->addWidget(tblV);
        auto listaButoane3 = new QHBoxLayout{};
        listaButoane3->addWidget(AddCos);
        listaButoane3->addWidget(GolCos);
        listaButoane3->addWidget(AddRandCos);
        listaButoane3->addWidget(ExportHTML);
        listaButoane3->addWidget(ExportCVS);
        ly1->addRow(listaButoane3);
        lymain->addLayout(ly1);
        auto ly2 = new QFormLayout;
        ly2->addRow("Nume", Nume);
        ly2->addRow("Tip", Tip);
        ly2->addRow("Pret", Pret);
        ly2->addRow("Producator", Produc);
        st->addLayout(ly2);
        auto listaButoane = new QHBoxLayout{};
        listaButoane->addWidget(Add);
        listaButoane->addWidget(Sterge);
        listaButoane->addWidget(Modif);
        listaButoane->addWidget(Exit);
        ly2->addRow(listaButoane);
        //st->addLayout(listaButoane);
        auto listaButoane2 = new QHBoxLayout{};
        listaButoane2->addWidget(FilNume);
        listaButoane2->addWidget(FilPret);
        listaButoane2->addWidget(FilProd);
        listaButoane2->addWidget(Raport);
        listaButoane2->addWidget(Cos);
        listaButoane2->addWidget(CosRDONLY);
        listaButoane2->addWidget(Undo);
        ly2->addRow(listaButoane2);
        ly2->addRow(tabel);
        //st->addLayout(listaButoane2);
        lymain->addLayout(st);

        /*QMainWindow* lymain2 = new QMainWindow;
        lymain2->show();*/
	}
    void loadData(vector<Prod> produse)
    {
        /*lista->clear();
        for (auto& p : produse) {
            string o = p.get_nume() + "  " + p.get_tip() + "  " + std::to_string(p.get_pret()) + "  " + p.get_produc();
            QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(o), lista);
            item->setData(Qt::UserRole, QString::fromStdString(o));
            item->setData(Qt::BackgroundRole, QBrush{ Qt::blue, Qt::BDiagPattern });
            lista->addItem(item);
        }*/
        modelTabel = new TableModel{ produse };
        tblV->setModel(modelTabel);

    }

    void loadTable(std::map<string, DTO> mapi)
    {
        tabel->clear();
        int k = 0;
        for (auto& p:mapi)
        {
            QTableWidgetItem* itemi = new QTableWidgetItem(QString::fromStdString(p.first));
            QTableWidgetItem* itemi2 = new QTableWidgetItem(QString::fromStdString(std::to_string(p.second.get_count())));
            tabel->setItem(0, k, itemi);
            tabel->setItem(1, k, itemi2);
            k++;   
        }
    }

};

