//Extend the digit let can present only 128 kinds (not enough)
//Combine the english lower letter to make the new symbol unsigned unsigned short number (65536 numbers can use)
#define MATCH 1
#define MISMATCH - 1
#define GAP -2
#include <iostream>
#include <iomanip>
#include <utility>
#include <string>
#include <vector>
#include <map>
#include <math.h>
#include <sstream>
using namespace std;

class score{
  public:
    int num;
    string prev_dir;
  score():num(0), prev_dir("None"){}
};
map <string, unsigned short> string_to_short;


//for debug
void print_matrix(vector<vector<score>> match_matrix){
  for (int i = 0; i < match_matrix.size(); i ++) {
    for (int j = 0; j < match_matrix[0].size(); j ++) {
      cout << match_matrix[i][j].prev_dir << ", ";
    }
    cout << endl;
  }
}



//Back track the matrix computing scores, output answers
void back_track_matrix(vector<vector<score>> match_matrix, vector <unsigned short> a, vector <unsigned short> b) {
  vector <string> seq_a;
  vector <string> seq_b;
  int match_index =  max(a.size(), b.size()) - 1;
  seq_a.resize(match_index + 1);
  seq_b.resize(match_index + 1);
  int i = a.size();
  int j = b.size();
  for (;match_index >= 0; match_index --) {
    if (match_matrix[i][j].prev_dir == "Left") {
      seq_a[match_index] = "___";
      seq_b[match_index] = to_string(b[j - 1]);
      j --;
    }
    else if (match_matrix[i][j].prev_dir == "Up") {
      seq_a[match_index] = to_string(a[i - 1]);
      seq_b[match_index] = "___";
      i --;
    }
    else if (match_matrix[i][j].prev_dir == "Left Up") {
      seq_a[match_index] = to_string(a[i - 1]);
      seq_b[match_index] = to_string(b[j - 1]);
      i --;
      j --;
    }
    else {
      if (match_matrix[i][j].prev_dir == "None" && i == 0 && j == 0) {
        break;
      }
      else {
        cout << "Error:There is a bug in this code." << endl;
        cout << "If you find the bug, please contact b608390@gmail.com, thanks ~" << endl;
        break;
      }
    }
  }
  cout << "Sequence A:";
  for (int i = 0; i < seq_a.size(); i ++) {
    cout << setw(5) << seq_a[i] << " ";
  }
  cout << endl;
  cout << "Sequence B:";
  for (int i = 0; i < seq_b.size(); i ++) {
    cout << setw(5) << seq_b[i] << " ";
  }
  //compute_score(seq_a, seq_b);
}

//forward to construct the match matrix
void forward_matrix(vector<vector<score>> & match_matrix, vector <unsigned short> a, vector <unsigned short> b) {
  int match_score = MATCH;
  int mismatch_score = MISMATCH;
  int gap_score = GAP;

  for (int i = 0; i < a.size() + 1; i ++) {
    for (int j = 0; j < b.size() + 1; j ++) {
      if (i == 0 && j == 0) {
        match_matrix[i][j].num = 0;
      }
      else if (i == 0) {
        match_matrix[i][j].num = match_matrix[i][j - 1].num + gap_score;
        match_matrix[i][j].prev_dir = "Left";
      }
      else if (j == 0) {
        match_matrix[i][j].num = match_matrix[i - 1][j].num + gap_score;
        match_matrix[i][j].prev_dir = "Up";
      }
      else {
        int from_left_score = match_matrix[i][j - 1].num + gap_score;
        int from_up_score = match_matrix[i - 1][j].num + gap_score;
        int from_left_up_score = 0;
        if (a[i - 1] == b[j - 1]){
          //match
          from_left_up_score = match_matrix[i - 1][j - 1].num + match_score;
        }
        else {
          //mismatch
          from_left_up_score = match_matrix[i - 1][j - 1].num + mismatch_score;
        }

        //compare the max point direction
        if (from_left_score > from_up_score) {
          if (from_left_score >= from_left_up_score) {
            match_matrix[i][j].num = from_left_score;
            match_matrix[i][j].prev_dir = "Left";
          }
          else {
            match_matrix[i][j].num = from_left_up_score;
            match_matrix[i][j].prev_dir = "Left Up";
          }
        }
        else{
          if (from_up_score >= from_left_up_score) {
            match_matrix[i][j].num = from_up_score;
            match_matrix[i][j].prev_dir = "Up";
          }
          else {
            match_matrix[i][j].num = from_left_up_score;
            match_matrix[i][j].prev_dir = "Left Up";
          }
        }
      }
    }
      //print_matrix(match_matrix);
  }
}

void needleman_wunsch(vector <unsigned short> a, vector <unsigned short> b) {
  vector<vector<score>> match_matrix;
  match_matrix.resize(a.size() + 1);
  for (int i = 0; i < a.size() + 1; i ++) {
    match_matrix[i].resize(b.size() + 1);
  }
  forward_matrix(match_matrix, a, b);
  back_track_matrix(match_matrix, a, b);
}

//convert the input data from string to short according to the mapping
void extend_convert(string a, string b) {
  vector <unsigned short> seq_a;
  vector <unsigned short> seq_b;
  for (int i = 0; i < a.length(); i ++) {
    stringstream ss;
    string s;
    ss << a[i];
    ss >> s;
    cout << s << endl;
    seq_a.push_back(string_to_short[s]);
  }
  for (int i = 0; i < b.length(); i ++) {
    stringstream ss;
    string s;
    ss << b[i];
    ss >> s;
    seq_b.push_back(string_to_short[s]);
  }
  needleman_wunsch(seq_a, seq_b);
}

void ask_for_input() {
  //The input format is not sure, use the original input method.
  string a, b;
  cout << "Please input two sequence A, B you want to compare" << endl;
  cout << "A:";
  cin >> a;
  cout << endl;
  cout << "B:";
  cin >> b ;
  cout << endl;
  //convert the input to the short number
  extend_convert(a, b);
}

int main() {
  //Use number to represent the letter ex. match_item example.set_match_item("jfeioejf", 177)
  //Can create up to 65536 kinds of matching (unsigned short.)following
  //is the example:
  string_to_short.insert(pair<string,  unsigned short>("G", 15));
  string_to_short.insert(pair<string,  unsigned short>("C", 256));
  string_to_short.insert(pair<string,  unsigned short>("A", 326));
  string_to_short.insert(pair<string,  unsigned short>("T", 789));
  string_to_short.insert(pair<string,  unsigned short>("U", 899));
  cout << string_to_short["U"] << endl;
   ask_for_input();
}
