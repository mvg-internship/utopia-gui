#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    but_1= new QPushButton("Запустить",this);
    but_1->setGeometry(QRect(QPoint(50, 100),
    QSize(200, 50)));
    but_2= new QPushButton("Сохранить",this);
    but_2->setGeometry(QRect(QPoint(350, 100),
    QSize(200, 50)));
    connect(but_1, SIGNAL (released()), this, SLOT (exec()));
    connect(but_2, SIGNAL (released()), this, SLOT (save_as()));
    QString save_results="";
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::exec(const QString &path){
    QString fileName = path;
   if (fileName.isNull()){
            fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open File"), "/D:",tr("EXE Files (*.exe);;Run Files (*.run )"));}
        if (!fileName.isEmpty()) {
            QFile file(fileName);
            QProcess process(this);
            process.start(fileName);
            process.waitForReadyRead();
            process.write("key");// передача ключей работающей программе
            process.waitForBytesWritten();
            process.waitForReadyRead();
            save_results+=process.readAll();
            process.waitForFinished();



        }

}
void MainWindow::save_as(){
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File_as"),
                               "/D:",tr("Text files (*.txt )" ));
    if (fileName != "") {
            QFile file(fileName);
            if (!file.open(QIODevice::WriteOnly)) {
            } else {
                QTextStream stream(&file);
                stream << save_results;
                stream.flush();
                file.close();
            }
        }
    save_results="";
}
