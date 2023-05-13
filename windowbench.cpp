#include <filesystem>
#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QProcessEnvironment>
#include <QString>
#include "windowbench.h"

windowBench::windowBench(QWidget* window ) {
  setWindowTitle(tr("Run Basicviz"));
  setGeometry(300, 300, 320, 240);

  option = new QLabel(tr("add options"),this);
  option-> move(50, 75);

  QLineEdit *lineEdit = new QLineEdit(this);
  lineEdit-> setGeometry(50, 100, 200, 30);

  QPushButton *btnRunUtopia = new QPushButton("Run Basicviz", this);
  btnRunUtopia-> setGeometry(210, 210, 100, 30);

  QPushButton *applyButton = new QPushButton("Apply", this);
  applyButton-> setGeometry(220, 100, 80, 30);
  connect(btnRunUtopia, &QPushButton::clicked, this, &windowBench::runBench);

  QObject::connect(applyButton, &QPushButton::clicked, [=]() {
    text = lineEdit-> text();
    });

}
void windowBench::runBench(){
  QString program = shellVariable2;
  QStringList arguments = text.split(' ', Qt::SkipEmptyParts);
  arguments.prepend(filename);
  QProcess::startDetached(program, arguments);
  qDebug() << QString("Starting process: %1 %2").arg(program).arg(arguments.join(" "));
}


