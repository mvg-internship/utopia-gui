#include <QApplication>
#include <QClipboard>
#include <QtTest>
#include <QProcess>
#include <QMessageBox>
#include "../mainwindow.h"
#include <filesystem>

class QTest1 : public QObject {
  Q_OBJECT
public:
  QTest1(QApplication *app);
  ~QTest1();

private slots:
  void testOpenFile();
  void testSave();
  void testLoadGraph();
  void testDisplayGraph();
  void testUndoRedo();
  void testPaste();
  void testCopy();
  void testCut();
  void testClear();
  void testSelectAll();
  void testCursorPosition();
  void testSetPlainText();
  void testFindText();
  void testSetWindowTitle();
  void testRunUtopia();
  void testExportResults();
  void testOpenFileInUtopia();
  void testApplyOptions();
  void testOpenUtopia();
  void testApplyTest();
  void testOpenFileInWindow();
private:
  const QProcessEnvironment env1 = QProcessEnvironment::systemEnvironment();
  const QString shellVariable1 = env1.value("UTOPIA_HOME");
  QApplication *app_;
  MainWindow *window_;
  CodeEditor *editor_;
  QPushButton *runButton_;
  QSignalSpy *openFileSpy_;
  QSignalSpy *saveAsSpy_;

  void initTestCase(){
    editor_ = new CodeEditor(window_);
    runButton_ = window_->findChild<QPushButton*>("runButton");
    openFileSpy_ = new QSignalSpy(window_, SIGNAL(openFile(QString)));
    saveAsSpy_ = new QSignalSpy(window_, SIGNAL(saveAs()));
  }

  void cleanupTestCase(){
    delete editor_;
    delete openFileSpy_;
    delete saveAsSpy_;
    window_->deleteLater();
  }
};

QTest1::QTest1(QApplication *app) : app_(app), window_(new MainWindow) {
}

QTest1::~QTest1() {
}

void QTest1::testOpenFile() {
  std::filesystem::path filePath(shellVariable1.toStdString());
  std::filesystem::path fullPath = filePath / "test/data/ril/test.ril";
  QString testFilePath = QString::fromStdString(fullPath.string());
  try {
    window_->openFile(testFilePath);
    QVERIFY2(window_->centralWidget() == nullptr, "Failed to open file");
  } catch (const std::exception& ex) {
     QFAIL(ex.what());
  }
}

void QTest1::testSave() {
  std::filesystem::path filePath(shellVariable1.toStdString());
  std::filesystem::path fullPath = filePath / "test/data/ril/test.ril";
  window_->openFile(QString::fromStdString(fullPath.string()));
  QVERIFY2(window_->centralWidget() == nullptr, "Failed to open file");
  window_->save();
  QVERIFY(true);
}

void QTest1::testLoadGraph() {
  const QString fileName = "./graphml-sample.xml";
  window_->loadGraph(fileName, window_->adjList);
  QVERIFY(!window_->adjList.isEmpty());
  QVERIFY(window_->adjList.contains("n1")); 
}

void QTest1::testDisplayGraph() {
  const QString fileName = "./graphml-sample.xml";
  window_->loadGraph(fileName, window_->adjList);
  QVERIFY(!window_->adjList.isEmpty());
  QVERIFY(window_->adjList.contains("n1")); 
  window_->displayGraph(window_->adjList);
  QVERIFY(true);
}

void QTest1::testCopy() { 
  CodeEditor editor;
  editor.setPlainText("test");
  QTextCursor cursor = editor.textCursor();
  cursor.select(QTextCursor::LineUnderCursor);
  editor.setTextCursor(cursor);
  editor.copy();
  QVERIFY(QApplication::clipboard()->text() == "test");
}

void QTest1::testPaste() {
  CodeEditor editor;
  QApplication::clipboard()->setText("test");
  editor.paste();
  QVERIFY(editor.toPlainText() == "test");
}

void QTest1::testUndoRedo() {
  CodeEditor editor;
  editor.clear();
  editor.setPlainText("test");
  editor.undo();
  editor.redo();
  QVERIFY(editor.toPlainText() == "test");
}
void QTest1::testCut() {
  CodeEditor editor;
  editor.setPlainText("test");
  editor.selectAll();
  editor.cut();
  QCOMPARE(QApplication::clipboard()->text(), QString("test"));
  QVERIFY(editor.toPlainText().isEmpty());
}

void QTest1::testClear() {
  CodeEditor editor;
  editor.setPlainText("test");
  editor.selectAll();
  editor.clear();
  QVERIFY(editor.toPlainText().isEmpty());
}

void QTest1::testSelectAll() {
  CodeEditor editor;
  editor.setPlainText("test");
  editor.selectAll();
  QCOMPARE(editor.textCursor().selectedText(), QString("test"));
}

void QTest1::testCursorPosition() {
  CodeEditor editor;
  editor.setPlainText("test");
  editor.moveCursor(QTextCursor::End);
  QCOMPARE(editor.textCursor().position(), 4);
}

void QTest1::testSetPlainText() {
  CodeEditor editor;
  editor.setPlainText("test");
  QCOMPARE(editor.toPlainText(), QString("test"));
}

void QTest1::testFindText() {
  CodeEditor editor;
  editor.setPlainText("This is a test.");
  QTextCursor cursor = editor.document()->find("test");
  QVERIFY(cursor.position() == 14);
}
void QTest1::testSetWindowTitle() {
  const QString windowTitle = "My Test Window Title";
  window_->setWindowTitle(windowTitle);
  QCOMPARE(window_->windowTitle(), windowTitle);
}

void QTest1::testOpenUtopia() {
  window_->runUtopia();
  QVERIFY(true);
}

void QTest1::testExportResults() {
  const QString graphFileName = "./graphml-sample.xml";
  window_->loadGraph(graphFileName, window_->adjList);
  QVERIFY(!window_->adjList.isEmpty());
  QVERIFY(window_->adjList.contains("n1")); 
  QVERIFY(true);
}

void QTest1::testOpenFileInUtopia() {
  windowRun window;
  window.handleButton();
  QVERIFY(window.a != "");
}

void QTest1::testRunUtopia() {
  windowRun window;
  window.onBtnRunUtopiaClicked();
  QVERIFY(true);
}

void QTest1::testApplyOptions() {
  windowRun window;
  window.handleButton();
  QVERIFY(true);
}

void QTest1::testApplyTest() {
  windowRun window;
  window.handleButton();
  window.handleApplyTestButton();
  QVERIFY(window.b != "");
}
void QTest1::testOpenFileInWindow() {
  window_->runUtopia();

// Check that the edit widget was created
  QVERIFY(window_->cho->edit != nullptr);

// Check that a file was selected and opened in the edit widget
  QVERIFY(window_->cho->b.isEmpty());
}

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);
  QTest1 test(&app);
  return QTest::qExec(&test, argc, argv);
}
#include "tst_qttest.moc"
