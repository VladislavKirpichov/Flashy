#ifndef USERPAGE_H
#define USERPAGE_H

#include <QWidget>
namespace Ui {
class UserPage;
}

class UserPage : public QWidget
{
    Q_OBJECT

public:
    explicit UserPage(QWidget *parent = nullptr);
    ~UserPage();

private slots:
    void on_pushButton_2_clicked();

private:
    Ui::UserPage *ui;
};

#endif // USERPAGE_H
