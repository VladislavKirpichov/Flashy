#include "mainpage.h"
#include "ui_mainpage.h"
#include "custompage.h"

MainPage::MainPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainPage)
{
    ui->setupUi(this);

}
MainPage::MainPage(QWidget *parent, CustomPage * custom):
    QWidget(parent),
    ui(new Ui::MainPage)
{
    ui->setupUi(this);
    custom_page = custom;
    custom_page->hide();
    this->move(100,0);
}

MainPage::~MainPage()
{
    delete ui;
}



void MainPage::on_add_page_button_clicked()
{
    hide();
    custom_page->show();
}

void MainPage::on_custom_page_button_clicked()
{
    hide();
    custom_page->show();
}
