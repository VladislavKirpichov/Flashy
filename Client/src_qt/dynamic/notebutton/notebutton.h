#ifndef NOTEBUTTON_H
#define NOTEBUTTON_H

#include <QPushButton>

class NoteButton : public QPushButton
{
    Q_OBJECT
public:
    NoteButton(QWidget *parent = nullptr, const std::string & name_str = "");
    ~NoteButton();
    static int buttons_count;   // Статическая переменная, счетчик номеров кнопок
    int get_ID();        // Функция для возврата локального номера кнопки
public slots:
    void open_custom_page_slot(int ID);
private:
        int button_ID = 0;
        QString note_name;
signals:
        void open_custom_page_signal(int);
};

#endif // NOTEBUTTON_H
