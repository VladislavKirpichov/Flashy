#include "notebutton.h"

NoteButton::NoteButton(QWidget *parent) :
    QPushButton(parent)
{
    buttons_count++;
    button_ID = buttons_count - 1;
    move(100 + (button_ID % 3) * 150, 50 + (button_ID / 3) * 50);
    std::string name = Manager::get_instance()->get_user().get_notes_name()[button_ID];
    this->setText(name.c_str());
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
