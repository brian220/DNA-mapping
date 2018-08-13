#include "ComputeMatchTable.cpp"
#include <iostream>
#include <string>
using namespace std;

class NeedlemanWunsch {
  private:
    string a;
    string b;
    vector<vector<TableEntity>> matchTable;

  public:
    void runNeedlemanWunsch() {
      inputTwoCompareString();
      initializeMatchTable();
      computeMatchTable();
      //backTrackMatrixTable();
      //computeMatchingScore();
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

    void computeMatchTable() {
      ComputeMatchTable cmt(a, b, matchTable);
      matchTable = cmt.forwardingTable();
      cmt.printMatrix();
    }
};

int main() {
  NeedlemanWunsch nw;
  nw.runNeedlemanWunsch();
}
