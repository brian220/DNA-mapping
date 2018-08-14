#include "ForwardMatchTable.cpp"
#include "BacktrackMatchTable.cpp"
#include "PrintMatchResult.cpp"
#include "TableEntity.cpp"
#include <iostream>
#include <string>
#include <utility>
using namespace std;

class NeedlemanWunsch {
  private:
    string a;
    string b;
    vector<vector<TableEntity>> matchTable;

    string aResult;
    string bResult;
  public:
    void runNeedlemanWunsch() {
      inputTwoCompareString();
      initializeMatchTable();
      forwardMatchTable();
      backtrackMatchTable();
      printMatchResult();
    }

    void inputTwoCompareString() {
      cout << "Please input two sequence A, B you want to compare" << endl;
      inputString(a);
      inputString(b);
    }

    void inputString(string& inputString) {
      cout << "Please input a string:" << endl;
      cin >> inputString;
    }

    void initializeMatchTable() {
      matchTable.resize(a.length() + 1);
      for (int i = 0; i < a.length() + 1; i ++) {
        matchTable[i].resize(b.length() + 1);
      }
    }

    void forwardMatchTable() {
      ForwardMatchTable cmt(a, b, matchTable);
      matchTable = cmt.forwardingTable();
    }

    void backtrackMatchTable() {
      BacktrackMatchTable bmt(a, b, matchTable);
      pair <string, string> result;
      result = bmt.backtrackingTable();
      aResult = result.first;
      bResult = result.second;
    }

    void printMatchResult() {
      PrintMatchResult pmr(aResult, bResult);
      pmr.printResult();
    }
};

int main() {
  NeedlemanWunsch nw;
  nw.runNeedlemanWunsch();
}
