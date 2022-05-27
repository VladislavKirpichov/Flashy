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

}

StartPage::~StartPage()
{
    delete ui;
}

void StartPage::open_window()
{
    main_window->hide();
    main_window->open_page(4);
    this->show();
}

void StartPage::on_reg_button_clicked()
{
    hide();
    reg_page = new regpage(this);
    reg_page->show();
}
void StartPage::connection()
{
    main_window = new MainWindow(this);
    main_window->hide();
    user_page = main_window->get_page();
    connect(user_page, &UserPage::exit_signal, this, &StartPage::open_window);
}

void StartPage::on_sign_up_button_clicked()
{
    std::string login = ui->login->text().toStdString();
    std::string pass = ui->pass->text().toStdString();
    if(Manager::get_instance()->auth(login, pass)){
        hide();
        Manager::get_instance()->get_user_from_server(login);
        connection();
        main_window->update();
        main_window->show();
    } else {
        QMessageBox::information(this, "Auth error", "Uncorrent Login or password");
    }
}

