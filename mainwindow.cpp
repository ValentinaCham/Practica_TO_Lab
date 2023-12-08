#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "linkedlist.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->addTaskButton, &QPushButton::clicked, this, &MainWindow::addTask);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addTask() {
    try {
        srand(static_cast<unsigned>(time(nullptr)));
        LinkedList<int> myList;
        std::thread t1(&MainWindow::thread1, this, std::ref(myList));
        std::thread t2(&MainWindow::thread2, this, std::ref(myList));
        std::thread t3(&MainWindow::thread3, this, std::ref(myList));
        std::thread t4(&MainWindow::thread4, this, std::ref(myList));

        Task *newTask = new Task(this, myList.operacion());
        mTasks.append(newTask);
        ui->tasksLayout->addWidget(newTask);
        ui->tasksLayout->activate();
        connect(newTask, &Task::removed, this, &MainWindow::removeTask);

        t1.join();
        t2.join();
        t3.join();
        t4.join();
    } catch (const std::exception& e) {
        qDebug() << "Exception in addTask(): " << e.what();
    }
}

int MainWindow::random(int min, int max) {
    return rand() % (max - min + 1) + min;
}

void MainWindow::thread1(LinkedList<int>& lista) {
    for (int i = 0; i < 10; ++i) {
        int valRemove = random(1, 20);
        lista.eliminar(valRemove);
        this_thread::sleep_for(chrono::milliseconds(500));  // Para simular la ejecución en paralelo
    }
}

// Hilo 2: Insertar elementos en la lista
void MainWindow::thread2(LinkedList<int>& lista) {
    for (int i = 0; i < 20; ++i) {
        int valAdd = random(1, 20);
        lista.insertar(valAdd);
        this_thread::sleep_for(chrono::milliseconds(500));  // Para simular la ejecución en paralelo
    }
}

// Hilo 3: Buscar elementos en la lista
void MainWindow::thread3(LinkedList<int>& lista) {
    for (int i = 0; i < 10; ++i) {
        int valSearch = random(1, 20);
        lista.buscar(valSearch);
        this_thread::sleep_for(chrono::milliseconds(500));  // Para simular la ejecución en paralelo
    }
}

// Hilo 4: Modificar elementos de la lista
void MainWindow::thread4(LinkedList<int>& lista) {
    for (int i = 0; i < 10; ++i) {
        int valorModificar = random(1, 20);
        int incremento = random(1, 5);
        lista.modificar(valorModificar, incremento);
        this_thread::sleep_for(chrono::milliseconds(500));  // Para simular la ejecución en paralelo
    }
}

void MainWindow::removeTask(Task* task) {
    ui->tasksLayout->removeWidget(task);
    mTasks.removeOne(task);
    task->deleteLater();
}

