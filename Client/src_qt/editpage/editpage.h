#ifndef EDITPAGE_H
#define EDITPAGE_H

#include <QWidget>
#include "questioneditor.h"
#include "Manager.h"
namespace Ui {
class EditPage;
}

class EditPage : public QWidget
{
    Q_OBJECT

public:
    explicit EditPage(QWidget *parent = nullptr);
    ~EditPage();
public slots:
    void open_page(int _page_num);
private slots:
    void on_save_text_button_clicked();
    void on_exit_button_clicked();

    void on_add_question_button_clicked();

private:
    Ui::EditPage *ui;
    int page_num;
    QList<QuestionEditor*> questions;
signals:
    void open_page_signal(int);
    void save_page_signal(QString);
};

#endif // EDITPAGE_H
