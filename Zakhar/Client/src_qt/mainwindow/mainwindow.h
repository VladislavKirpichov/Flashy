#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialog>
#include <QStackedWidget>
#include "mainpage.h"
#include "userpage.h"
#include "custompage.h"
#include "recompage.h"
#include "testpage.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QDialog
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_13_clicked();

    void on_pushButton_6_clicked();

private:
    Ui::MainWindow *ui;
    UserPage * user_page;
    MainPage * main_page;
    CustomPage * custom_page;
    RecomPage * recom_page;
    TestPage * test_page;
};

#endif // MAINWINDOW_H
