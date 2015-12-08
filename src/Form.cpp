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

#include "Form.h"
#include "Utils.h"

Form::Form(QWidget* parent) : QMainWindow(parent)
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
  QGroupBox* firstTabelGBox = new QGroupBox(tr("Group A"));
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
  
  QGroupBox* secondTabelGBox = new QGroupBox(tr("Group B"));
  QVBoxLayout* secondTableLayout = new QVBoxLayout(secondTabelGBox);
  m_secondTabel = new QTableWidget();
  m_secondTabel->setColumnCount(2);
  QHBoxLayout* secondBtnsLayout = new QHBoxLayout();
  QPushButton* secondLoadFroFileBtn = new QPushButton(tr("Load from file"));
  QPushButton* secondAddRowBtn = new QPushButton(tr("Add"));
  QPushButton* secondRemoveRowBtn = new QPushButton(tr("Remove"));
  secondBtnsLayout->addWidget(secondLoadFroFileBtn);
  secondBtnsLayout->addStretch();
  secondBtnsLayout->addWidget(secondAddRowBtn);
  secondBtnsLayout->addWidget(secondRemoveRowBtn);
  secondTableLayout->addWidget(m_secondTabel);
  secondTableLayout->addLayout(secondBtnsLayout);

  connect(secondLoadFroFileBtn, SIGNAL(clicked()), this, SLOT(loadSecondTable()));
  connect(secondAddRowBtn, SIGNAL(clicked()), this, SLOT(addRowToSecondTable()));
  connect(secondRemoveRowBtn, SIGNAL(clicked()), this, SLOT(removeRowFromSecondTable()));

  tabelLayout->addWidget(firstTabelGBox);
  tabelLayout->addWidget(secondTabelGBox);

  m_valueLEdit = new QLineEdit();
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
  
  QGroupBox* resultGBox = new QGroupBox(tr("Result"));
  QVBoxLayout* resultLayout = new QVBoxLayout(resultGBox);
  m_resultTEdit = new QTextEdit();
  resultLayout->addWidget(m_resultTEdit);

  mainLayout->addLayout(tabelLayout);
  mainLayout->addWidget(m_valueLEdit);
  mainLayout->addLayout(calcBtnLayout);
  mainLayout->addWidget(resultGBox);

  setMenuBar(menuBar);
  setCentralWidget(centralWidget);
}

void Form::loadDataToTable(QTableWidget* table)
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
    QStringList list = line.split(" ");
    if (list.count() != 2)
    {
      QMessageBox::warning(this, tr("Loading"), tr("Supported only 2 dimension"), QMessageBox::Ok);
      return;
    }
    table->setRowCount(row + 1);
    for (int i = 0; i < list.count(); ++i)
    {
      QTableWidgetItem* item = new QTableWidgetItem();
      double value = list.at(i).toDouble();
      item->setData(Qt::DisplayRole, value);
      table->setItem(row, i, item);
    }
    ++row;
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

void Form::loadSecondTable()
{
  loadDataToTable(m_secondTabel);
}

void Form::addRowToSecondTable()
{
  m_secondTabel->setRowCount(m_secondTabel->rowCount() + 1);
}

void Form::removeRowFromSecondTable()
{
  m_secondTabel->removeRow(m_secondTabel->currentRow());
}

QList<QVector<double> > Form::getDataFromTable(QTableWidget* table)
{
  QList<QVector<double> > group;
  if (!table)
    return group;

  for (int row = 0; row < table->rowCount(); ++row)
  {
    QVector<double> vector;
    for (int column = 0; column < table->columnCount(); ++column)
    {
      QTableWidgetItem* item = table->item(row, column);
      if (!item)
        continue;
      vector.append(item->data(Qt::DisplayRole).toDouble());
    }
    group.append(vector);
  }
  return group;
}

void Form::calByAverageValue()
{
  QList<QList<QVector<double> > > groups;
  groups.append(getDataFromTable(m_firstTabel));
  groups.append(getDataFromTable(m_secondTabel));
  QString valueStr = m_valueLEdit->text();
  QStringList valueStrList = valueStr.split(" ");
  QVector<double> valueVector;
  for (int i = 0; i < valueStrList.count(); ++i)
    valueVector.append(valueStrList.at(i).toDouble());
  if (valueVector.count() != 2)
  {
    QMessageBox::warning(this, tr("Loading"), tr("Supported only 2 dimension"), QMessageBox::Ok);
    return;
  }
  int groupNum = Utils::calcByAverage(groups, valueVector);
  if (groupNum == -1)
  {
    m_resultTEdit->append(tr("No resulte"));
    return;
  }
  m_resultTEdit->append(tr("Method by average value: group %1").arg(groupNum+1));
}

void Form::calByRegion()
{
}

void Form::calByMinValue()
{
}