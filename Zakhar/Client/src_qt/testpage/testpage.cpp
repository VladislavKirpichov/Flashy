#include "testpage.h"
#include "ui_testpage.h"

TestPage::TestPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TestPage)
{
    ui->setupUi(this);
}

TestPage::~TestPage()
{
    delete ui;
}

void TestPage::on_end_test_button_clicked()
{

}
