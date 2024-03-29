#include "windowrun.h"
#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QProcessEnvironment>
#include <QString>
#include <filesystem>

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
  applyTestFile = new QPushButton("Apply",this);
  applyTestFile->setGeometry(QRect(QPoint(110, 35), QSize(50, 30)));
  connect(applyTestFile, SIGNAL (released()), this, SLOT(handleApplyTestButton()));

  QLineEdit *lineEdit = new QLineEdit(this);
  lineEdit-> setGeometry(50, 100, 200, 30);

  QPushButton *btnRunUtopia = new QPushButton("Run Utopia", this);
  btnRunUtopia-> setGeometry(210, 210, 100, 30);

  QPushButton *applyButton = new QPushButton("Apply", this);
  applyButton-> setGeometry(220, 100, 80, 30);
  connect(btnRunUtopia, &QPushButton::clicked, this, &windowRun::onBtnRunUtopiaClicked);
  QObject::connect(applyButton, &QPushButton::clicked, [=]() {
    text = lineEdit-> text();
   });

}
void windowRun::handleButton(const QString &path) {
  QString filename = path;
  a = filename;
  if (filename.isNull()) {
    std::filesystem::path filePath(shellVariable.toStdString());
    std::filesystem::path fullPath = filePath / "test/data/ril/test.ril";
    filename = QFileDialog::getOpenFileName(this, tr("Open File"),QString::fromStdString(fullPath.string()), tr("RIL Files (*.ril)"));
    emit fileSelected(filename);
    a = filename;
  }
  else{
    qDebug() << "No file selected: ";
  }
}
void windowRun::handleApplyTestButton(){
  b = a;
}
void windowRun::onBtnRunUtopiaClicked() {
  std::filesystem::path filePath(shellVariable.toStdString());
  std::filesystem::path fullPath = filePath / "build/src/umain";
  QString program = QString::fromStdString(fullPath.string());
  QStringList arguments;
  arguments << text << b;
  QProcess::startDetached(program, arguments);
  qDebug() << QString("Starting process: %1 %2").arg(program).arg(arguments.join(" "));
}

