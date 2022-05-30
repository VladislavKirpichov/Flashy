#include "testpage.h"
#include "ui_testpage.h"


TestPage::TestPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TestPage),
    result(0)
{
    ui->setupUi(this);
    this->move(100,0);
    page_num = 2;
    update();
}

TestPage::~TestPage()
{
    delete ui;
}
void TestPage::update()
{
    result = 0;
    question_fields.clear();
    QString _title = (Manager::get_instance()->get_page().get_title()).c_str();
    ui->page_title->setText(_title);
    for(int i=0; i< Manager::get_instance()->get_page().get_questions_id().size();i++){
        QuestionFIeld *q = new QuestionFIeld(this);
        std::string title= Manager::get_instance()->get_questions()[i].get_title();
        std::string answer= Manager::get_instance()->get_questions()[i].get_answer();
        q->set_data(title, answer);
        question_fields.push_back(q);
        question_fields[i]->move(80,350+ 100*(i+1));
        connect(question_fields[i], &QuestionFIeld::answer_signal, this, &TestPage::answer_slot);
    }

}
void TestPage::open_page(int _page_num)
{
    if(page_num == _page_num){
        update();
        this->show();
    } else {
        this->hide();
    }
}

void TestPage::answer_slot(bool res)
{
    if(res)
        result++;
}

void TestPage::on_end_test_button_clicked()
{
    double proc = (int)((result/question_fields.size())*100);
    QString str_res = QString::number(proc) + "%";
    QMessageBox::information(this, "Result", str_res);
    emit open_page_signal(3);
}
