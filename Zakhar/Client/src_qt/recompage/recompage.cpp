#include "recompage.h"
#include "ui_recompage.h"

RecomPage::RecomPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RecomPage)
{
    ui->setupUi(this);
    this->move(100,0);
    page_num = 1;
}

RecomPage::~RecomPage()
{
    delete ui;
}

void RecomPage::open_page(int _page_num)
{
    if(page_num == _page_num){
        this->show();
    } else {
        this->hide();
    }
}
