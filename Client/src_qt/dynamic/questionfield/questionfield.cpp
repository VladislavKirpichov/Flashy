#include "questionfield.h"
#include "ui_questionfield.h"

QuestionFIeld::QuestionFIeld(QWidget *parent, bool is_yours) :
    QWidget(parent),
    ui(new Ui::QuestionFIeld)
{
    ui->setupUi(this);
    if(is_yours){
        ui->like_button->hide();
        ui->dislike_button->hide();
        ui->answer_button->setFixedSize(168,50);
    }
}

QuestionFIeld::~QuestionFIeld()
{
    delete ui;
}

void QuestionFIeld::on_like_button_clicked()
{

}

void QuestionFIeld::on_dislike_button_clicked()
{

}

void QuestionFIeld::on_answer_button_clicked()
{

}

void QuestionFIeld::set_title(const std::string &new_title)
{
     ui->question->setText(new_title.c_str());
}
