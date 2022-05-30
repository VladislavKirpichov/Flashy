#include "questioneditor.h"
#include "ui_questioneditor.h"

QuestionEditor::QuestionEditor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QuestionEditor),
    is_hide(true)
{
    ui->setupUi(this);
    ui->answer->setEchoMode(QLineEdit::Password);

}

QuestionEditor::~QuestionEditor()
{
    delete ui;
}

void QuestionEditor::set_data(const std::string &new_title, const std::string &new_answer)
{
      ui->question->setText(new_title.c_str());
        ui->answer->setText(new_answer.c_str());
}

void QuestionEditor::on_save_button_clicked()
{
    std::string question = ui->question->text().toStdString();
    std::string answer = ui->answer->text().toStdString();
}

void QuestionEditor::on_hide_button_clicked()
{
    if(is_hide)
        ui->answer->setEchoMode(QLineEdit::Normal);
    else {
        ui->answer->setEchoMode(QLineEdit::Password);
    }
    is_hide = !is_hide;
}
QString QuestionEditor::get_question(){
    return ui->question->text();
}
QString QuestionEditor::get_answer(){
    return ui->answer->text();
}
