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

void MainWindow::displayGraph(QMap<QString, QVector<QString>>& adjList) {
  // Set up the parameters for the layout
  qreal k = 0.2;
  qreal damping = 0.9;
  qreal threshold = 0.1;
  qreal nodeSize = 25;

  // Set up the initial positions of the nodes
  QMap<QString, QPointF> positions;
  qreal x = 0.0;
  qreal y = 0.0;
  qreal delta = 2 * M_PI / adjList.size();
  for (const QString& key : adjList.keys()) {
    positions[key] = QPointF(400 + 200 * cos(x), 300 + 200 * sin(y));
    x += delta;
    y += delta;
    }

    // Create the scene and add the nodes
  QGraphicsScene* scene = new QGraphicsScene();
  QMap<QString, QGraphicsEllipseItem*> nodes;
  for (const QString& key : adjList.keys()) {
    qreal x = positions[key].x();
    qreal y = positions[key].y();
    QGraphicsEllipseItem* node = scene->addEllipse(QRectF(x - nodeSize/2, y - nodeSize/2, nodeSize, nodeSize));
    node->setBrush(Qt::blue);
    nodes[key] = node;
    QGraphicsTextItem* label = new QGraphicsTextItem(key);
    label->setPos((x - nodeSize / 4) - 20, (y - nodeSize / 4) + 15);
    scene->addItem(label);
    }

    // Add the edges
  for (const QString& key : adjList.keys()) {
    for (const QString& neighbor : adjList[key]) {
      QGraphicsLineItem* edge = scene->addLine(QLineF(positions[key], positions[neighbor]));
      edge->setPen(QPen(Qt::black, 1));
      }
  }

    // Perform the layout
  qreal energy = 0.0;
  do {
    energy = 0.0;
    for (const QString& key1 : adjList.keys()) {
      for (const QString& key2 : adjList.keys()) {
        if (key1 == key2) {
          continue;
        }
        QPointF delta = positions[key2] - positions[key1];
        qreal distance = qMax(delta.manhattanLength(), qreal(1.0));
        QPointF force = delta / distance * k;
        force -= positions[key1] * damping;
        positions[key1] += force;
        nodes[key1]->setPos(positions[key1]);
        energy += force.x() * force.x() + force.y() * force.y();
        }
    }
  } while (energy > threshold);

  // Create the view and show it
  QGraphicsView* view = new QGraphicsView(scene);
  view->setRenderHint(QPainter::Antialiasing);
  view->setWindowTitle("Graph");
  view->show();
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
