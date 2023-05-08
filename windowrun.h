#ifndef WINDOWRUN_H
#define WINDOWRUN_H
#include "codeeditor.h"
#include <QDialog>
#include <QFileDialog>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include<QMainWindow>
#include <QProcessEnvironment>
#include <QString>
#include <qdebug.h>
#include <string.h>


class windowRun: public QDialog {
Q_OBJECT

public:
  windowRun(QWidget *window = 0);
  QString a;
private slots:
  void handleButton(const QString &path = QString());
  void onBtnRunUtopiaClicked();
signals:
  void fileSelected(const QString &path);
private:
  const QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
  const QString shellVariable = env.value("UTOPIA_HOME");
  QString path;
  QFont font;
  QLabel *testFile;
  QLabel *option;
  QPushButton *buttonf;
  QString filename;
  QLineEdit*pleText;
  QString text;
  QPushButton *btnRunUtopia;
  QPushButton *applyButton;
  QString str;
  CodeEditor *edit;

  friend class QTest1;
};


#endif // CHOOSE_H
