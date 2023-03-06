#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QPushButton>
#include <QTextStream>
#include <QProcess>
#include <qdebug.h>
#include <QToolButton>
#include <QMenu>
#include <QMenuBar>
#include <QDebug>
#include <codeeditor.h>
#include <stdio.h>
#include <string.h>
#include <choose.h>
#include <QPushButton>
QT_BEGIN_NAMESPACE
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
  Q_OBJECT
  private slots:
    void showresult();
    void execSettings(const QString &path = QString());
    void openFile(const QString &path = QString());
    void save();
    void SaveAs();
    void runUtopia();;
    void exportResults();


  public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void handleButton();
    void setmenu();

  private:
    QString path1;
    QString pathOpenfile;
    QMenu *menu;
    QFont font;
    CodeEditor *edit;
    chooze *cho;
};
#endif // MAINWINDOW_H
