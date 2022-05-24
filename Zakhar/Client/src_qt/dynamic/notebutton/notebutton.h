#ifndef NOTEBUTTON_H
#define NOTEBUTTON_H

#include <QPushButton>
#include "Manager.h"

class NoteButton : public QPushButton
{
    Q_OBJECT
public:
    explicit NoteButton(QWidget *parent = nullptr);
    ~NoteButton();
    static int buttons_count;   // Статическая переменная, счетчик номеров кнопок
    int get_ID();        // Функция для возврата локального номера кнопки

private:
        int button_ID = 0;
        QString note_name;
};

#endif // NOTEBUTTON_H
