#include "lab10.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qformlayout.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qlistwidget.h>
#include "GUIapp.h"

void testAll() {
    testProd();
    testRepo();
    testService();
    testExporta();
    testUndo();
    testRepoLab();
    testFileRepo();
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    testAll();
    repo_file rep{ "produse.txt" };
    service serv{ rep };
    GUIapp gw{ serv };
    gw.show();
    

    /*QWidget w{};
    QHBoxLayout* lymain = new QHBoxLayout{};
    w.setLayout(lymain);

    auto st = new QVBoxLayout{};
    auto lista = new QListWidget;
    lymain->addWidget(lista);
    auto ly2 = new QFormLayout;
    ly2->addRow("Nume", new QLineEdit);
    ly2->addRow("Tip", new QLineEdit);
    ly2->addRow("Pret", new QLineEdit);
    ly2->addRow("Producator", new QLineEdit);
    st->addLayout(ly2);
    auto listaButoane = new QHBoxLayout{};
    listaButoane->addWidget(new QPushButton{ "Add" });
    listaButoane->addWidget(new QPushButton{ "Add" });
    listaButoane->addWidget(new QPushButton{ "Add" });
    st->addLayout(listaButoane);
    lymain->addLayout(st);
    w.show();*/


    return a.exec();
}
