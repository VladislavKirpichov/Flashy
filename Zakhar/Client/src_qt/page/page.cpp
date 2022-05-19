#include "page.h"
#include "ui_page.h"

Page::Page(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Page)
{
    ui->setupUi(this);
    this->move(100,0);
}

Page::~Page()
{
    delete ui;
}
