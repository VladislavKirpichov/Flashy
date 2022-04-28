#ifndef CUSTOMPAGE_H
#define CUSTOMPAGE_H

#include <QWidget>
#include "recompage.h"

namespace Ui {
class CustomPage;
}

class CustomPage : public QWidget
{
    Q_OBJECT

public:
    explicit CustomPage(QWidget *parent = nullptr);
    explicit CustomPage(QWidget *parent = nullptr, RecomPage * recom = nullptr);
    ~CustomPage();

private slots:
    void on_pushButton_2_clicked();

private:
    Ui::CustomPage *ui;
    RecomPage * recom_page;
};

#endif // CUSTOMPAGE_H
