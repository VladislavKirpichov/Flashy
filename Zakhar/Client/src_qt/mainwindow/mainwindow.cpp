#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    recom_page = new RecomPage(this);
    recom_page->hide();
    connect(this, &MainWindow::signal, recom_page, &RecomPage::open_page);

    test_page = new TestPage(this);
    test_page->hide();
    connect(this, &MainWindow::signal, test_page, &TestPage::open_page);

    custom_page = new CustomPage(this);
    custom_page->hide();
    connect(this, &MainWindow::signal, custom_page, &CustomPage::open_page);
    connect(custom_page, &CustomPage::open_page_signal, this, &MainWindow::open_page);

    main_page = new MainPage(this);
    main_page->show();
    connect(this, &MainWindow::signal, main_page, &MainPage::open_page);
    connect(main_page, &MainPage::open_page_signal, this, &MainWindow::open_page);

    user_page = new UserPage(this);
    user_page->hide();
    connect(this, &MainWindow::signal, user_page, &UserPage::open_page);


    this->show();


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::open_page(int page_num)
{
    emit signal(page_num);
}


void MainWindow::on_user_button_clicked()
{
    emit signal(5);
}

void MainWindow::on_flashy_button_clicked()
{
    emit signal(4);
}
