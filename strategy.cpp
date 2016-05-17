#include "strategy.h"

SelectStrategy::SelectStrategy(Env* env) : env(env), diffi(0) {
  srand(time(0));
}

string SelectStrategy::next(int& difficulty) {
  difficulty = diffi = chooseDifficulty();
  int nowTimestamp = env->basic->getTimestamp();
  for (int i = 1;; ++i) {
    string word = env->vocList[diffi]->getItem(i);
    Progress prog(env->fsbProg, word);
    if (nowTimestamp - prog.getTimestamp() > gap(prog.getFamilarity())) {
      return word;
    }
  }
}


void FormStrategy::setWord(const string& word) {
  this->word = word;
  str::clearEnds(this->word);
}

bool FormStrategy::isLegal() {
  return legal;
}

bool FormStrategy::isOK() {
  return ok;
}



// ------------------------


SmartSelection::SmartSelection(Env* env) : SelectStrategy(env) {
}

int SmartSelection::chooseDifficulty() {
  int level = env->basic->getLevel();
  int basicDiffi = level / (LEVEL_MAX / DIFFI_NUM), diffi;
  srand(time(0));
  int t = rand() % 10;
  if (t == 0) diffi = basicDiffi - 2;
  if (t >= 1 && t <= 2) diffi = basicDiffi - 1;
  if (t >= 3 && t <= 6) diffi = basicDiffi;
  if (t >= 7 && t <= 8) diffi = basicDiffi + 1;
  if (t == 9) diffi = basicDiffi + 2;
  if (diffi < 0) diffi = 0;
  if (diffi >= DIFFI_NUM) diffi = DIFFI_NUM - 1;
  return diffi;
}


FixedSelection::FixedSelection(Env* env, int fixedDiffi) :
    SelectStrategy(env),
    fixedDiffi(fixedDiffi) {
}

int FixedSelection::chooseDifficulty() {
  return fixedDiffi;
}


RandomSelection::RandomSelection(Env* env) : SelectStrategy(env) {
}

int RandomSelection::chooseDifficulty() {
  return rand() % DIFFI_NUM;
}




string RemOrNotForm::display() {
  string res = "\n ";
  for (int i = 1; i <= word.length() + 2; ++i) {
    res += "-";
  }
  res += " \n| ";
  res += word;
  res += " |\n ";
  for (int i = 1; i <= word.length() + 2; ++i) {
    res += "-";
  }
  res += " \n\n";
  res += " Remember or not? [y/n]:\n ";
  return res;
}

void RemOrNotForm::rcvResponse(const string& resp) {
  string s = resp;
  str::clearEnds(s);
  if (s == "y" || s == "Y") {
    legal = true;
    ok = true;
    return;
  }
  if (s == "n" || s == "N") {
    legal = true;
    ok = false;
    return;
  }
  legal = false;
  ok = false;
}
