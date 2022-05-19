#ifndef PAGE_H
#define PAGE_H

#include <QWidget>
#include<custompage.h>
namespace Ui {
class Page;
}

class Page : public QWidget
{
    Q_OBJECT

public:
    explicit Page(QWidget *parent = nullptr);
    explicit Page(QWidget *parent = nullptr, CustomPage * custom = nullptr);
    ~Page();

private:
    Ui::Page *ui;
};

#endif // PAGE_H
