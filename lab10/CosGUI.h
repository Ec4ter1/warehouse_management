#pragma once
#include <qwidget.h>
#include <qtimer.h>
#include <QtWidgets/QHBoxLayout>
#include <qpushbutton.h>
#include <qlistwidget.h>
#include <qtablewidget.h>
#include <qstring.h>
#include <qlabel.h>
#include <vector>
#include "service.h"
#include "observer.h"
#include <qlineedit.h>
#include <qboxlayout.h>
#include <qformlayout.h>
#include <qmessagebox.h>

class CosGUICuLista :public QWidget, public Observer {
public:
    CosGUICuLista(service& serv, Cos& cosulet) :cosulet{ cosulet }, serv{ serv } {
        initGUI();
        connect();
        cosulet.addObserver(this);
        loadData(cosulet.lista());
    }

    void update() override {
        loadData(cosulet.lista());
    }

    ~CosGUICuLista() {
        cosulet.removeObserver(this);
    }

private:
    service& serv;
    Cos& cosulet;

    QListWidget* l = new QListWidget;
    QPushButton* AddCos = new QPushButton{ "Adauga cos" };
    QPushButton* GolCos = new QPushButton{ "Goleste cos" };
    QPushButton* AddRandCos = new QPushButton{ "Adauga random cos" };
    QLineEdit* Nume = new QLineEdit;

    void addCosGUI();
    void GolCosGUI();
    void AddRandCosGUI();

    void initGUI() {
        QHBoxLayout* lymain = new QHBoxLayout{};
        setLayout(lymain);

        auto st = new QVBoxLayout{};
        //auto lista = new QListWidget;
        auto ly1 = new QFormLayout;
        ly1->addWidget(l);
        auto listaButoane3 = new QHBoxLayout{};
        listaButoane3->addWidget(AddCos);
        listaButoane3->addWidget(GolCos);
        listaButoane3->addWidget(AddRandCos);
        /*listaButoane3->addWidget(ExportHTML);
        listaButoane3->addWidget(ExportCVS);*/
        ly1->addRow(listaButoane3);
        ly1->addRow("Nume", Nume);
        lymain->addLayout(ly1);
    }

    void connect() {

        QObject::connect(AddCos, &QPushButton::clicked, [&]() {
            addCosGUI();
            });

        QObject::connect(GolCos, &QPushButton::clicked, [&]() {
            GolCosGUI();
            });

        QObject::connect(AddRandCos, &QPushButton::clicked, [&]() {
            AddRandCosGUI();
            });
    }

    void loadData(vector<Prod> produse)
    {
        l->clear();
        for (auto& p : produse) {
            string o = p.get_nume() + "  " + p.get_tip() + "  " + std::to_string(p.get_pret()) + "  " + p.get_produc();
            QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(o), l);
            item->setData(Qt::UserRole, QString::fromStdString(o));
            item->setData(Qt::BackgroundRole, QBrush{ Qt::blue, Qt::BDiagPattern });
            l->addItem(item);
        }

    }

};