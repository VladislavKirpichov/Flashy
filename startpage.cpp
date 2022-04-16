#include "startpage.h"
#include "ui_startpage.h"
#include <QMessageBox>
StartPage::StartPage(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::StartPage)
{
    ui->setupUi(this);
}

StartPage::~StartPage()
{
    delete ui;
}


void StartPage::on_pushButton_clicked()
{
    QString login = ui->login->text();
    QString pass = ui->pass->text();
    if(login == "Zakhar" && pass == "123"){
        hide();
        main_page = new MainWindow(this);
        main_page->show();
    } else {
        QMessageBox::information(this, "Auth error", "Uncorrent Login or password");
    }

}
