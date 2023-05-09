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
  QString b;
  QString text;
public slots:
  void onBtnRunUtopiaClicked();
private slots:
  void handleButton(const QString &path = QString());
  void handleApplyTestButton();
signals:
  void fileSelected(const QString &path);
private:
  const QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
  const QString shellVariable = env.value("Graphiz");
  QString path;
  QFont font;
  QLabel *testFile;
  QLabel *option;
  QPushButton *buttonf;
  QString filename;
  QLineEdit*pleText;
  QPushButton *btnRunUtopia;
  QPushButton *applyButton;
  QPushButton *applyTestFile;
  QString str;
  CodeEditor *edit;

  friend class QTest1;
};


#endif // CHOOSE_H
