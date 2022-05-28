#ifndef REGPAGE_H
#define REGPAGE_H

#include <QDialog>
#include <QMessageBox>
#include "Manager.h"
namespace Ui {
class regpage;
}

class regpage : public QDialog
{
    Q_OBJECT

public:
    explicit regpage(QWidget *parent = nullptr);
    ~regpage();

private slots:

    void on_create_acc_button_clicked();
signals:
    void reg_signal();
private:
    Ui::regpage *ui;
};

#endif // REGPAGE_H
