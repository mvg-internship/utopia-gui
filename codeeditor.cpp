#include "codeeditor.h"

CodeEditor::CodeEditor(QWidget *parent) : QPlainTextEdit(parent) {

  contMenu = new QMenu(this);
  actionPaste = new QAction(tr("Paste"),this);
  actionCopy = new QAction(tr("Copy"),this);
  actionCut = new QAction(tr("Cut"),this);
  selectLine = new QAction(tr("Select line"),this);
  actionUndo = new QAction(tr("Undo"),this);
  actionRedo = new QAction(tr("Redo"),this);
  selectW = new QAction(tr("Select"),this);
  del = new QAction(tr("Delete"),this);
  selectA = new QAction(tr("Select All"),this);

  connect(actionPaste, SIGNAL(triggered()), this, SLOT(paste()));
  connect(actionCopy, SIGNAL(triggered()), this, SLOT(copy()));
  connect(actionCut, SIGNAL(triggered()), this, SLOT(cut()));
  connect(selectLine, SIGNAL(triggered()), this, SLOT(selectCurrent()));
  connect(actionUndo, SIGNAL(triggered()), this, SLOT(undo()));
  connect(actionRedo, SIGNAL(triggered()), this, SLOT(redo()));
  connect(selectW, SIGNAL(triggered()), this, SLOT(selectWord()));
  connect(selectA, SIGNAL(triggered()), this, SLOT(selectAll()));

  contMenu-> addAction(actionPaste);
  contMenu-> addAction(actionCopy);
  contMenu-> addAction(actionCut);
  contMenu-> addAction(selectLine);
  contMenu-> addAction(actionUndo);
  contMenu-> addAction(actionRedo);
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
  actionRedo->setEnabled(true);
  actionUndo->setEnabled(true);
  actionCopy->setEnabled(!f);
  actionCut->setEnabled(!f);
  actionPaste->setEnabled(!f);
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
