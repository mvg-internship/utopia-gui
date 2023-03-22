#include "mainwindow.h"
#include <QString>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent){
  setWindowTitle(tr("Utopia"));
  setMenu();
  QString save_results = "";
  QString pathOpenfile="";
}

MainWindow::~MainWindow(){

  delete menu;
}

void MainWindow::execSettings(const QString &path){
  QString fileName = pathFile;
  if (fileName.isNull()) {

    fileName = QFileDialog::getOpenFileName(this, tr("Open File"), shellVariable1+"test/data/ril/test.ril", tr("Text Files (*)"));
  }
  if (!fileName.isEmpty()) {

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
      return;

    QTextStream in(&file);
    while (!in.atEnd()) {

      QString line = in.readLine();
      pathFile += line;
    }
  }
  else {
      qDebug()<<"the file did not open";
  }

}
void MainWindow::openFile(const QString &path){
  QString fileName = pathFile;
  if (fileName.isNull()) {

    fileName = QFileDialog::getOpenFileName(this, tr("Open File"), shellVariable1+"test/data/ril/test.ril", tr("RIL Files (*.ril)"));
    pathOpenfile=fileName;
  }
  if (!fileName.isEmpty()) {

    edit = new CodeEditor(this);
    setCentralWidget(edit);
    edit->setWindowTitle(QObject::tr(""));
    edit->setFont(font);
    edit->show();
    QFile file(fileName);
    if (file.exists() && file.open(QFile::ReadOnly | QFile::Text)) {
      edit->setPlainText(file.readAll());
      file.close();
    }
    return;
}
  else {
    qDebug()<<"the file did not open";
  }

}

void MainWindow::save(){
    
  QString fileName = pathOpenfile;
  if (fileName != "") {
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly)) {
      qDebug()<<"the file did not open"; 
    }else {
      QTextStream stream(&file);
      stream << edit->toPlainText();
      stream.flush();
      file.close();
         }
  }
}
void MainWindow::SaveAs(){
    
  QString fileName = QFileDialog::getSaveFileName(this, tr("Save as"), shellVariable1+"test/data/ril/test.ril",tr("Text file (*.txt );; RIL file (*.ril )"));
  if (fileName != "") {
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly)) {
      qDebug()<<"the file did not open";
    }else {
           QTextStream stream(&file);
           stream << edit->toPlainText();
           stream.flush();
           file.close();
            }
        }
}
void MainWindow::runUtopia(){
  cho = new windowRun(this);
  cho->show();
}


void MainWindow::exportResults(){}


void MainWindow::setMenu () {
    
menu = menuBar()->addMenu(tr("&File"));
menu->addAction(tr("Open file"), this, SLOT(openFile()), QKeySequence(tr("Ctrl+N","File|New")));
menu->addAction(tr("Save file"), this, SLOT(save()), QKeySequence(tr("Ctrl+S","File|Save")));
menu->addAction(tr("Save as file"), this, SLOT(SaveAs()), QKeySequence(tr("Ctrl+T","File|Save as")));
menu->addAction(tr("Export"), this, SLOT(exportResults()), QKeySequence(tr("Ctrl+E","File|Export")));

menu = menuBar()->addMenu(tr("&Run"));
menu->addAction(tr("Run"), this, SLOT(runUtopia()), QKeySequence(tr("Ctrl+R","File|New")));
}
