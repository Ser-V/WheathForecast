#ifndef FORM_H
#define FORM_H

#include <QMainWindow>

#include "Utils.h"

class QAction;
class QLineEdit;
class QTableWidget;
class QTextEdit;

class Form : public QMainWindow
{
  Q_OBJECT

public:
  Form(QWidget* parent = 0x0);
  ~Form();

private slots:
  void loadFirstTable();
  void addRowToFisrtTable();
  void removeRowFromFisrtTable();

  void loadCheckTable();
  void saveResult();
  void addRowToCheckTable();
  void removeRowFromCheckTable();

  void calByAverageValue();
  void calByRegion();
  void calByMinValue();

private:
  void creatActions();
  void createContent();

  void loadDataToTable(QTableWidget* table, int additionColumns = 0);
  QMap<QString, VectorList > getDataFromTable(const QTableWidget* table) const;

private:
  QAction* m_closeAction;

  QTableWidget* m_firstTabel;
  QTableWidget* m_checkTable;
  QTextEdit* m_resultTEdit;

  int m_dimension;
};

#endif /* FORM_H */
