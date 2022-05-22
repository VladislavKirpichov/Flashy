#ifndef TESTPAGE_H
#define TESTPAGE_H

#include <QWidget>

namespace Ui {
class TestPage;
}

class TestPage : public QWidget
{
    Q_OBJECT

public:
    explicit TestPage(QWidget *parent = nullptr);
    ~TestPage();
public slots:
    void open_page(int _page_num);
private slots:
    void on_end_test_button_clicked();

private:
    Ui::TestPage *ui;
    int page_num;
signals:
    void open_page_signal(int);
};

#endif // TESTPAGE_H
