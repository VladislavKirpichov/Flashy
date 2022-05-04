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

private:
    Ui::RecomPage *ui;
};

#endif // RECOMPAGE_H
