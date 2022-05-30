#include "mainpage.h"
#include "ui_mainpage.h"
#include "Manager.h"
#include <QInputDialog>
#include <QComboBox>
MainPage::MainPage(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::MainPage) {
    ui->setupUi(this);
    this->move(100, 0);
    page_num = 4;
    std::vector<std::string> pages_title = Manager::get_instance()->get_user().get_pages_titles();
    for (int i = 0; i < pages_title.size(); i++){
        note_buttons.push_back(new NoteButton(this, pages_title[i], i));
        connect(note_buttons[i], &NoteButton::open_custom_page_signal, this, &MainPage::open_custom_page);
    }
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

void MainPage::open_custom_page(int note_num)
{
   // Manager::get_instance()->get_page_from_server(Manager::get_instance()->get_user().get_pages_id()[note_num]);
    emit update_custom_page_signal();
    emit open_page_signal(3);
}

void MainPage::on_add_page_button_clicked() {
    QString text = QInputDialog::getText(this, tr("Creating page"),
                                         tr("Page title: "), QLineEdit::Normal);

    if(Manager::get_instance()->create_page_to_server(text.toStdString())) {
        emit open_page_signal(6);
    }
}
