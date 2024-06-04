#include <QMainWindow>
#include <QPushButton>
#include <QTableWidget>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QWidget>
#include <QMessageBox>
#include <QStackedWidget>

#include <iostream>
//#include "scan_table.h"
#include "table.h"

class MainWindow : public QMainWindow {
  Q_OBJECT
public:
  MainWindow(QWidget* parent = nullptr);
    
private:
  QStackedWidget* stackedWidget;
  QTableWidget* tableWidget;

private slots:
  void showMainPage();
  void showTableChoicePage();
  void showTablePage();
};