#ifndef CODEEDITOR_H
#define CODEEDITOR_H

#include <QPlainTextEdit>
#include <QPainter>
#include <QTextBlock>
#include <qmenu.h>
#include <qtextstream.h>
#include <QDateTime>
QT_BEGIN_NAMESPACE
class QPaintEvent;
class QResizeEvent;
class QSize;
class QWidget;
QT_END_NAMESPACE

class LineNumberArea;

class CodeEditor : public QPlainTextEdit {
Q_OBJECT

  public:
    void change_();
    void contextMenuEvent(QContextMenuEvent *event );
    CodeEditor(QWidget *parent = nullptr);
    QMenu *contmenu;
    QAction *c1;
    QAction *c2;
    QAction *c3;
    QAction *c4;
    QAction *c5;
    QAction *c6;
    QAction *c7;
    QAction *c8;
    QAction *c9;
    QColor lineColor = QColor(Qt::magenta).lighter(160);
    QBrush grey = Qt::red;
    bool f = true;
    bool tmp = 1;

  public slots:
    void select_word();
    void select_current_line();
    void redo_1();
    void undo_1();

  private slots:
    void highlightCurrentLine();

  private:
    QWidget *lineNumberArea;
};

#endif // CODEEDITOR_H
