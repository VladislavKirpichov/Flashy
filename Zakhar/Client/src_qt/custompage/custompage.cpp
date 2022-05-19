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

void CustomPage::on_Similar_notes_button_clicked()
{
    this->hide();
    recom_page->show();
}

void CustomPage::on_start_testing_button_clicked()
{
    this->hide();
    test_page->show();
}
