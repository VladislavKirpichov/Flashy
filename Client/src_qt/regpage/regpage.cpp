#include "regpage.h"
#include "ui_regpage.h"

regpage::regpage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::regpage)
{
    ui->setupUi(this);
}

regpage::~regpage()
{
    delete ui;
}

void regpage::on_create_acc_button_clicked()
{
    std::string login = ui->login->text().toStdString();
    std::string name = ui->name->text().toStdString();
    std::string email = ui->email->text().toStdString();
    std::string pass = ui->pass->text().toStdString();
    std::string repeat_pass = ui->repeat_pass->text().toStdString();
    if(pass == repeat_pass){
        if(Manager::get_instance()->reg(name, login, pass, email)){
            Manager::get_instance()->get_user() = User(name, login, pass,email);
            Manager::get_instance()->get_user_from_server(login,pass);
            std::cout <<  Manager::get_instance()->get_user().get_id() << "\n";
            hide();
            emit reg_signal();
        } else {
            QMessageBox::information(this, "Reg error", "Registration Error");
        }
    } else {
         QMessageBox::information(this, "Reg error", "Password mismatch");
    }
}
