#include "test.h"

TestOneWord::TestOneWord(Env* env, int diffi, int no) :
    OneInteraction(env), diffi(diffi), no(no), terminated(false) {
}

string TestOneWord::getWord() {
  return word;
}

bool TestOneWord::isCorrect() {
  return correct;
}

void TestOneWord::ask() {
  srand(time(0));
  correctPos = rand() % OPTION_NUM;
  word = select();
  cout << endl;
  cout << "-------------" << endl;
  cout << endl;
  cout << "   (" << no << ") " << word << "   (Input 'q' to terminate the test)" << endl;
  cout << endl;
  for (int i = 0; i < OPTION_NUM; ++i) {
    string nowWord;
    if (i == correctPos) {
      nowWord = word;
    }
    else {
      nowWord = select();
    }
    cout << "   " << char(i + 'A') << ". ";
    Def def(env->fsbDef, nowWord);
    cout << def.getItem(rand() % def.getSize())->getDef() << endl;
  }
  cout << endl;
  cout << " ";
}

bool TestOneWord::isTerminated() {
  return terminated;
}

void TestOneWord::reask() {
  cout << "Illegal input! Please re-input: " << endl;
}

void TestOneWord::getResponse() {
  ans = str::readSent(cin);
}

bool TestOneWord::isLegal() {
  if (ans.length() > 1 || ans.length() == 0) {
    return false;
  }
  char c = ans[0];
  if (c == 'Q' || c == 'q') return true;
  return (c >= 'A' && c <= 'A' + OPTION_NUM - 1) || (c >= 'a' && c <= 'a' + OPTION_NUM - 1);
}

void TestOneWord::process() {
  if (ans[0] >= 'a' && ans[0] <= 'z') {
    ans[0] = ans[0] - 'a' + 'A';
  }
  if (ans[0] == 'Q') {
    terminated = true;
    return;
  }
  correct = (ans[0] - 'A' == correctPos);
  cout << endl;
  if (correct) {
    cout << "√" << endl << endl;
  }
  else {
    cout << "×  The correct answer is " << char(correctPos + 'A') << endl << endl;
  }
  cout << " " << word << endl;
  Def def(env->fsbDef, word);
  def.print(cout);
}

string TestOneWord::select() {
  int tdiffi;
  if (diffi == -1) {
    tdiffi = rand() % DIFFI_NUM;
  }
  else {
    tdiffi = diffi;
  }

  int no = rand() % (env->vocList[tdiffi]->getSize()) + 1;
  return env->vocList[tdiffi]->getItem(no);
}




TestWord::TestWord(Env* env) : Interaction(env) {
}

void TestWord::work() {
  cout << " Input difficulty [0-" << DIFFI_NUM - 1 << "] (input -1 to randomize):" << endl;
  cout << " ";
  int diffi;
  for (;;) {
    string res = str::readSent(cin);
    if (res == "-1") {
      diffi = -1;
      break;
    }
    bool ok = false;
    for (int i = 0; i < DIFFI_NUM; ++i) {
      if (res.length() == 1 && res[0] == i + '0') {
        diffi = i;
        ok = true;
        break;
      }
    }
    if (ok) {
      break;
    }

    cout << " Illegal input! Please re-input:" << endl;
    cout << " ";
  }
  cout << " Input the amount to test [10-100]:" << endl;
  cout << " ";
  int amount;
  for (;;) {
    string res = str::readSent(cin);
    bool isNum = true;
    for (int i = 0; i < res.length(); ++i) {
      if (res[i] < '0' || res[i] > '9') {
        isNum = false;
        break;
      }
    }
    if (isNum) {
      amount = str::strToInt(res);
      if (amount >= 10 && amount <= 100) {
        break;
      }
    }

    cout << " Illegal input! Please re-input:" << endl;
    cout << " ";
  }

  int correctCnt = 0;
  for (int i = 1; i <= amount; ++i) {
    TestOneWord tow(env, diffi, i);
    tow.show();
    if (tow.isTerminated()) {
      amount = i - 1;
      break;
    }
    if (tow.isCorrect()) {
      ++correctCnt;
    }
  }
  
  cout << endl;
  cout << "  " << correctCnt << "/" << amount << "    accuracy: ";
  if (amount > 0) {
    cout << fixed << setprecision(2) << (double)correctCnt * 100 / amount << "%" << endl;
  }
  else {
    cout << 0 << endl;
  }
  cout << endl;
}

/*
int main() {

  Env* env = new Env("Heli");
  RandomSelection* fs = new RandomSelection(env);
  RemOrNotForm* ronf = new RemOrNotForm();
  Learn learn(fs, ronf, env);
  learn.work();
  
  delete fs;
  delete ronf;
  delete env;
  
}
*/
