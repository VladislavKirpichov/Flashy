#ifndef QUESTIONFIELD_H
#define QUESTIONFIELD_H

#include <QWidget>

namespace Ui {
class QuestionFIeld;
}

class QuestionFIeld : public QWidget
{
    Q_OBJECT

public:
    explicit QuestionFIeld(QWidget *parent = nullptr);
    ~QuestionFIeld();

private slots:
    void on_like_button_clicked();

    void on_dislike_button_clicked();

    void on_answer_button_clicked();

private:
    Ui::QuestionFIeld *ui;
};

#endif // QUESTIONFIELD_H
