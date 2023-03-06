#ifndef CHOOSE_H
#define CHOOSE_H


#include <QDialog>
#include <QFileDialog>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <string.h>
#include <QProcessEnvironment>
#include <QString>
class chooze: public QDialog{
Q_OBJECT

  public:
    chooze(QWidget* p = 0);

  private:
    QString path;
    QLabel *tf;
    QLabel *op;
    QPushButton *buttonf;
    QString filename;
    QLineEdit* pleText;
    QString* text;
    QString a;
    QPushButton *btnRunUtopia;
  private slots:
  void handleButton(const QString &path = QString());
  void onBtnRunUtopiaClicked();
};

#endif // CHOOSE_H
