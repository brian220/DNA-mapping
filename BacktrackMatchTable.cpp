#include "TableEntity.cpp"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class BacktrackMatchTable {
  private:
    vector<vector<TableEntity>> matchTable;
    string a;
    string b;

    string aResult;
    string bResult;
    int matchLength = 0;

    int currentIndex = 0;
    int i = 0;
    int j = 0;

  public:
    BacktrackMatchTable(string a, string b, vector<vector<TableEntity>> matchTable) {
      this -> a = a;
      this -> b = b;
      this -> matchTable = matchTable;
    }

    pair<string, string> backtrackingTable() {
      setResultLength();
      formResultString();
      return getResultStringPair();
    }

    void setResultLength() {
      matchLength =  max(a.length(), b.length());
      aResult.resize(matchLength);
      bResult.resize(matchLength);
    }

    pair<string, string> formResultString() {
      setBacktrackParameter();
      for (;currentIndex >= 0; currentIndex --) {
        storeResultFromTable();
      }
    }

    void setBacktrackParameter() {
      currentIndex = matchLength - 1;
      i = a.length();
      j = b.length();
    }

    void storeResultFromTable() {
      if (isDir("Left")) {
        storeResult('-', b[j - 1]);
        moveLeft();
      }
      else if (isDir("Up")) {
        storeResult(a[i - 1], '-');
        moveUp();
      }
      else if (isDir("Left Up")) {
        storeResult(a[i - 1], b[j - 1]);
        moveLeft();
        moveUp();
      }
    }

    bool isDir(string dir) {
      return (matchTable[i][j].dir == dir);
    }

    void storeResult(char aLetter, char bLetter) {
      aResult[currentIndex] = aLetter;
      bResult[currentIndex] = bLetter;
    }

    void moveLeft() {
      j --;
    }

    void moveUp() {
      i --;
    }

    pair<string, string> getResultStringPair() {
      pair<string, string> returnStringPair (aResult, bResult);
      return returnStringPair;
    }
};
