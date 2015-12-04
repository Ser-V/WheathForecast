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
#include <QPushButton>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QTextEdit>

#include "Form.h"

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

  connect(firstBtnsLayout, SIGNAL(clicked()), this, SLOT(loadFirstTable()));
  connect(firstAddRowBtn, SIGNAL(clicked()), this, SLOT(addRowToFisrtTable()));
  connect(firstRemoveRowBtn, SIGNAL(clicked()), this, SLOT(removeRowFromFisrtTable()));
  
  QGroupBox* secondTabelGBox = new QGroupBox(tr("Group B"));
  QVBoxLayout* secondTableLayout = new QVBoxLayout(secondTabelGBox);
  m_secondTabel = new QTableWidget();
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

  connect(secondBtnsLayout, SIGNAL(clicked()), this, SLOT(loadSecondTable()));
  connect(secondAddRowBtn, SIGNAL(clicked()), this, SLOT(addRowToSecondTable()));
  connect(secondRemoveRowBtn, SIGNAL(clicked()), this, SLOT(removeRowFromSecondTable()));

  tabelLayout->addWidget(firstTabelGBox);
  tabelLayout->addWidget(secondTabelGBox);

  QHBoxLayout* calcBtnLayout = new QHBoxLayout();
  QPushButton* calcByAvarageValueBtn = new QPushButton(tr("Calculate by average value"));
  QPushButton* calcByRegionBtn = new QPushButton(tr("Calculate by region"));
  QPushButton* calcByMinValueBtn = new QPushButton(tr("Calculate by min value"));
  calcBtnLayout->addWidget(calcByAvarageValueBtn);
  calcBtnLayout->addWidget(calcByRegionBtn);
  calcBtnLayout->addWidget(calcByMinValueBtn);
  
  QGroupBox* resultGBox = new QGroupBox(tr("Result"));
  QVBoxLayout* resultLayout = new QVBoxLayout(resultGBox);
  m_resultTEdit = new QTextEdit();
  resultLayout->addWidget(m_resultTEdit);

  mainLayout->addLayout(tabelLayout);
  mainLayout->addLayout(calcBtnLayout);
  mainLayout->addWidget(resultGBox);

  setMenuBar(menuBar);
  setCentralWidget(centralWidget);
}

void Form::loadFirstTable()
{
}

void Form::addRowToFisrtTable()
{
}

void Form::removeRowFromFisrtTable()
{
}

void Form::loadSecondTable()
{
}

void Form::addRowToSecondTable()
{
}

void Form::removeRowFromSecondTable()
{
}