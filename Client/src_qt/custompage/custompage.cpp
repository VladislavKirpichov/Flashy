#include "custompage.h"
#include "ui_custompage.h"

CustomPage::CustomPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CustomPage)
{
    ui->setupUi(this);
    page_num = 3;
    this->move(100,0);
    update();

}

CustomPage::~CustomPage()
{
    delete ui;
}

void CustomPage::update()
{
    question_fields.clear();
    QString _text = (Manager::get_instance()->get_page().get_text()).c_str();
    QString _title = (Manager::get_instance()->get_page().get_title()).c_str();
    QString _created = (Manager::get_instance()->get_page().get_created_time()).c_str();
    QString _last_visited = (Manager::get_instance()->get_page().get_last_visited_time()).c_str();
    ui->page_title->setText(_title);
    ui->text_field->setText(_text);
    ui->created_time_title->setText(_created);
    ui->last_visited_time_title->setText(_last_visited);
    for(int i=0; i< Manager::get_instance()->get_page().get_questions_id().size();i++){
        QuestionEditor *q = new QuestionEditor(this);
        std::string title= Manager::get_instance()->get_questions()[i].get_title();
        std::string answer= Manager::get_instance()->get_questions()[i].get_answer();
        q->set_data(title, answer);
        question_fields.push_back(q);
        question_fields[i]->move(80,350+ 100*(i+1));
        question_fields[i]->show();
    }

}

void CustomPage::open_page(int _page_num)
{
    if(page_num == _page_num){
        update();
        this->show();
    } else {
        this->hide();
    }
}


void CustomPage::on_recom_notes_button_clicked()
{
    emit open_page_signal(1);
}

void CustomPage::on_start_testing_button_clicked()
{
    emit open_page_signal(2);
}


void CustomPage::on_save_button_clicked()
{
    QString _text = ui->text_field->toPlainText();
    QString _title = ui->page_title->text();
    Manager::get_instance()->get_page().set_text(_text.toStdString());
    Manager::get_instance()->get_page().set_title(_title.toStdString());
    for(int i=0; i< Manager::get_instance()->get_page().get_questions_id().size();i++){
        QString quest_title = question_fields[i]->get_question();
        QString quest_answer = question_fields[i]->get_answer();
        Manager::get_instance()->get_questions()[i].set_title(quest_title.toStdString());
        Manager::get_instance()->get_questions()[i].set_answer(quest_answer.toStdString());
    }
        for(int i=Manager::get_instance()->get_page().get_questions_id().size(); i<question_fields.size(); ++i){
            QString quest_title = question_fields[i]->get_question();
            QString quest_answer = question_fields[i]->get_answer();
            Manager::get_instance()->get_questions().emplace_back(Question(Manager::get_instance()->get_page().get_id()));
            Manager::get_instance()->get_questions()[i].set_title(quest_title.toStdString());
            Manager::get_instance()->get_questions()[i].set_answer(quest_answer.toStdString());
        }
        Manager::get_instance()->change_page_in_server();
}

void CustomPage::on_add_question_button_clicked()
{
    std::string page_id = Manager::get_instance()->get_page().get_page_id();
    std::string str = Manager::get_instance()->create_question_to_server();
    std::cout << str << "\n";
    int question_id = std::stoi(str);
    Manager::get_instance()->get_page().get_questions_id().emplace_back(question_id);
    Manager::get_instance()->get_questions().emplace_back(Manager::get_instance()->get_question_from_server(question_id));
    update();
}
