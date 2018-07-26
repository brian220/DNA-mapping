#define MATCH 1
#define MISMATCH - 1
#define GAP -2
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class score{
  public:
    int num;
    string prev_dir;
  score():num(0), prev_dir("None"){}
};

//for debug
void print_matrix(vector<vector<score>> & match_matrix){
  for (int i = 0; i < match_matrix.size(); i ++) {
    for (int j = 0; j < match_matrix[0].size(); j ++) {
      cout << match_matrix[i][j].num << " ";
    }
    cout << endl;
  }
}

//forward to construct the match matrix
void forward_matrix(vector<vector<score>> & match_matrix, string a, string b) {
  int match_score = MATCH;
  int mismatch_score = MISMATCH;
  int gap_score = GAP;
  cout << a.length() << endl;
  cout << b.length() << endl;

  for (int i = 0; i < a.length() + 1; i ++) {
    for (int j = 0; j < b.length() + 1; j ++) {
      cout << i << j << endl;
      if (i == 0 && j == 0) {
        match_matrix[i][j].num = 0;
      }
      else if (i == 0) {
        match_matrix[i][j].num = match_matrix[i][j - 1].num + gap_score;
        match_matrix[i][j].prev_dir = "Left";
        //cout << match_matrix[i][j].num << endl;
      }
      else if (j == 0) {
        match_matrix[i][j].num = match_matrix[i - 1][j].num + gap_score;
        match_matrix[i][j].prev_dir = "Up";
        //cout << match_matrix[i][j].num << endl;
      }
      else {
        int from_left_score = match_matrix[i][j - 1].num + gap_score;
        int from_up_score = match_matrix[i - 1][j].num + gap_score;
        int from_left_up_score = 0;
        if (a[i - 1] == b[j - 1]){
          cout << "match:";
          cout << a[i - 1] << b[j - 1] << endl;
          //match
          from_left_up_score = match_matrix[i - 1][j - 1].num + match_score;
        }
        else {
          //mismatch
          cout << "mismatch:";
          cout << a[i - 1] << b[j - 1] << endl;
          from_left_up_score = match_matrix[i - 1][j - 1].num + mismatch_score;
        }

        //compare the max point direction
        if (from_left_score > from_up_score) {
          if (from_left_score > from_left_up_score) {
            match_matrix[i][j].num = from_left_score;
            match_matrix[i][j].prev_dir = "Left";
          }
          else {
            match_matrix[i][j].num = from_left_up_score;
            match_matrix[i][j].prev_dir = "Left Up";
          }
        }
        else{
          if (from_up_score > from_left_up_score) {
            match_matrix[i][j].num = from_up_score;
            match_matrix[i][j].prev_dir = "Up";
          }
          else {
            match_matrix[i][j].num = from_left_up_score;
            match_matrix[i][j].prev_dir = "Left Up";
          }
        }
        cout << from_left_score<< endl;
        cout << from_up_score << endl;
        cout << from_left_up_score << endl;
      }
    }
      print_matrix(match_matrix);
  }
}

//Back track the matrix computing scores, output answers
void back_track_matrix(vector<vector<score>> & match_matrix, string a, string b) {
  string seq_a;
  string seq_b;
  seq_a.resize(max(a.length(), b.length()));
  seq_b.resize(max(a.length(), b.length()));
  int i = a.length();
  int j = b.length();
  cout << i << " " << j << endl;
  while (i >= 0 || j >= 0){
    if (match_matrix[i][j].prev_dir == "Left") {
      cout << "l" << endl;
      seq_a[i] = '-';
      j --;
    }
    else if (match_matrix[i][j].prev_dir == "Up") {
      cout << "u" << endl;
      seq_b[j] = '-';
      i --;
    }
    else if (match_matrix[i][j].prev_dir == "Left Up") {
      cout << "lu" << endl;
      seq_a[i] = a[i];
      seq_b[j] = b[j];
      i --;
      j --;
    }
    if (i == 0 && j == 0) {
      break;
    }
  }
  cout << "Output sequence A:" << seq_a << endl;
  cout << "Output sequence B:" << seq_b << endl;
}

void needleman_wunsch(string a, string b) {
  vector<vector<score>> match_matrix;
  match_matrix.resize(a.length() + 1);
  for (int i = 0; i < a.length() + 1; i ++) {
    match_matrix[i].resize(b.length() + 1);
  }
  forward_matrix(match_matrix, a, b);
  back_track_matrix(match_matrix, a, b);
}

void ask_for_input(){
  string a, b;
  cout << "Please input two sequence A, B you want to compare" << endl;
  cout << "A:";
  cin >> a;
  cout << endl;
  cout << "B:";
  cin >> b ;
  cout << endl;
  needleman_wunsch(a, b);
}

int main() {
  ask_for_input();
}
