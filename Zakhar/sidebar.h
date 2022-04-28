#ifndef SIDEBAR_H
#define SIDEBAR_H

#include <QWidget>
#include "userpage.h"
namespace Ui {
class Sidebar;
}

class Sidebar : public QWidget
{
    Q_OBJECT

public:
    explicit Sidebar(QWidget *parent = nullptr);
    ~Sidebar();

private slots:
    void on_pushButton_13_clicked();

private:
    Ui::Sidebar *ui;
    UserPage * user_page;
};

#endif // SIDEBAR_H
