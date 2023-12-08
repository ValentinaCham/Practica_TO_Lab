#ifndef TASK_H
#define TASK_H

#include <QDialog>
#include <QString>
#include <QRegularExpression>
#include <QStringList>

namespace Ui {
class Task;
}

class Task : public QDialog
{
    Q_OBJECT

public:
    explicit Task(QWidget *parent = nullptr, std::string operation = "");
    ~Task();

signals:
    void removed(Task* task);

private slots:
    void checkResult();
    int evaluateExpression(const QString &expression);

private:
    Ui::Task *ui;
    int expected_result;
};

#endif // TASK_H
