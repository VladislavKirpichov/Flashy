#ifndef STARTPAGE_H
#define STARTPAGE_H

#include <QMainWindow>
#include "mainwindow.h"
#include "regpage.h"
QT_BEGIN_NAMESPACE
namespace Ui { class StartPage; }
QT_END_NAMESPACE

class StartPage : public QMainWindow
{
    Q_OBJECT

public:
    StartPage(QWidget *parent = nullptr);
    ~StartPage();

private slots:
    void on_pushButton_clicked();

    void on_reg_button_clicked();

private:
    Ui::StartPage *ui;
    MainWindow * main_window;
    regpage * reg_page;

};
#endif // STARTPAGE_H
