#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_lab10.h"

class lab10 : public QMainWindow
{
    Q_OBJECT

public:
    lab10(QWidget *parent = nullptr);
    ~lab10();

private:
    Ui::lab10Class ui;
};
