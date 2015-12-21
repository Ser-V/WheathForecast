#ifndef FORM_H
#define FORM_H

#include <QMainWindow>

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

  void loadSecondTable();
  void addRowToSecondTable();
  void removeRowFromSecondTable();

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
  QList<QVector<double> > getDataFromTable(QTableWidget* table);

private:
  QAction* m_closeAction;

  QTableWidget* m_firstTabel;
  QTableWidget* m_secondTabel;
  QTableWidget* m_checkTable;
  QLineEdit* m_valueLEdit;
  QTextEdit* m_resultTEdit;

  int m_dimension;
};

#endif /* FORM_H */
