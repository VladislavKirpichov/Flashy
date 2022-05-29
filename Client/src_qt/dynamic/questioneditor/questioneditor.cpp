#include "questioneditor.h"
#include "ui_questioneditor.h"

QuestionEditor::QuestionEditor(QWidget *parent, size_t _index) :
    QWidget(parent),
    ui(new Ui::QuestionEditor),
    is_hide(false),
    index(_index)
{
    ui->setupUi(this);
}

QuestionEditor::~QuestionEditor()
{
    delete ui;
}

void QuestionEditor::on_save_button_clicked()
{
    std::string question = ui->question_edit->text().toStdString();
    std::string answer = ui->answer_edit->text().toStdString();
}

void QuestionEditor::on_hide_button_clicked()
{
    if(is_hide)
        ui->answer_edit->setEchoMode(QLineEdit::Normal);
    else {
        ui->answer_edit->setEchoMode(QLineEdit::Password);
    }
    is_hide = !is_hide;
}
