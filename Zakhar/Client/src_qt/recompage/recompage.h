#ifndef RECOMPAGE_H
#define RECOMPAGE_H

#include <QWidget>

namespace Ui {
class RecomPage;
}

class RecomPage : public QWidget
{
    Q_OBJECT

public:
    explicit RecomPage(QWidget *parent = nullptr);
    ~RecomPage();
public slots:
    void open_page(int _page_num);
private:
    Ui::RecomPage *ui;
    int page_num;
};

#endif // RECOMPAGE_H
