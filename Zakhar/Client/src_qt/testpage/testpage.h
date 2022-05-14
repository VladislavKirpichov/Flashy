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

private:
    Ui::TestPage *ui;
};

#endif // TESTPAGE_H
