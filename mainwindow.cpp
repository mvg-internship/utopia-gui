#include "mainwindow.h"
#include <QString>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent) {
  setWindowTitle(tr("Utopia"));
  setMenu();
  QString save_results = "";
  QString pathOpenfile = "";
}

MainWindow::~MainWindow(){
  delete menu;
}

void MainWindow::execSettings(const QString &path) {
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
void MainWindow::openFile(const QString &path) {
  QString fileName = pathFile;
  if (fileName.isNull()) {

    fileName = QFileDialog::getOpenFileName(this, tr("Open File"), shellVariable1+"test/data/ril/test.ril", tr("RIL Files (*.ril)"));
    pathOpenfile = fileName;
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
    qDebug() << "the file did not open";
  }

}

void MainWindow::save() {
    
  QString fileName = pathOpenfile;
  if (fileName != "") {
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly)) {
      qDebug() << "the file did not open";
    } else {
      QTextStream stream(&file);
      stream << edit->toPlainText();
      stream.flush();
      file.close();
    }
  }
}
void MainWindow::SaveAs() {
    
  QString fileName = QFileDialog::getSaveFileName(this, tr("Save as"), shellVariable1+"test/data/ril/test.ril",tr("Text file (*.txt );; RIL file (*.ril )"));
  if (fileName != "") {
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly)) {
      qDebug() << "the file did not open";
    } else {
      QTextStream stream(&file);
      stream << edit->toPlainText();
      stream.flush();
      file.close();
      }
    }
}
void MainWindow::runUtopia() {
  cho = new windowRun(this);
  cho->show();
}


void MainWindow::loadGraph(QString filename, QMap<QString, QVector<QString>> &adjList){
  QFile file(filename);
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
  qDebug() << "Failed to open file";
  return;
  }

  QXmlStreamReader xmlReader(&file);

  QString currentElement;
  QString source, target;

  while (!xmlReader.atEnd() && !xmlReader.hasError()) {
    QXmlStreamReader::TokenType token = xmlReader.readNext();

    if (token == QXmlStreamReader::StartElement) {
      if (xmlReader.name().compare(QString("node")) == 0) {
        currentElement = xmlReader.attributes().value("id").toString();
        adjList[currentElement] = QVector<QString>();
      }
      if (xmlReader.name().compare(QString("edge")) == 0){
        source = xmlReader.attributes().value("source").toString();
        target = xmlReader.attributes().value("target").toString();
        adjList[source].append(target);
        adjList[target].append(source);
      }
    }
  }

  file.close();
}

void MainWindow::displayGraph(QMap<QString, QVector<QString>> &adjList) {
  GVC_t *gvc;
  Agraph_t *g;
  Agnode_t *n, *m;
  Agedge_t *e;

  gvc = gvContext();

  g = agopen("G", Agdirected, NULL);

  QMap<QString, Agnode_t*> nodes;
  for (const QString& key : adjList.keys()) {
    n = agnode(g, NULL, TRUE);
    agsafeset(n, const_cast<char*>("label"), const_cast<char*>(key.toUtf8().constData()), const_cast<char*>(""));
    nodes[key] = n;
  }

  for (const QString& key : adjList.keys()) {
    for (const QString& neighbor : adjList[key]) {
      n = nodes[key];
      m = nodes[neighbor];
      e = agedge(g, n, m, NULL, TRUE);
    }
  }

  gvLayout(gvc, g, "dot");

  char *renderData;
  unsigned int renderDataLength;
  gvRenderData(gvc, g, "png", &renderData, &renderDataLength);

  QImage image;
  image.loadFromData((uchar*)renderData, renderDataLength);

  QGraphicsScene *scene = new QGraphicsScene();
  QGraphicsPixmapItem *item = new QGraphicsPixmapItem(QPixmap::fromImage(image));
  scene->addItem(item);
  QGraphicsView *view = new QGraphicsView(scene);
  view->setWindowTitle("Graph");
  view->show();

  gvFreeRenderData(renderData);
  gvFreeLayout(gvc, g);
  agclose(g);
  gvFreeContext(gvc);
}
void MainWindow::exportResults(){
  QMap<QString, QVector<QString>> adjList;
  QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), shellVariable1+"test/data/ril/test.ril", tr("XML Files (*.xml)"));

  loadGraph(fileName, adjList);
  displayGraph(adjList);
}

void MainWindow::setMenu(){
    
  menu = menuBar()->addMenu(tr("&File"));
  menu->addAction(tr("Open file"), this, SLOT(openFile()), QKeySequence(tr("Ctrl+N","File|New")));
  menu->addAction(tr("Save file"), this, SLOT(save()), QKeySequence(tr("Ctrl+S","File|Save")));
  menu->addAction(tr("Save as file"), this, SLOT(SaveAs()), QKeySequence(tr("Ctrl+T","File|Save as")));
  menu->addAction(tr("Export"), this, SLOT(exportResults()), QKeySequence(tr("Ctrl+E","File|Export")));

  menu = menuBar()->addMenu(tr("&Run"));
  menu->addAction(tr("Run"), this, SLOT(runUtopia()), QKeySequence(tr("Ctrl+R","File|New")));
}
