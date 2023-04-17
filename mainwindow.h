#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QPushButton>
#include <QTextStream>
#include <QProcess>
#include "windowrun.h"
#include <qdebug.h>
#include <QToolButton>
#include <QtMath>
#include <QMenu>
#include <QMenuBar>
#include <QDebug>
#include "codeeditor.h"
#include <QPushButton>
#include <QProcessEnvironment>
#include <QGraphicsView>
#include <QGraphicsLineItem>
#include <QXmlStreamReader>
#include <QRect>
#include <QtGlobal>
#include <random>
#include <stdio.h>
#include <string.h>

QT_BEGIN_NAMESPACE
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
Q_OBJECT

private slots:
  void execSettings(const QString &path = QString());
  void openFile(const QString &path = QString());
  void save();
  void SaveAs();
  void runUtopia();
  void exportResults();


public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
  void handleButton();
  void setMenu();

private:
  QString pathFile;
  QString pathOpenfile;
  QMenu *menu;
  QFont font;
  CodeEditor *edit;
  windowRun *cho;
  const QProcessEnvironment env1 = QProcessEnvironment::systemEnvironment();
  const QString shellVariable1 = env1.value("UTOPIA_HOME");
  void loadGraph(QString filename, QMap<QString, QVector<QString>> &adjList);
  QMap<QString, QVector<QString>> adjList;
  void displayGraph(QMap<QString, QVector<QString>>&adjList);
  QGraphicsScene *scene;
  QMap<QString, QGraphicsEllipseItem*> nodes;
};
#endif // MAINWINDOW_H
