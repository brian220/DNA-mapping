#include <iostream>
#include <string>
using namespace std;

class PrintMatchResult {
  private:
    string aResult;
    string bResult;

    int score = 0;

    int matchScore = MATCH;
    int mismatchScore = MISMATCH;
    int gapScore = GAP;

  public:
    PrintMatchResult (string aResult, string bResult) {
      this -> aResult = aResult;
      this -> bResult = bResult;
    }

    void printResult() {
      printStringResult();
      printScore();
    }

    void printStringResult() {
      cout << "Output sequence A:" << aResult << endl;
      cout << "Output sequence B:" << bResult << endl;
    }

    void printScore() {
      computeScore();
      cout << "Score: " << score << endl;
    }

    void computeScore() {
      for (int i = 0; i < aResult.length(); i ++) {
        checkStringBitByBit(i);
      }
    }

    void checkStringBitByBit(int i) {
      if (isMatch(i)) {
        addScore(matchScore);
      }
      else if (isGap(i)) {
        addScore(gapScore);
      }
      else if (isMisMatch(i)) {
        addScore(mismatchScore);
      }
    }

   bool isMatch(int i) {
     return (aResult[i] == bResult[i]);
   }

   bool isGap(int i) {
     return (aResult[i] == '-' || bResult[i] == '-');
   }

   bool isMisMatch(int i) {
     return (aResult[i] != bResult[i]);
   }

   void addScore(int s) {
     score += s;
   }
};
