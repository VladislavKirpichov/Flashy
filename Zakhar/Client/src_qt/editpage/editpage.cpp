#include "editpage.h"
#include "ui_editpage.h"

EditPage::EditPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EditPage)
{
    ui->setupUi(this);
    page_num = 6;
    this->move(100,0);
}

EditPage::~EditPage()
{
    delete ui;
}

void EditPage::open_page(int _page_num)
{
    if(page_num == _page_num){
        this->show();
    } else {
        this->hide();
    }
}

void EditPage::on_save_text_button_clicked()
{
    emit save_text_signal(ui->text_field->toPlainText());
}

void EditPage::on_exit_button_clicked()
{
    emit open_page_signal(3);
}
