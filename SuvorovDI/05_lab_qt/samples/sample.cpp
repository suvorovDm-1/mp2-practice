#include <QApplication>
#include "MainWindow.h"
// #include "table.h"
// #include "array_hash_table.h"
#include "table.h"
#include "scan_table.h"

using namespace my_namespace;

int main(int argc, char* argv[]) {
  QApplication app(argc, argv);
  MainWindow mainWindow;
  mainWindow.show();

  return app.exec();

  

  return 0;
}