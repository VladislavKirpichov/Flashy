#include "notebutton.h"

NoteButton::NoteButton(QWidget *parent, const std::string & name_str) :
    QPushButton(parent)
{
    button_ID = buttons_count++;
    setFixedSize(120,120);
    move(80 + (button_ID % 3) * 130, 140 + (button_ID / 3) * 140);
    this->setText(name_str.c_str());
    this->show();
    connect(this, &QPushButton::clicked, this, &NoteButton::open_custom_page_slot);
}

NoteButton::~NoteButton()
{
    buttons_count--;
}

int NoteButton::get_ID()
{
    return button_ID;
}

void NoteButton::open_custom_page_slot(int ID)
{
    emit open_custom_page_signal(ID);
}

int NoteButton::buttons_count = 0;
