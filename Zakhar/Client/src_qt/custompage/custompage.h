#ifndef CUSTOMPAGE_H
#define CUSTOMPAGE_H

#include <QWidget>
#include "recompage.h"
#include "testpage.h"
namespace Ui {
class CustomPage;
}

class CustomPage : public QWidget
{
    Q_OBJECT

public:
    explicit CustomPage(QWidget *parent = nullptr);
    explicit CustomPage(QWidget *parent = nullptr, RecomPage * recom = nullptr, TestPage * test  = nullptr);
    ~CustomPage();

private slots:

    void on_Similar_notes_button_clicked();

    void on_start_testing_button_clicked();

private:
    Ui::CustomPage *ui;
    RecomPage * recom_page;
    TestPage *test_page;
};

#endif // CUSTOMPAGE_H
