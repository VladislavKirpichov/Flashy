#include "mainpage.h"
#include "ui_mainpage.h"
#include "custompage.h"

MainPage::MainPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainPage)
{
    ui->setupUi(this);

}
MainPage::MainPage(QWidget *parent, CustomPage * custom) :
    QWidget(parent),
    ui(new Ui::MainPage)
{
    ui->setupUi(this);
    custom_page = custom;
    custom_page->hide();
}

MainPage::~MainPage()
{
    delete ui;
}

void MainPage::on_pushButton_6_clicked()
{
    hide();
    custom_page->show();
}

void MainPage::on_pushButton_9_clicked()
{

}
