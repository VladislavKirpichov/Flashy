#include "startpage.h"
#include "ui_startpage.h"
#include "Manager.h"
#include <QMessageBox>
#include <QHBoxLayout>
StartPage::StartPage(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::StartPage)
{
    ui->setupUi(this);
    main_window = new MainWindow(this);
    reg_page = new regpage(this);

}

StartPage::~StartPage()
{
    delete ui;
    delete main_window;
    delete reg_page;
    delete user_page;
}

void StartPage::open_window()
{
    main_window->hide();
    main_window->open_page(4);
    this->show();
}

void StartPage::reg_slot()
{
    hide();
    connection();
    main_window->update();
    main_window->show();
}

void StartPage::on_reg_button_clicked()
{
    hide();
    reg_page->show();
    connect(reg_page, &regpage::reg_signal, this, &StartPage::reg_slot);
}
void StartPage::connection()
{
    main_window->hide();
    user_page = main_window->get_page();
    connect(user_page, &UserPage::exit_signal, this, &StartPage::open_window);
}

void StartPage::on_sign_up_button_clicked()
{
    std::string login = ui->login->text().toStdString();
    std::string pass = ui->pass->text().toStdString();
    if(true){
//    if(Manager::get_instance()->auth(login, pass)){
//        Manager::get_instance()->get_user_from_server(login, pass);
        hide();
        connection();
        main_window->update();
        main_window->show();
    } else {
        QMessageBox::information(this, "Auth error", "Uncorrent Login or password");
    }
}

