#ifndef MAINPAGE_H
#define MAINPAGE_H

#include <QWidget>
#include "custompage.h"
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
    void on_pushButton_6_clicked();

    void on_pushButton_9_clicked();

private:
    Ui::MainPage *ui;
    CustomPage * custom_page;
};

#endif // MAINPAGE_H
