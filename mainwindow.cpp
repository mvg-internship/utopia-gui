#include "mainwindow.h"
#include <QString>
#include <filesystem>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent) {
  setWindowTitle(tr("Utopia"));
  setMenu();
  QString save_results = "";
  QString pathOpenfile = "";
}

MainWindow::~MainWindow(){
  delete menu;
}

void MainWindow::openFile(const QString &path) {
  QString fileName = path;
  if (fileName.isNull()) {
    std::filesystem::path filePath(shellVariable1.toStdString());
    std::filesystem::path fullPath = filePath / "test/data/ril/test.ril";
    fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QString::fromStdString(fullPath.string()), tr("RIL Files (*.ril)"));
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
      return;
    }
    else {
      qDebug() << "Failed to open file: ";
    }
  }
  else {
    qDebug() << "No file selected: ";
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
  std::filesystem::path filePath(shellVariable1.toStdString());
  std::filesystem::path fullPath = filePath / "test/data/ril/test.ril";
  QString fileName = QFileDialog::getSaveFileName(this, tr("Save as"), QString::fromStdString(fullPath.string()),tr("Text file (*.txt );; RIL file (*.ril )"));
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
  connect(cho, &windowRun::fileSelected, this, &MainWindow::openFileinWindow);
}


void MainWindow::loadGraph(QString filename, QMap<QString, QVector<QString>> &adjList){
  QFile file(filename);
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
  qDebug() << "Failed to open file: ";
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

  char graphName[] = "G";
  g = agopen(graphName, Agdirected, nullptr);

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
  std::filesystem::path filePath(shellVariable1.toStdString());
  std::filesystem::path fullPath = filePath / "test/data/ril/test.ril";

  QStringList filters;
  filters << "XML Files (*.xml)" << "Verilog Files (*.v)" << "Bench Files (*bench)";
  QString filterString = filters.join(";;");
  QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QString::fromStdString(fullPath.string()), filterString);//choose a file

  if (!fileName.isEmpty()) {
    if (fileName.endsWith(".xml", Qt::CaseInsensitive)) {
      loadGraph(fileName, adjList);
      displayGraph(adjList);
    } else if (fileName.endsWith(".v", Qt::CaseInsensitive)) {
      cho = new windowRun(this);
      cho->b = fileName;
      cho->text = " ";//here will be the option which need to generate xml file
      cho->onBtnRunUtopiaClicked();//run Utopia
    } else if (fileName.endsWith(".bench", Qt::CaseInsensitive)) {
      bench = new windowBench(this);
      bench->filename = fileName;
      bench->show();
    }
  } else {
    qDebug() << "No file selected";
  }
}


void MainWindow::openFileinWindow(const QString &filePath) {
  if (!filePath.isEmpty()) {
    openFile(filePath);
  }
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
