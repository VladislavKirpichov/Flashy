#include "questionfield.h"
#include "ui_questionfield.h"

QuestionFIeld::QuestionFIeld(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QuestionFIeld)
{
    ui->setupUi(this);
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
