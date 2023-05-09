#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "codeeditor.h"
#include <graphviz/gvc.h>
#include <graphviz/cgraph.h>
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
#include "windowbench.h"

QT_BEGIN_NAMESPACE
QT_END_NAMESPACE

class MainWindow : public QMainWindow {

Q_OBJECT

private slots:
  void openFile(const QString &path = QString());
  void openFileinWindow(const QString &path = QString());
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
  windowBench *bench;
  const QProcessEnvironment env1 = QProcessEnvironment::systemEnvironment();
  const QString shellVariable1 = env1.value("UTOPIA_HOME");
  void loadGraph(QString filename, QMap<QString, QVector<QString>> &adjList);
  QMap<QString, QVector<QString>> adjList;
  void displayGraph(QMap<QString, QVector<QString>>&adjList);
  QGraphicsScene *scene;
  QMap<QString, QGraphicsEllipseItem*> nodes;
  
  friend class QTest1;
};
#endif // MAINWINDOW_H
