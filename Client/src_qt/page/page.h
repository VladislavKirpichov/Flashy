#ifndef PAGE_H
#define PAGE_H

#include <QWidget>
#include<custompage.h>

class Page : public QWidget
{
    Q_OBJECT

public:
    explicit Page(QWidget *parent = nullptr);
    explicit Page(QWidget *parent = nullptr, CustomPage * custom = nullptr);
    ~Page();

};

#endif // PAGE_H
