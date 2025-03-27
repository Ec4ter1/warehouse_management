#pragma once
#include <QAbstractTableModel>
#include "produs.h"
#include <vector>
#include <qdebug.h>

using namespace std;

class TableModel : public QAbstractTableModel {
	std::vector<Prod> produse;
public:
	TableModel(const std::vector<Prod>& produse) : produse{ produse } {
	}

	int rowCount(const QModelIndex& parent = QModelIndex()) const override {
		return produse.size();
	}
	int columnCount(const QModelIndex& parent = QModelIndex()) const override {
		return 4;
	}

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
		qDebug() << "row:" << index.row() << " col:" << index.column() << " role" << role;
		if (role == Qt::DisplayRole) {
			Prod p = produse[index.row()];
			if (index.column() == 0) {
				return QString::fromStdString(p.get_nume());
			}
			else if (index.column() == 1) {
				return QString::fromStdString(p.get_tip());
			}
			else if (index.column() == 2) {
				return QString::number(p.get_pret());
			}
			else if (index.column() == 3) {
				return QString::fromStdString(p.get_produc());
			}
		}

		return QVariant{};
	}

	/*void setproduse(const vector<Prod>& produse) {
		this->produse = produse;
		auto topLeft = createIndex(0, 0);
		auto bottomR = createIndex(rowCount(), columnCount());
		emit dataChanged(topLeft, bottomR);
	}*/
};