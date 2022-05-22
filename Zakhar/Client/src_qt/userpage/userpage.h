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
private slots:
    void on_exit_button_clicked();

private:
    Ui::UserPage *ui;
    int page_num;
};

#endif // USERPAGE_H
