#include <QtCore/QCoreApplication>
#include <QtCore/QFile>
#include <QGroupBox>
#include <QDoubleValidator>
#include <QFileDialog>
#include <QLabel>
#include <QLayout>
#include <QLineEdit>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QPushButton>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QTextEdit>
#include <QTextStream>

#include "Form.h"

const QString splitRegExp = "[\\s\t]";

Form::Form(QWidget* parent) : QMainWindow(parent), m_dimension(-1)
{
  creatActions();
  createContent();
}

Form::~Form()
{
}

void Form::creatActions()
{
  m_closeAction = new QAction(tr("Close"), this);

  connect(m_closeAction, SIGNAL(triggered()), QCoreApplication::instance(), SLOT(quit()));
}

void Form::createContent()
{
  QMenuBar* menuBar = new QMenuBar;
  QMenu* fileMenu = new QMenu(tr("File"));
  fileMenu->addAction(m_closeAction);
  menuBar->addMenu(fileMenu);

  QWidget* centralWidget = new QWidget();
  QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);
  
  QHBoxLayout* tabelLayout = new QHBoxLayout();
  QGroupBox* firstTabelGBox = new QGroupBox(tr("Groups"));
  QVBoxLayout* firstTableLayout = new QVBoxLayout(firstTabelGBox);
  m_firstTabel = new QTableWidget();
  m_firstTabel->setColumnCount(2);
  QHBoxLayout* firstBtnsLayout = new QHBoxLayout();
  QPushButton* firstLoadFroFileBtn = new QPushButton(tr("Load from file"));
  QPushButton* firstAddRowBtn = new QPushButton(tr("Add"));
  QPushButton* firstRemoveRowBtn = new QPushButton(tr("Remove"));
  firstBtnsLayout->addWidget(firstLoadFroFileBtn);
  firstBtnsLayout->addStretch();
  firstBtnsLayout->addWidget(firstAddRowBtn);
  firstBtnsLayout->addWidget(firstRemoveRowBtn);
  firstTableLayout->addWidget(m_firstTabel);
  firstTableLayout->addLayout(firstBtnsLayout);

  connect(firstLoadFroFileBtn, SIGNAL(clicked()), this, SLOT(loadFirstTable()));
  connect(firstAddRowBtn, SIGNAL(clicked()), this, SLOT(addRowToFisrtTable()));
  connect(firstRemoveRowBtn, SIGNAL(clicked()), this, SLOT(removeRowFromFisrtTable()));

  tabelLayout->addWidget(firstTabelGBox);

  QHBoxLayout* calcBtnLayout = new QHBoxLayout();
  QPushButton* calcByAverageValueBtn = new QPushButton(tr("Calculate by average value"));
  QPushButton* calcByRegionBtn = new QPushButton(tr("Calculate by region"));
  QPushButton* calcByMinValueBtn = new QPushButton(tr("Calculate by min value"));
  calcBtnLayout->addWidget(calcByAverageValueBtn);
  calcBtnLayout->addWidget(calcByRegionBtn);
  calcBtnLayout->addWidget(calcByMinValueBtn);

  connect(calcByAverageValueBtn, SIGNAL(clicked()), this, SLOT(calByAverageValue()));
  connect(calcByRegionBtn, SIGNAL(clicked()), this, SLOT(calByRegion()));
  connect(calcByMinValueBtn, SIGNAL(clicked()), this, SLOT(calByMinValue()));
  
  QGroupBox* checkGBox = new QGroupBox(tr("Test data"));
  QVBoxLayout* checkLayout = new QVBoxLayout(checkGBox);
  QHBoxLayout* checkBtnsLayout = new QHBoxLayout();
  QPushButton* checkLoadFromFileBtn = new QPushButton(tr("Load from file"));
  QPushButton* checkSaveBtn = new QPushButton(tr("Save"));
  QPushButton* checkAddRowBtn = new QPushButton(tr("Add"));
  QPushButton* checkRemoveRowBtn = new QPushButton(tr("Remove"));
  checkBtnsLayout->addWidget(checkLoadFromFileBtn);
  checkBtnsLayout->addWidget(checkSaveBtn);
  checkBtnsLayout->addStretch();
  checkBtnsLayout->addWidget(checkAddRowBtn);
  checkBtnsLayout->addWidget(checkRemoveRowBtn);
  m_checkTable = new QTableWidget();
  m_checkTable->setColumnCount(3);
  checkLayout->addWidget(m_checkTable);
  checkLayout->addLayout(checkBtnsLayout);

  connect(checkLoadFromFileBtn, SIGNAL(clicked()), this, SLOT(loadCheckTable()));
  connect(checkSaveBtn, SIGNAL(clicked()), this, SLOT(saveResult()));
  connect(checkAddRowBtn, SIGNAL(clicked()), this, SLOT(addRowToCheckTable()));
  connect(checkRemoveRowBtn, SIGNAL(clicked()), this, SLOT(removeRowFromCheckTable()));

  QGroupBox* resultGBox = new QGroupBox(tr("Result"));
  QVBoxLayout* resultLayout = new QVBoxLayout(resultGBox);
  m_resultTEdit = new QTextEdit();
  resultLayout->addWidget(m_resultTEdit);

  mainLayout->addLayout(tabelLayout);
  mainLayout->addWidget(checkGBox);
  mainLayout->addLayout(calcBtnLayout);
  mainLayout->addWidget(resultGBox);

  setMenuBar(menuBar);
  setCentralWidget(centralWidget);
}

void Form::loadDataToTable(QTableWidget* table, int additionColumns)
{
  if (!table)
    return;

  QString fileName = QFileDialog::getOpenFileName(this, tr("Open file"), QString(), "*.txt");
  if (fileName.isEmpty())
    return;

  QFile file(fileName);
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    return;

  int row = 0;
  while (!file.atEnd())
  {
    QString line = file.readLine();
    QStringList list = line.split(QRegExp(splitRegExp), QString::SkipEmptyParts);
    if (m_dimension < 0)
      m_dimension = list.count() - 1;
    /*
    if (list.count() != m_dimension)
    {
      QMessageBox::warning(this, tr("Loading"), tr("Dimension is different"), QMessageBox::Ok);
      return;
    }
    /**/
    if (table->columnCount() != list.count())
      table->setColumnCount(list.count() + additionColumns);
    table->setRowCount(row + 1);
    for (int i = 0; i < list.count(); ++i)
    {
      QTableWidgetItem* item = new QTableWidgetItem();
      double value = list.at(i).toDouble();
      item->setData(Qt::DisplayRole, value);
      table->setItem(row, i, item);
    }
    if (additionColumns > 0)
    {
      QTableWidgetItem* item = new QTableWidgetItem();
      item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
      table->setItem(row, table->columnCount() - additionColumns, item);
    }
    ++row;
  }
  if (additionColumns > 0)
  {
    QTableWidgetItem* item = new QTableWidgetItem(tr("Result"));
    table->setHorizontalHeaderItem(table->columnCount() - additionColumns, item);
  }
}

void Form::loadFirstTable()
{
  loadDataToTable(m_firstTabel);
}

void Form::addRowToFisrtTable()
{
  m_firstTabel->setRowCount(m_firstTabel->rowCount() + 1);
}

void Form::removeRowFromFisrtTable()
{
  m_firstTabel->removeRow(m_firstTabel->currentRow());
}

void Form::loadCheckTable()
{
  loadDataToTable(m_checkTable, 1);
}

void Form::saveResult()
{
  QString fileName = QFileDialog::getSaveFileName(this, tr("Save"), "", "*.txt;; *.csv");
  if (fileName.isEmpty())
    return;
  QFile file(fileName);

  if (!file.open(QIODevice::WriteOnly))
    return;

  QTextStream out(&file);
  for (int r = 0; r < m_checkTable->rowCount(); ++r)
  {
    for (int c = 0; c < m_checkTable->columnCount(); ++c)
    {
      QTableWidgetItem* item = m_checkTable->item(r, c);
      out << item->data(Qt::DisplayRole).toString() << "\t";
    }
    out << "\n";
  }
}

void Form::addRowToCheckTable()
{
  m_checkTable->setRowCount(m_checkTable->rowCount() + 1);
}

void Form::removeRowFromCheckTable()
{
  m_checkTable->removeRow(m_checkTable->currentRow());
}

QMap<QString, VectorList > Form::getDataFromTable(const QTableWidget* table) const
{
  QMap<QString, VectorList > map;
  if (!table)
    return map;

  for (int row = 0; row < table->rowCount(); ++row)
  {
    QVector<double> vector;
    QString group;
    for (int column = 0; column < table->columnCount() - 1; ++column)
    {
      QTableWidgetItem* item = table->item(row, column);
      if (!item)
        continue;
      vector.append(item->data(Qt::DisplayRole).toDouble());
    }
    QTableWidgetItem* item = table->item(row, table->columnCount() - 1);
    if (item)
      group = item->data(Qt::DisplayRole).toString();
    if (!group.isEmpty())
      map[group].append(vector);
  }

  return map;
}

void Form::calByAverageValue()
{
  QMap<QString, VectorList > groups = getDataFromTable(m_firstTabel);
  for (int vectorNum = 0; vectorNum < m_checkTable->rowCount(); ++vectorNum)
  {
    QVector<double> valueVector;
    for (int i = 0; i < m_checkTable->columnCount() - 1; ++i)
      valueVector.append(m_checkTable->item(vectorNum, i)->data(Qt::DisplayRole).toDouble());
    if (valueVector.count() != m_dimension)
    {
      m_resultTEdit->append(tr("Dimension error for row %1").arg(vectorNum));
      continue;
    }
    QList<QVector<double> > averageVectors;
    QString group = Utils::calcByAverage(groups, valueVector, averageVectors);
    if (!group.isEmpty())
    {
      QTableWidgetItem* item = new QTableWidgetItem();
      item->setData(Qt::DisplayRole, group);
      m_checkTable->setItem(vectorNum, m_checkTable->columnCount() - 1, item);
      QString avStr;
      for (int i = 0; i < averageVectors.count(); ++i)
      {
        avStr += "(";
        for (int j = 0; j < averageVectors.at(i).count(); ++j)
          avStr += QString::number(averageVectors.at(i).at(j), 'f', 1) + " ";
        avStr += ") ";
      }
      m_resultTEdit->append(tr("%1) Method by average value: group %2, average vectors %3").arg(vectorNum+1).arg(group).arg(avStr));
    }
  }
}

void Form::calByRegion()
{
  QMap<QString, VectorList > groups = getDataFromTable(m_firstTabel);
  for (int vectorNum = 0; vectorNum < m_checkTable->rowCount(); ++vectorNum)
  {
    QVector<double> valueVector;
    for (int i = 0; i < m_checkTable->columnCount() - 1; ++i)
      valueVector.append(m_checkTable->item(vectorNum, i)->data(Qt::DisplayRole).toDouble());
    if (valueVector.count() != m_dimension)
    {
      m_resultTEdit->append(tr("Dimension error for row %1").arg(vectorNum));
      continue;
    }
    double r;
    QString group = Utils::calcByRegion(groups, valueVector, r);
    if (!group.isEmpty())
    {
      QTableWidgetItem* item = new QTableWidgetItem();
      item->setData(Qt::DisplayRole, group);
      m_checkTable->setItem(vectorNum, m_checkTable->columnCount() - 1, item);
      m_resultTEdit->append(tr("%1) Method by region: group %2, radius %3").arg(vectorNum+1).arg(group).arg(r));
    }
  }
}

void Form::calByMinValue()
{
  QMap<QString, VectorList > groups = getDataFromTable(m_firstTabel);
  for (int vectorNum = 0; vectorNum < m_checkTable->rowCount(); ++vectorNum)
  {
    QVector<double> valueVector;
    for (int i = 0; i < m_checkTable->columnCount() - 1; ++i)
      valueVector.append(m_checkTable->item(vectorNum, i)->data(Qt::DisplayRole).toDouble());

    if (valueVector.count() != m_dimension)
    {
      m_resultTEdit->append(tr("Dimension error for row %1").arg(vectorNum));
      continue;
    }
    QVector<double> minP;
    QString group = Utils::calcByMinValue(groups, valueVector, minP);
    if (!group.isEmpty())
    {
      QTableWidgetItem* item = new QTableWidgetItem();
      item->setData(Qt::DisplayRole, group);
      m_checkTable->setItem(vectorNum, m_checkTable->columnCount() - 1, item);
    }
    QString mpStr;
    for (int i = 0; i < minP.count(); ++i)
      mpStr += QString::number(minP.at(i)) + " ";
    m_resultTEdit->append(tr("%1) Method by min value: group %2, min point (%3)").arg(vectorNum+1).arg(group).arg(mpStr));
  }
}