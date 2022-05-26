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

private:
    Ui::QuestionFIeld *ui;
};

#endif // QUESTIONFIELD_H
