#include "mainpage.h"
#include "ui_mainpage.h"
#include "Manager.h"
MainPage::MainPage(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::MainPage) {
    ui->setupUi(this);
    this->move(100, 0);
    page_num = 4;
    std::vector<std::string> pages_title = Manager::get_instance()->get_user().get_pages_title();
    for (int i = 0; i < pages_title.size(); i++)
        note_buttons.push_back(new NoteButton(this, pages_title[i]));
}

MainPage::~MainPage() {
    delete ui;
}

void MainPage::open_page(int _page_num) {
    if (page_num == _page_num) {
        this->show();
    } else {
        this->hide();
    }
}

void MainPage::on_add_page_button_clicked() {
    emit open_page_signal(3);
}

void MainPage::on_custom_page_button_clicked() {
    emit open_page_signal(3);
}
