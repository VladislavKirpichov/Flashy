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
    explicit QuestionFIeld(QWidget *parent = nullptr, bool is_yours = true);
    ~QuestionFIeld();
    void set_title(const std::string & new_title);
private slots:
    void on_like_button_clicked();

    void on_dislike_button_clicked();

    void on_answer_button_clicked();



private:
    Ui::QuestionFIeld *ui;
    bool is_yours;
};

#endif // QUESTIONFIELD_H
