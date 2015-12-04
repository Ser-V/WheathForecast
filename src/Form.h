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

private:
  void creatActions();
  void createContent();

private:
  QAction* m_closeAction;

  QTableWidget* m_firstTabel;
  QTableWidget* m_secondTabel;
  QTextEdit* m_resultTEdit;
};

#endif /* FORM_H */
