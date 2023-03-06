#include "choose.h"
#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QProcessEnvironment>
#include <QString>
QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
QString shellVariable = env.value("UTOPIA_HOME");

chooze::chooze(QWidget* p ){
  setWindowTitle(tr("Run Utopia"));
  setGeometry(300,300,320,240);


  tf = new QLabel(tr("сhoose test file (*.ril) format"),this);
  tf->move(50,15);

  op = new QLabel(tr("app options to launch utopia if needed"),this);
  op->move(50,75);

   buttonf = new QPushButton("test",this);
   buttonf->setGeometry(QRect(QPoint(50, 35), QSize(50, 30)));
   connect(buttonf, SIGNAL (released()), this, SLOT(handleButton()));

   QLineEdit *lineEdit = new QLineEdit(this);
   lineEdit->setGeometry(50, 100, 200, 30);
   // Создание кнопки "Run Utopia"
   QPushButton *btnRunUtopia = new QPushButton("Run Utopia", this);
   btnRunUtopia->setGeometry(210,210, 100, 30);

   // Создаем кнопку "Apply"
   QPushButton *applyButton = new QPushButton("Apply", this);
   applyButton->setGeometry(220, 100, 80, 30);
   connect(btnRunUtopia, &QPushButton::clicked, this, &chooze::onBtnRunUtopiaClicked);

   // Подключаем сигнал нажатия на кнопку "Apply" к слоту, который будет выводить символы из QlineEdit в консоль
   QObject::connect(applyButton, &QPushButton::clicked, [=]() {
   QString text = lineEdit->text();

   });

}
void chooze::handleButton(const QString &path) {
QString filename =path;
  if (filename.isNull()) {
    filename = QFileDialog::getOpenFileName(this, tr("Open File"),shellVariable+"test/data/ril/test.ril", tr("RIL Files (*.ril)"));
    a=filename;
  }
}
void chooze::onBtnRunUtopiaClicked() {
  QString command =shellVariable+"build/src/umain rtl " +a ;
  qDebug()<<"text"<<command;
  QProcess::startDetached(command);
}
