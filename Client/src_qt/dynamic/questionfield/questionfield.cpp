#include "questionfield.h"
#include "ui_questionfield.h"

QuestionFIeld::QuestionFIeld(QWidget *parent, bool is_yours) :
    QWidget(parent),
    ui(new Ui::QuestionFIeld),
    is_clicked(false)
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
   if( ui->answer_line->text() == answer && !is_clicked){
    emit answer_signal(true);
   }else{
       emit answer_signal(false);
       is_clicked = true;
   }
}

void QuestionFIeld::set_data(const std::string &new_title, const std::string &new_answer)
{
        ui->question->setText(new_title.c_str());
        answer = new_answer.c_str();
}
