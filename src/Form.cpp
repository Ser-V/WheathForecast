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
#include <QTextCodec>
#include <QTextEdit>
#include <QTextStream>

#include "Form.h"

const QString splitRegExp = "[\\s\t]";

Form::Form(QWidget* parent) : QMainWindow(parent), m_dimension(-1)
{
  setWindowTitle(tr("Weather forecast"));
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
  QGroupBox* firstTabelGBox = new QGroupBox(tr("Training sample"));
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
  
  QGroupBox* checkGBox = new QGroupBox(tr("Control sample"));
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
  
  table->clear();
  int row = -1;
  while (!file.atEnd())
  {
    QString line = QTextCodec::codecForLocale()->toUnicode(file.readLine());
    QStringList list = line.split(QRegExp(splitRegExp), QString::SkipEmptyParts);
    //if (m_dimension < 0)
      //m_dimension = list.count() - additionColumns;
    /*
    if (list.count() != m_dimension)
    {
      QMessageBox::warning(this, tr("Loading"), tr("Dimension is different"), QMessageBox::Ok);
      return;
    }
    /**/
    if (row == -1)
    {
      if (table->columnCount() != list.count() + additionColumns)
        table->setColumnCount(list.count() + additionColumns);
      for (int i = 0; i < list.count(); ++i)
      {
        QTableWidgetItem* item = new QTableWidgetItem();
        item->setData(Qt::DisplayRole, (list.at(i)));
        table->setHorizontalHeaderItem(i, item);
      }
    }
    else
    {
      table->setRowCount(row + 1);
      for (int i = 0; i < list.count(); ++i)
      {
        QTableWidgetItem* item = new QTableWidgetItem();
        item->setData(Qt::DisplayRole, list.at(i));
        table->setItem(row, i, item);
      }
      if (additionColumns > 0)
      {
        QTableWidgetItem* item = new QTableWidgetItem();
        item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        table->setItem(row, table->columnCount() - additionColumns, item);
      }
      if (table->columnCount() != list.count() + additionColumns)
      {
        QMessageBox::warning(this, tr("Loading data"), tr("Dimension is different. Line %1").arg(row + 1), QMessageBox::Ok);
          return;
      }
    }
    ++row;
  }
  if (additionColumns > 0)
  {
    QTableWidgetItem* item = new QTableWidgetItem(tr("Phenomenon"));
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

  QString separator = fileName.split(".").last() == "csv" ? ";" : "\t";
  QTextStream out(&file);
  for (int c = 0; c < m_checkTable->columnCount(); ++c)
  {
    QTableWidgetItem* item = m_checkTable->horizontalHeaderItem(c);
    if (item)
      out << item->data(Qt::DisplayRole).toString() << separator;
  }
  out << "\r\n";
  for (int r = 0; r < m_checkTable->rowCount(); ++r)
  {
    for (int c = 0; c < m_checkTable->columnCount(); ++c)
    {
      QTableWidgetItem* item = m_checkTable->item(r, c);
      if (item)
        out << item->data(Qt::DisplayRole).toString() << separator;
    }
    out << "\r\n";
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

  QLocale locale = QLocale::system();
  for (int row = 0; row < table->rowCount(); ++row)
  {
    QVector<double> vector;
    QString group;
    for (int column = 0; column < table->columnCount() - 1; ++column)
    {
      QTableWidgetItem* item = table->item(row, column);
      if (!item)
        continue;
      vector.append(locale.toDouble(item->data(Qt::DisplayRole).toString()));
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
  m_resultTEdit->clear();
  QLocale locale = QLocale::system();
  QMap<QString, VectorList > groups = getDataFromTable(m_firstTabel);
  bool isAverageClac = false;
  for (int vectorNum = 0; vectorNum < m_checkTable->rowCount(); ++vectorNum)
  {
    QVector<double> valueVector;
    for (int i = 0; i < m_checkTable->columnCount() - 1; ++i)
    {
      QTableWidgetItem* item = m_checkTable->item(vectorNum, i);
      if (!item)
        continue;
      valueVector.append(locale.toDouble(item->data(Qt::DisplayRole).toString()));
    }
    /*
    if (valueVector.count() != m_dimension)
    {
      m_resultTEdit->append(tr("Dimension error for row %1").arg(vectorNum));
      continue;
    }
    /* */
    Utils::AverageCalcOutput output;
    QString group = Utils::calcByAverage(groups, valueVector, output);
    if (!output.error.isEmpty())
    {
      m_resultTEdit->append(tr("%1) Error. %2").arg(vectorNum+1).arg(output.error));
    }
    else if (!group.isEmpty())
    {
      QTableWidgetItem* item = new QTableWidgetItem();
      item->setData(Qt::DisplayRole, group);
      m_checkTable->setItem(vectorNum, m_checkTable->columnCount() - 1, item);
      if (!isAverageClac)
      {
        for (QMap< QString, QVector<double> >::const_iterator cit = output.averagePoints.cbegin(); cit != output.averagePoints.cend(); ++cit)
        {
          QString avStr = "(";
          for (int j = 0; j < (*cit).count(); ++j)
            avStr += QString::number((*cit).at(j), 'f', 1)
            + ((j != (*cit).count() - 1) ? "; " : "");
          avStr += ")";
          m_resultTEdit->append(tr("Phenomenon %1 - average vectors %2").arg(cit.key()).arg(avStr));
        }
        isAverageClac = true;
      }
      m_resultTEdit->append(tr("%1) Method by average value: Phenomenon %2, distance %3").arg(vectorNum+1).arg(group).arg(output.distance, 0, 'f', 1));
    }
  }
}

void Form::calByRegion()
{
  m_resultTEdit->clear();
  QMap<QString, VectorList > groups = getDataFromTable(m_firstTabel);
  for (int vectorNum = 0; vectorNum < m_checkTable->rowCount(); ++vectorNum)
  {
    QVector<double> valueVector;
    for (int i = 0; i < m_checkTable->columnCount() - 1; ++i)
    {
      QTableWidgetItem* item = m_checkTable->item(vectorNum, i);
      if (!item)
        continue;
      valueVector.append(item->data(Qt::DisplayRole).toDouble());
    }
    /*
    if (valueVector.count() != m_dimension)
    {
      m_resultTEdit->append(tr("Dimension error for row %1").arg(vectorNum));
      continue;
    }
    /* */
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
  m_resultTEdit->clear();
  QMap<QString, VectorList > groups = getDataFromTable(m_firstTabel);
  for (int vectorNum = 0; vectorNum < m_checkTable->rowCount(); ++vectorNum)
  {
    QVector<double> valueVector;
    for (int i = 0; i < m_checkTable->columnCount() - 1; ++i)
      valueVector.append(m_checkTable->item(vectorNum, i)->data(Qt::DisplayRole).toDouble());
    /*
    if (valueVector.count() != m_dimension)
    {
      m_resultTEdit->append(tr("Dimension error for row %1").arg(vectorNum));
      continue;
    }
    /* */
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