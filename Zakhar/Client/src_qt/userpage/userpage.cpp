#include "userpage.h"
#include "ui_userpage.h"

UserPage::UserPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserPage)
{
    ui->setupUi(this);
    this->move(100,0);
    page_num = 5;
}

UserPage::~UserPage()
{
    delete ui;
}

void UserPage::open_page(int _page_num)
{
    if(page_num == _page_num){
        this->show();
    } else {
        this->hide();
    }
}



void UserPage::on_exit_button_clicked()
{

}
