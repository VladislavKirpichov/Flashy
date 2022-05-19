#ifndef PAGE_H
#define PAGE_H

#include <QWidget>

namespace Ui {
class Page;
}

class Page : public QWidget
{
    Q_OBJECT

public:
    explicit Page(QWidget *parent = nullptr);
    ~Page();

private:
    Ui::Page *ui;
};

#endif // PAGE_H
