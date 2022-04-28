#ifndef REGPAGE_H
#define REGPAGE_H

#include <QDialog>

namespace Ui {
class regpage;
}

class regpage : public QDialog
{
    Q_OBJECT

public:
    explicit regpage(QWidget *parent = nullptr);
    ~regpage();

private:
    Ui::regpage *ui;
};

#endif // REGPAGE_H
