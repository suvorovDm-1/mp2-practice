#include <iostream>
#include "array_hash_table.h"

int main() {
  try {
    ArrayHashTable<std::string, int> scan_table(100, 11);
     scan_table.Insert("t", new int(2));
     scan_table.Insert("rrt", new int(5));
     scan_table.Insert("cw", new int(23));
     /*scan_table.Remove("trgw");*/
     scan_table.Insert("dg", new int(545));
     scan_table.Insert("fsdfa", new int(2333));
     /*std::cout << *scan_table.Find("dg");*/
     std::cout << scan_table;
  }
  catch (std::exception ex) {
    std::cout << ex.what();
  }

  return 0;
}