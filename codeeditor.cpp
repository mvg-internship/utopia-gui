#include "codeeditor.h"

CodeEditor::CodeEditor(QWidget *parent) : QPlainTextEdit(parent) {

  contMenu = new QMenu(this);
  paste = new QAction(tr("Paste"),this);
  copy = new QAction(tr("Copy"),this);
  cut = new QAction(tr("Cut"),this);
  selectLine = new QAction(tr("Select line"),this);
  undo = new QAction(tr("Undo"),this);
  redo = new QAction(tr("Redo"),this);
  selectW = new QAction(tr("Select"),this);
  del = new QAction(tr("Delete"),this);
  selectA = new QAction(tr("Select All"),this);

  connect(paste, SIGNAL(triggered()), this, SLOT(paste()));
  connect(copy, SIGNAL(triggered()), this, SLOT(copy()));
  connect(cut, SIGNAL(triggered()), this, SLOT(cut()));
  connect(selectLine, SIGNAL(triggered()), this, SLOT(selectCurrent()));
  connect(undo, SIGNAL(triggered()), this, SLOT(undo()));
  connect(redo, SIGNAL(triggered()), this, SLOT(redo()));
  connect(selectW, SIGNAL(triggered()), this, SLOT(selectWord()));
  connect(selectA, SIGNAL(triggered()), this, SLOT(selectAll()));

  contMenu-> addAction(paste);
  contMenu-> addAction(copy);
  contMenu-> addAction(cut);
  contMenu-> addAction(selectLine);
  contMenu-> addAction(undo);
  contMenu-> addAction(redo);
  contMenu-> addAction(selectW);
  contMenu-> addAction(del);
  contMenu-> addAction(selectA);
  connect(this, &CodeEditor::copyAvailable, this, &CodeEditor::change_);
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
  selectW->setEnabled(f);
  selectLine->setEnabled(f);
  del->setEnabled(!f);
  redo->setEnabled(true);
  undo->setEnabled(true);
  copy->setEnabled(!f);
  cut->setEnabled(!f);
  paste->setEnabled(!f);
  contMenu->exec(event->globalPos());
  f = true;
}

void CodeEditor::selectWord() {
  QTextCursor c = textCursor();
  c.select(QTextCursor::WordUnderCursor);
  setTextCursor(c);
}
void CodeEditor::selectCurrent() {
  QTextCursor c = textCursor();
  c.select(QTextCursor::LineUnderCursor);
  setTextCursor(c);
}

void CodeEditor::change_() {
  f = false;
}
