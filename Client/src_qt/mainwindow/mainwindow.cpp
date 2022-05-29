#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Manager.h"
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
    connect(test_page, &TestPage::open_page_signal, this, &MainWindow::open_page);

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

    edit_page = new EditPage(this);
    edit_page->hide();
    connect(this, &MainWindow::signal, edit_page, &EditPage::open_page);
    connect(edit_page, &EditPage::open_page_signal, this, &MainWindow::open_page);

    connect(edit_page, &EditPage::save_page_signal, custom_page, &CustomPage::save_text);


    connect(this, &MainWindow::user_signal, user_page, &UserPage::update);
    connect(main_page, &MainPage::update_custom_page_signal, this, &MainWindow::update_custom_page_slot);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete user_page;
    delete main_page;
    delete custom_page;
    delete recom_page;
    delete test_page;
    delete edit_page;
}

UserPage *MainWindow::get_page()
{
    return user_page;
}

void MainWindow::update()
{
    QString _name = (Manager::get_instance()->get_user().get_name()).c_str();
    QString _login = (Manager::get_instance()->get_user().get_login()).c_str();
    QString _password = (Manager::get_instance()->get_user().get_password()).c_str();

    ui->user_button->setText(_name);
    emit user_signal(_name, _login, _password);
}

void MainWindow::open_page(int page_num)
{
    emit signal(page_num);
}

void MainWindow::update_custom_page_slot()
{
    custom_page->update();
}


void MainWindow::on_user_button_clicked()
{
    emit signal(5);
}

void MainWindow::on_flashy_button_clicked()
{
    update();
    emit signal(4);
}
