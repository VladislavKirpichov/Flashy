#include "startpage.h"
#include "ui_startpage.h"
#include <QMessageBox>
#include <QHBoxLayout>
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

void StartPage::on_reg_button_clicked()
{
    hide();
    reg_page = new regpage(this);
    reg_page->show();
}

void StartPage::on_sign_up_button_clicked()
{
    QString login = ui->login->text();
    QString pass = ui->pass->text();
    if(true){
        hide();
        main_window = new MainWindow(this);
        main_window->show();
    } else {
        QMessageBox::information(this, "Auth error", "Uncorrent Login or password");
    }
}
