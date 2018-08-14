#define MATCH 1
#define MISMATCH - 1
#define GAP -2
#include "TableEntity.cpp"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class ForwardMatchTable {
  private:
    vector<vector<TableEntity>> matchTable;
    string a;
    string b;

    int matchScore = MATCH;
    int mismatchScore = MISMATCH;
    int gapScore = GAP;

    int fromLeftScore = 0;
    int fromUpScore = 0;
    int fromLeftUpScore = 0;

  public:
    ForwardMatchTable(string a, string b, vector<vector<TableEntity>>  matchTable) {
      this -> a = a;
      this -> b = b;
      this -> matchTable = matchTable;
    }

    vector<vector<TableEntity>> forwardingTable() {
      setStartPoint();
      setFirstRow();
      setFirstCol();
      setRemainingTable();
      printMatchTable();
      return matchTable;
    }

    void setStartPoint() {
      matchTable[0][0].num = 0;
    }

    void setFirstRow() {
      for (int j = 1; j < b.length() + 1; j ++) {
        setTableNum(matchTable[0][j].num, getTableNum(0, j - 1), gapScore);
        matchTable[0][j].dir = "Left";
      }
    }

    void setFirstCol() {
      for (int i = 1; i < a.length() + 1; i ++) {
        setTableNum(matchTable[i][0].num, getTableNum(i - 1, 0), gapScore);
        matchTable[i][0].dir = "Up";
      }
    }

   //Remaining table is the part of table except first row and first col
   //compute the score from three direction, then choose the greastest score as table score number
    void setRemainingTable() {
      for (int i = 1; i < a.length() + 1; i ++) {
        for (int j = 1; j < b.length() + 1; j ++) {
          setThreedirScore(i, j);
          storeGreatestScore(i, j);
        }
      }
    }

   //compute the score from three direction
    void setThreedirScore(int i, int j) {
      setTableNum(fromLeftScore, getTableNum(i, j - 1), gapScore);
      setTableNum(fromUpScore, getTableNum(i - 1, j), gapScore);
      setLeftUpNum(i, j);
    }

    void setLeftUpNum(int i, int j) {
      if (a[i - 1] == b[j - 1]){
        setTableNum(fromLeftUpScore, getTableNum(i - 1, j - 1), matchScore);
      }
      else {
        setTableNum(fromLeftUpScore, getTableNum(i - 1, j - 1), mismatchScore);
      }
    }

    void setTableNum(int &tableNumToBeSet, int tableNum, int score) {
      tableNumToBeSet = tableNum + score;
    }

    int getTableNum(int i , int j) {
      return matchTable[i][j].num;
    }

    //store the greastest one
    void storeGreatestScore(int i, int j) {
      storeGreatestScoreNum(i, j);
      storeGreatestScoredir(i, j);
    }

    void storeGreatestScoreNum(int i, int j) {
      matchTable[i][j].num = max(fromLeftScore, fromUpScore);
      matchTable[i][j].num = max(matchTable[i][j].num, fromLeftUpScore);
    }

    void storeGreatestScoredir(int i, int j) {
      if (matchTable[i][j].num == fromLeftScore) {
        matchTable[i][j].dir = "Left";
      }
      else if (matchTable[i][j].num == fromUpScore) {
        matchTable[i][j].dir = "Up";
      }
      else {
        matchTable[i][j].dir = "Left Up";
      }
    }

    void printMatchTable() {
      PrintTable pt;
      pt.printTable(matchTable);
    }
};
