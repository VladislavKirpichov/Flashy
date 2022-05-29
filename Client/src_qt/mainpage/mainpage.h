#ifndef MAINPAGE_H
#define MAINPAGE_H

#include <QWidget>
#include "notebutton.h"
namespace Ui {
class MainPage;
}

class MainPage : public QWidget
{
    Q_OBJECT

public:
    explicit MainPage(QWidget *parent = nullptr);
    ~MainPage();

public slots:
    void open_page(int _page_num);
    void open_custom_page(int note_num);
private slots:
    void on_add_page_button_clicked();
private:
    Ui::MainPage *ui;
    int page_num;
    QList<NoteButton*> note_buttons;
signals:
    void open_page_signal(int);
    void update_custom_page_signal();
};

#endif // MAINPAGE_H
