//#include <QApplication>
#include "table.h"
#include "array_hash_table.h"

using namespace my_namespace;

int main(int argc, char* argv[]) {
  // QApplication app(argc, argv);
  // MainWindow mainWindow;
  // mainWindow.show();

  // return app.exec();

  ArrayHashTable<int, int> a(10, 3);

  return 0;
}