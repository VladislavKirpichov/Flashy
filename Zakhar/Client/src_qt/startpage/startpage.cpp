#include "startpage.h"
#include <iostream>
#include "ui_startpage.h"
#include <QMessageBox>
#include <QHBoxLayout>
StartPage::StartPage(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::StartPage)
{
    ui->setupUi(this);
//    QPushButton * buttons[10];
//    QHBoxLayout* hboxLayoutPtr=new QHBoxLayout;
//    for(int i=0; i<10; i++){
//        buttons[i] = new QPushButton;
//        hboxLayoutPtr->addWidget(buttons[i]);
//        buttons[i]->setText("Hm"+ QString::number(i+1));
//        buttons[i]->move(50,50+10*i);
//        buttons[i]->show();
//    }

}

StartPage::~StartPage()
{
    delete ui;
}


void StartPage::on_pushButton_clicked()
{
    QString login = ui->login->text();
    QString pass = ui->pass->text();
    if(true){
        hide();
        main_window = new MainWindow(this);
        main_window->show();
        std::cout << "Hello";
    } else {
        QMessageBox::information(this, "Auth error", "Uncorrent Login or password");
    }

}

void StartPage::on_reg_button_clicked()
{
    hide();
    reg_page = new regpage(this);
    reg_page->show();
}
