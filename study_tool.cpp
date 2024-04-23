#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#include <stdlib.h>
#include <time.h>

#define QUESTIONS 20

using namespace std;

struct Word {
  string word;
  string def;
};

int main(int argc, char* argv[]) {
  if (argc == 1) {
    cout << "No file arguments detected" << endl;
    exit(0);
  }
  string text;
  vector<Word> word_list;
  for (int i = 1; i < argc; i++) {
    fstream file(argv[i]);
    if (file.fail()) {
      cout << "File \"" << argv[i] << "\" not found" << endl;
      file.close();
      exit(0);
    }
    bool first = true;
    while (getline(file, text)) {
      Word new_word;
      new_word.word = text;
      getline(file, text);
      new_word.def = text;
      word_list.push_back(new_word);
    }
    file.close();
  }


  cout << "***Welcome to Test Tool***" << endl << "Enter number of quiz questions, or 0 for the max" << endl;
  int quiz_size;
  cin >> quiz_size;
  if (quiz_size > word_list.size() || quiz_size <= 0) quiz_size = word_list.size();

  srand(time(NULL));

  vector<int> used_words = {-1};
  vector<int> wrong_answers;
  int score = 0;
  for (int q_num = 1; q_num <= quiz_size; q_num++) {
    int c_idx = rand() % word_list.size();
    if (find(used_words.begin(), used_words.end(), c_idx) == used_words.end()) {
      used_words.push_back(c_idx);
      Word chosen = word_list.at(c_idx);
      cout << "Question " << q_num << endl << "Def: " << chosen.def << endl;
      vector<int> used = {-1};
      int a_idx = rand() % 4;
      for (int i = 0; i < 4; i++) {
        if (i == a_idx) {
          cout << i+1 << ".) " << chosen.word << " !" << endl;
        } else {
          int r_idx = rand() % word_list.size();
          if (find(used.begin(), used.end(), r_idx) == used.end() && r_idx != *(used.end()) && word_list.at(r_idx).word != chosen.word) {
            used.push_back(r_idx);
            cout << i+1 << ".) " << (word_list.at(r_idx)).word << endl;
          } else {
            i--;
          }
        }
      }
      int input;
      while (true) {
        cin >> input;
        if (input >= 1 && input <= 4) break;
        else {
          cout << "Invalid input, try again" << endl;
          cin.clear();
          cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
      }
      if (input == a_idx+1) score++;
      else wrong_answers.push_back(q_num);
    } else {
      q_num--;
    }
  }

  cout << "Score: " << score << " / " << quiz_size << " = " << (round(((double)score/quiz_size)/0.01)) << "%" << endl;
  if (score != quiz_size) {
    cout << "Your wrong answers were on the following questions: ";
    for_each(wrong_answers.begin(), wrong_answers.end(), [](int i){cout << i << " ";});
    cout << endl;
  }
}