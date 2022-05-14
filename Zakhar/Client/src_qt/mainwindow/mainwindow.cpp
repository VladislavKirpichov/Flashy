#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    recom_page = new RecomPage(this);
    recom_page->move(100,0);
    recom_page->hide();

    test_page = new TestPage(this);
    test_page->move(100,0);
    test_page->hide();

    custom_page = new CustomPage(this, recom_page, test_page);
    custom_page->move(100,0);
    custom_page->hide();

    main_page = new MainPage(this, custom_page);
    main_page->move(100,0);
    main_page->show();

    user_page = new UserPage(this);
    user_page->move(100,0);
    user_page->hide();


    this->show();


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_13_clicked()
{
      recom_page->hide();
      main_page->hide();
      user_page->show();
}

void MainWindow::on_pushButton_6_clicked()
{
    recom_page->hide();
    user_page->hide();
    main_page->show();
}
