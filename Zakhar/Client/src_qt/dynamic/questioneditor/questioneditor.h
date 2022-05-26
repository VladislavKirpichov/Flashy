#ifndef QUESTIONEDITOR_H
#define QUESTIONEDITOR_H

#include <QWidget>

namespace Ui {
class QuestionEditor;
}

class QuestionEditor : public QWidget
{
    Q_OBJECT

public:
    explicit QuestionEditor(QWidget *parent = nullptr);
    ~QuestionEditor();

private:
    Ui::QuestionEditor *ui;
};

#endif // QUESTIONEDITOR_H
