#include "Task.h"
#include "ui_Task.h"

Task::Task(QWidget *parent, std::string operation) :
    QDialog(parent),
    ui(new Ui::Task)

{
    ui->setupUi(this);
    QString operationQString = QString::fromStdString(operation);
    ui->lblOperacion->setText(operationQString);
    expected_result = evaluateExpression(operationQString);
    connect(ui->btnVerificar, &QPushButton::clicked, [this]{emit removed(this);});
    connect(ui->btnVerificar, &QPushButton::clicked, this, &Task::checkResult);
}

Task::~Task()
{
    delete ui;
}

void Task::checkResult() {
    // Obtener el texto del QLineEdit
    QString text = ui->resultado->text();

    // Llamar a la función evaluateExpression con el texto obtenido
    int result = evaluateExpression(text);

    // Set the color based on the correctness of the result
    if (result == expected_result) {
        ui->resultado->setStyleSheet("QLineEdit { background-color : green; }");
    } else {
        ui->resultado->setStyleSheet("QLineEdit { background-color : red; }");
    }
}

int Task::evaluateExpression(const QString &expression) {
    QStringList tokens = expression.split(QRegularExpression("[-+]"));
    QStringList operators = expression.split(QRegularExpression("[0-9]"));

    int result = tokens.first().toInt();

    for (int i = 1; i < tokens.size(); ++i) {
        int operand = tokens[i].toInt();
        if (operators[i - 1] == "+") {
            result += operand;
        } else if (operators[i - 1] == "-") {
            result -= operand;
        }
    }

    return result;
}
