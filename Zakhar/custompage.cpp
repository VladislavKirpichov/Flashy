#include "custompage.h"
#include "ui_custompage.h"

CustomPage::CustomPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CustomPage)
{
    ui->setupUi(this);
}
CustomPage::CustomPage(QWidget *parent, RecomPage * recom) :
    QWidget(parent),
    ui(new Ui::CustomPage)
{
    ui->setupUi(this);
    recom_page = recom;
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
