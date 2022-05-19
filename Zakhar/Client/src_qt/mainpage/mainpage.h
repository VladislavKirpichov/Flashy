#ifndef MAINPAGE_H
#define MAINPAGE_H

#include <QWidget>
#include "custompage.h"
#include "page.h"
namespace Ui {
class MainPage;
}

class MainPage : public QWidget
{
    Q_OBJECT

public:
    explicit MainPage(QWidget *parent = nullptr);
    explicit MainPage(QWidget *parent = nullptr, CustomPage * custom = nullptr);
    ~MainPage();

private slots:
    void on_add_page_button_clicked();

    void on_custom_page_button_clicked();

private:
    Ui::MainPage *ui;
    CustomPage * custom_page;
};

#endif // MAINPAGE_H
