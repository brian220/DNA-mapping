#ifndef __TABLEENTITY_CPP_INCLUDED__
#define __TABLEENTITY_CPP_INCLUDED__

#include <iostream>
#include <vector>
using namespace std;

class TableEntity {
  public:
    int num;
    string dir;
  TableEntity():num(0), dir("None"){}
};

class PrintTable {
  //for debug
  public:
  void printTable(vector<vector<TableEntity>> matchTable){
    for (int i = 0; i < matchTable.size(); i ++) {
      for (int j = 0; j < matchTable[0].size(); j ++) {
        cout << matchTable[i][j].num << ", ";
      }
      cout << endl;
    }
  }
};

#endif
