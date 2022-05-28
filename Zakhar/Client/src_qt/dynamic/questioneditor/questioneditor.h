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
    QuestionEditor(QWidget *parent = nullptr, size_t _index = 0);
    ~QuestionEditor();

private slots:
    void on_save_button_clicked();

    void on_hide_button_clicked();

private:
    Ui::QuestionEditor *ui;
    bool is_hide;
    size_t index;
};

#endif // QUESTIONEDITOR_H
