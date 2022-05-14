#include "custompage.h"
#include "ui_custompage.h"

CustomPage::CustomPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CustomPage)
{
    ui->setupUi(this);
}
CustomPage::CustomPage(QWidget *parent, RecomPage * recom, TestPage * test) :
    QWidget(parent),
    ui(new Ui::CustomPage)
{
    ui->setupUi(this);
    recom_page = recom;
    test_page = test;
}

CustomPage::~CustomPage()
{
    delete ui;
}

void CustomPage::on_pushButton_2_clicked()
{
    this->hide();
    recom_page->show();
}

void CustomPage::on_pushButton_clicked()
{
    this->hide();
    test_page->show();
}
