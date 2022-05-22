#include "testpage.h"
#include "ui_testpage.h"

TestPage::TestPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TestPage)
{
    ui->setupUi(this);
    this->move(100,0);
    page_num = 2;
}

TestPage::~TestPage()
{
    delete ui;
}

void TestPage::open_page(int _page_num)
{
    if(page_num == _page_num){
        this->show();
    } else {
        this->hide();
    }
}

void TestPage::on_end_test_button_clicked()
{

}
