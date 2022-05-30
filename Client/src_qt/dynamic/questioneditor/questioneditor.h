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
    void set_data(const std::string & new_title, const std::string& new_answer);

private slots:
    void on_save_button_clicked();

    void on_hide_button_clicked();

private:
    Ui::QuestionEditor *ui;
    bool is_hide;
    size_t index;
};

#endif // QUESTIONEDITOR_H
