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
