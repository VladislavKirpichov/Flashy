#ifndef TESTPAGE_H
#define TESTPAGE_H

#include <QWidget>
#include <QMessageBox>
#include "questionfield.h"
#include "Manager.h"
namespace Ui {
class TestPage;
}

class TestPage : public QWidget
{
    Q_OBJECT

public:
    explicit TestPage(QWidget *parent = nullptr);
    ~TestPage();
    void update();
public slots:
    void open_page(int _page_num);
    void answer_slot(bool res);
private slots:
    void on_end_test_button_clicked();

private:
    Ui::TestPage *ui;
    int page_num;
    std::vector<QuestionFIeld*> question_fields;
    double result;
signals:
    void open_page_signal(int);
};

#endif // TESTPAGE_H
