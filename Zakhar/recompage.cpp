#include "recompage.h"
#include "ui_recompage.h"

RecomPage::RecomPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RecomPage)
{
    ui->setupUi(this);
}

RecomPage::~RecomPage()
{
    delete ui;
}
