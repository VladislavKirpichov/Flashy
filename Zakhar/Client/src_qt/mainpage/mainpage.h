#ifndef MAINPAGE_H
#define MAINPAGE_H

#include <QWidget>
#include "page.h"
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
private slots:
    void on_add_page_button_clicked();

    void on_custom_page_button_clicked();

private:
    Ui::MainPage *ui;
    int page_num;
signals:
    void open_page_signal(int);
};

#endif // MAINPAGE_H
