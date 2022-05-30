#include "notebutton.h"

NoteButton::NoteButton(QWidget *parent, const std::string & name_str, const int & num) :
    QPushButton(parent)
{
    button_num = num;
    setFixedSize(120,120);
    move(80 + (button_num % 3) * 130, 140 + (button_num / 3) * 140);
    this->setText(name_str.c_str());
    this->show();
    connect(this, &QPushButton::clicked, this, &NoteButton::open_custom_page_slot);
}

NoteButton::~NoteButton()
{

}

int NoteButton::get_ID()
{
    return button_num;
}

void NoteButton::open_custom_page_slot(int ID)
{
    emit open_custom_page_signal(ID);
}

