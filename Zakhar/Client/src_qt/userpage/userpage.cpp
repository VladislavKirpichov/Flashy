#include "userpage.h"
#include "ui_userpage.h"

UserPage::UserPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserPage)
{
    ui->setupUi(this);
}

UserPage::~UserPage()
{
    delete ui;
}



void UserPage::on_exit_button_clicked()
{

}
