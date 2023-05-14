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
  QMenu *contMenu;
  QAction *actionPaste;
  QAction *actionCopy;
  QAction *actionCut;
  QAction *selectLine;
  QAction *actionUndo;
  QAction *actionRedo;
  QAction *selectW;
  QAction *del;
  QAction *selectA;
  QColor lineColor = QColor(Qt::magenta).lighter(160);
  QBrush grey = Qt::red;
  bool f = true;

public slots:
  void selectWord();
  void selectCurrent();

private slots:
  void highlightCurrentLine();

private:
  QWidget *lineNumberArea;
  
  friend class QTest1;
};

#endif // CODEEDITOR_H
