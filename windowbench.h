#ifndef WINDOWBENCH_H
#define WINDOWBENCH_H
#include "codeeditor.h"
#include <QDialog>
#include <QFileDialog>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QMainWindow>
#include <QProcessEnvironment>
#include <QString>
#include <qdebug.h>
#include <string.h>


class windowBench: public QDialog {
    Q_OBJECT

public:
    windowBench(QWidget *window = 0);
    QString text;
    QString filename;
public slots:
    void runBench();
private:
    const QProcessEnvironment env2 = QProcessEnvironment::systemEnvironment();
    const QString shellVariable2 = env2.value("Graphviz");
    QString path;
    QFont font;
    QLabel *option;
    QLineEdit*pleText;
    QPushButton *btnRunUtopia;
    QPushButton *applyButton;
    QString str;
    CodeEditor *edit;

    friend class QTest1;
};


#endif
