#ifndef WINDOWRUN_H
#define WINDOWRUN_H
#include <QDialog>
#include <QFileDialog>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QProcessEnvironment>
#include <QString>
#include <string.h>
#include <qdebug.h>

class windowRun: public QDialog {
Q_OBJECT

public:
  windowRun(QWidget *window = 0);
private:
  const QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
  const QString shellVariable = env.value("UTOPIA_HOME");
  QString path;
  QLabel *testFile;
  QLabel *option;
  QPushButton *buttonf;
  QString filename;
  QLineEdit*pleText;
  QString text;
  QString a;
  QPushButton *btnRunUtopia;
  QString str;
private slots:
  void handleButton(const QString &path = QString());
  void onBtnRunUtopiaClicked();
};

#endif // CHOOSE_H
