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
    void set_data(const std::string & new_title, const std::string& new_answer);
private slots:
    void on_like_button_clicked();

    void on_dislike_button_clicked();

    void on_answer_button_clicked();


signals:
    void answer_signal(bool);
private:
    Ui::QuestionFIeld *ui;
    QString answer;
    bool is_yours;
    bool is_clicked;
};

#endif // QUESTIONFIELD_H
