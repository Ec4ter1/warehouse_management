#pragma once

#include <qwidget.h>
#include <qpainter.h>
#include "cos.h"
#include "qdebug.h"

class CosDesen : public QWidget, public Observer
{
private:
	Cos& cosulet;
public:
	CosDesen(Cos& cosulet) : cosulet{ cosulet } {
		cosulet.addObserver(this);
	};

	void update() override {
		repaint();
	}

	void paintEvent(QPaintEvent* ev) override {
		QPainter p{ this };
		srand(time(NULL));
		for (const auto& u : cosulet.lista()) {
			int x = rand() % 400;
			int y = rand() % 400;
			qDebug() << x << " " << y << '\n';
			p.drawRect(x, y, 40, u.get_pret());
		}

	}
};