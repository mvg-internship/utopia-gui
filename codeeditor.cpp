#include "codeeditor.h"

CodeEditor::CodeEditor(QWidget *parent) : QPlainTextEdit(parent) {

  contmenu = new QMenu(this);
  c1 = new QAction(tr("Вставить"),this);
  c2 = new QAction(tr("Копировать"),this);
  c3 = new QAction(tr("Вырезать"),this);
  c4 = new QAction(tr("Выделить строку"),this);
  c5 = new QAction(tr("Отменить"),this);
  c6 = new QAction(tr("Повторить"),this);
  c7 = new QAction(tr("Выделить"),this);
  c8 = new QAction(tr("Удалить"),this);
  c9 = new QAction(tr("Выделить все"),this);

  connect(c1,SIGNAL(triggered()),this,SLOT(paste()));
  connect(c2,SIGNAL(triggered()),this,SLOT(copy()));
  connect(c3,SIGNAL(triggered()),this,SLOT(cut()));
  connect(c4,SIGNAL(triggered()),this,SLOT(select_current_line()));
  connect(c5,SIGNAL(triggered()),this,SLOT(undo_1()));
  connect(c6,SIGNAL(triggered()),this,SLOT(redo_1()));
  connect(c7,SIGNAL(triggered()),this,SLOT(select_word()));
  connect(c9,SIGNAL(triggered()),this,SLOT(selectAll()));

  contmenu->addAction(c1);
  contmenu->addAction(c2);
  contmenu->addAction(c3);
  contmenu->addAction(c4);
  contmenu->addAction(c5);
  contmenu->addAction(c6);
  contmenu->addAction(c7);
  contmenu->addAction(c8);
  contmenu->addAction(c9);
  connect(this,&CodeEditor::copyAvailable,this,&CodeEditor::change_);
}

void CodeEditor::highlightCurrentLine() {
  QList<QTextEdit::ExtraSelection> extraSelections;
  if (!isReadOnly()) {
    QTextEdit::ExtraSelection selection;
    selection.format.setBackground(lineColor);
    selection.format.setProperty(QTextFormat::FullWidthSelection, true);
    selection.cursor = textCursor();
    selection.cursor.clearSelection();
    extraSelections.append(selection);
  }
  setExtraSelections(extraSelections);
}

void CodeEditor::contextMenuEvent(QContextMenuEvent *event ) {
  c7->setEnabled(f);
  c4->setEnabled(f);
  c8->setEnabled(!f);
  c6->setEnabled(true);
  c5->setEnabled(true);
  c2->setEnabled(!f);
  c3->setEnabled(!f);
  c1->setEnabled(!f);
  contmenu->exec(event->globalPos());
  f= true;
}

void CodeEditor::redo_1() {
  redo();
}

void CodeEditor::undo_1() {
  undo();
}

void CodeEditor::select_word() {
  QTextCursor c = textCursor();
  c.select(QTextCursor::WordUnderCursor);
  setTextCursor(c);
}
void CodeEditor::select_current_line() {
  QTextCursor c = textCursor();
  c.select(QTextCursor::LineUnderCursor);
  setTextCursor(c);
}

void CodeEditor::change_() {
  f= false;
}
