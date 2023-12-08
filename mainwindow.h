#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <thread>
#include <ctime>
#include <cstdlib>
#include <mutex>
#include <chrono>
#include "task.h"
#include "linkedlist.h"

class Task;
template <typename T> class LinkedList;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void thread1(LinkedList<int>& lista);
    void thread2(LinkedList<int>& lista);
    void thread3(LinkedList<int>& lista);
    int random(int min, int max);
    void thread4(LinkedList<int>& lista);
public slots:
    void addTask();
    void removeTask(Task* task);
private:
    Ui::MainWindow *ui;
    QVector<Task*> mTasks;
};
#endif // MAINWINDOW_H
