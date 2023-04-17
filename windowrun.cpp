#include "windowrun.h"
#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QProcessEnvironment>
#include <QString>

windowRun::windowRun(QWidget* window ) {
  setWindowTitle(tr("Run Utopia"));
  setGeometry(300, 300, 320, 240);

  testFile = new QLabel(tr("сhoose test file (*.ril) format"),this);
  testFile-> move(50, 15);

  option = new QLabel(tr("app options to launch utopia if needed"),this);
  option-> move(50, 75);

  buttonf = new QPushButton("test",this);
  buttonf-> setGeometry(QRect(QPoint(50, 35), QSize(50, 30)));
  connect(buttonf, SIGNAL (released()), this, SLOT(handleButton()));

  QLineEdit *lineEdit = new QLineEdit(this);
  lineEdit-> setGeometry(50, 100, 200, 30);

  QPushButton *btnRunUtopia = new QPushButton("Run Utopia", this);
  btnRunUtopia-> setGeometry(210, 210, 100, 30);

  QPushButton *applyButton = new QPushButton("Apply", this);
  applyButton-> setGeometry(220, 100, 80, 30);
  connect(btnRunUtopia, &QPushButton::clicked, this, &windowRun::onBtnRunUtopiaClicked);
  QObject::connect(applyButton, &QPushButton::clicked, [=,this]() {
    text = lineEdit-> text();
   });

}
void windowRun::handleButton(const QString &path) {
  QString filename = path;
  if (filename.isNull()) {
    filename = QFileDialog::getOpenFileName(this, tr("Open File"),shellVariable+"test/data/ril/test.ril", tr("RIL Files (*.ril)"));
    a = filename;
  }
}
void windowRun::onBtnRunUtopiaClicked() {
  QString command = shellVariable + text + a ;
  qDebug() << "text" << command;
  QProcess::startDetached(command);
}
