#ifndef CUSTOMPAGE_H
#define CUSTOMPAGE_H

#include <QWidget>
namespace Ui {
class CustomPage;
}

class CustomPage : public QWidget
{
    Q_OBJECT

public:
    explicit CustomPage(QWidget *parent = nullptr);
    ~CustomPage();
public slots:
    void open_page(int _page_num);
    void save_text(QString new_text);
private slots:

    void on_recom_notes_button_clicked();

    void on_start_testing_button_clicked();

    void on_edit_button_clicked();

private:
    Ui::CustomPage *ui;
    int page_num;
signals:
    void open_page_signal(int);
};

#endif // CUSTOMPAGE_H
