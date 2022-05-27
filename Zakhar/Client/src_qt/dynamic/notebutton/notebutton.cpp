#include "notebutton.h"

NoteButton::NoteButton(QWidget *parent, const std::string & name_str) :
    QPushButton(parent)
{
    buttons_count++;
    button_ID = buttons_count - 1;
    setFixedSize(120,120);
    move(80 + (button_ID % 3) * 130, 140 + (button_ID / 3) * 140);
    this->setText(name_str.c_str());
    this->show();

}

NoteButton::~NoteButton()
{
    buttons_count--;
}

int NoteButton::get_ID()
{
    return button_ID;
}

int NoteButton::buttons_count = 0;