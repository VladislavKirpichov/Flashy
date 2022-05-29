#include "custompage.h"
#include "ui_custompage.h"

CustomPage::CustomPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CustomPage)
{
    ui->setupUi(this);
    page_num = 3;
    this->move(100,0);

}

CustomPage::~CustomPage()
{
    delete ui;
}

void CustomPage::update()
{
    QString _text = (Manager::get_instance()->get_page().get_text()).c_str();
    QString _title = (Manager::get_instance()->get_page().get_title()).c_str();
    QString _created = (Manager::get_instance()->get_page().get_created_time()).c_str();
    QString _last_visited = (Manager::get_instance()->get_page().get_last_visited_time()).c_str();
    ui->page_title->setText(_title);
    ui->text_field->setText(_text);
    ui->created_time_title->setText(_created);
    ui->last_visited_time_title->setText(_last_visited);

}

void CustomPage::open_page(int _page_num)
{
    if(page_num == _page_num){
        this->show();
    } else {
        this->hide();
    }
}

void CustomPage::save_text(QString new_text)
{
    ui->text_field->setText(new_text);
}

void CustomPage::on_recom_notes_button_clicked()
{
    emit open_page_signal(1);
}

void CustomPage::on_start_testing_button_clicked()
{
    emit open_page_signal(2);
}

void CustomPage::on_edit_button_clicked()
{
    emit open_page_signal(6);
}
