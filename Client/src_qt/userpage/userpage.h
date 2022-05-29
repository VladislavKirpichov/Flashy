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
public slots:
    void open_page(int _page_num);
    void update(QString name, QString login, QString password);
private slots:
    void on_exit_button_clicked();

    void on_change_name_button_clicked();

private:
    Ui::UserPage *ui;
    int page_num;
signals:
    void exit_signal();
};

#endif // USERPAGE_H
