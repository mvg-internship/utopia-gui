#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QPushButton>
#include <QTextStream>
#include <QProcess>
#include <Qdebug>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public slots:
    void save_as();
    void exec(const QString &path = QString());

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
void handleButton();
private:
    QPushButton *but_1;
    QPushButton *but_2;
    Ui::MainWindow *ui;
    QString save_results;
};
#endif // MAINWINDOW_H
