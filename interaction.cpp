#include "interaction.h"
#include "def.h"

OneInteraction::OneInteraction(Env* env) : env(env) {
}

void OneInteraction::show() {
  /*
  cout << env << endl;
  cout << env->statList.size() << endl;
  */
  ask();
  getResponse();
  while (!isLegal()) {
    reask();
    getResponse();
  }
  process();
}


Interaction::Interaction(Env* env) : env(env) {
}


LookUpOneWord::LookUpOneWord(Env* env) : OneInteraction(env) {
}

string LookUpOneWord::getWord() {
  return word;
}

void LookUpOneWord::ask() {
  cout << " Input a word: ";
}

void LookUpOneWord::reask() {
  cout << "Illegal characters contained. Please re-input: ";
}

void LookUpOneWord::getResponse() {
  cin >> word;
}

bool LookUpOneWord::isLegal() {
  str::clearEnds(word);
  for (int i = 0; i < word.length(); ++i) {
    if ((word[i] != '-') && (word[i] < 'a' || word[i] > 'z') && (word[i] < 'A' || word[i] > 'Z')) {
      return false;
    }
  }
  return true;
}

void LookUpOneWord::process() {
  Def* def = new Def(env->fsbDef, word);
  if (def->succeed()) {
    def->print(cout);
    env->history->add(word);
  }
  else {
    cout << " Cannot find the word!" << endl << endl;
  }
}


LearnOneWord::LearnOneWord (SelectStrategy* sstra, FormStrategy* fstra, Env* env) :
    OneInteraction(env), sstra(sstra), fstra(fstra) {
}

string LearnOneWord::getWord() {
  return word;
}

void LearnOneWord::ask() {
  word = sstra->next(diffi);
  //cout << " @@@@diffi: " << diffi << endl;
  fstra->setWord(word);
  cout << fstra->display();
}

void LearnOneWord::reask() {
  cout << "Illegal input! Please re-input:" << endl;
}

void LearnOneWord::getResponse() {
  string resp;
  cin >> resp;
  fstra->rcvResponse(resp);
}

bool LearnOneWord::isLegal() {
  return fstra->isLegal();
}

void LearnOneWord::process() {
  env->pass(word, diffi, fstra->isOK());
  Def def(env->fsbDef, word);
  def.print(cout);
}


// ====================================================



LookUpWord::LookUpWord(Env* env) : Interaction(env) {
}

void LookUpWord::work() {
  for (;;) {
    LookUpOneWord* luow = new LookUpOneWord(env);
    luow->show();
    string word = luow->getWord();
    delete luow;

    for (;;) {
      cout << " What to do?" << endl;
      cout << "   Continue to look up words[c]" << endl;
      cout << "   Show example sentences[s]" << endl;
      cout << "   Show history(<=20)[h]" << endl;
      cout << "   Quit[q]" << endl;
      cout << " ";

      string in;
      cin >> in;
      str::clearEnds(in);

      if (in == "c" || in == "C") {
        break;
      }
      if (in == "q" || in == "Q") {
        return;
      }
      if (in == "s" || in == "S") {
        Sentences sent(env->fsbSent, word);
        sent.print(cout);
        continue;
      }
      if (in == "h" || in == "H") {
        cout << endl;
        for (int i = env->history->getSize(), j = 1; i >= 1 && j <= 20; --i, ++j) {
          cout << "   ★  " << env->history->getItem(i) << " ★" << endl;
        }
        cout << endl;
        continue;
      }

      cout << " Illegal input!" << endl;
    }
  }
}


// ---------------------------------


Learn::Learn(SelectStrategy* sstra, FormStrategy* fstra, Env* env) :
    Interaction(env), sstra(sstra), fstra(fstra) {
}

void Learn::work() {
  for (;;) {
    LearnOneWord* low = new LearnOneWord(sstra, fstra, env);
    low->show();
    string word = low->getWord();
    
    for (;;) {
      cout << " What to do?" << endl;
      cout << "   Next word[n]" << endl;
      cout << "   Show example sentences[s]" << endl;
      cout << "   Add example sentences[a]" << endl;
      cout << "   Delete example sentences[d]" << endl;
      cout << "   Quit[q]" << endl;
      cout << " ";

      string in;
      cin >> in;
      str::clearEnds(in);

      if (in == "n" || in == "N") {
        break;
      }
      if (in == "q" || in == "Q") {
        return;
      }

      Sentences sent(env->fsbSent, word);
      if (in == "s" || in == "S") {
        sent.print(cout);
        continue;
      }
      if (in == "a" || in == "A") {
        cout << " Input a sentence:" << endl;
        cout << " ";
        sent.add(str::readSent(cin));
        continue;
      }
      if (in == "d" || in == "D") {
        cout << " Input the number of sentence:" << endl;
        cout << " ";
        string num = str::readSent(cin);
        
        bool isNum = true;
        for (int i = 0; i < num.length(); ++i) {
          if (num[i] < '0' || num[i] > '9') {
            isNum = false;
            break;
          }
        }

        if (isNum) {
          sent.del(str::strToInt(num));
        }
        else {
          cout << " Illegal input!" << endl;
        }
        continue;
      }

      cout << " Illegal input!" << endl;
    }
  }
}


// -----------------------------


Count::Count(Env* env) : Interaction(env) {
}

void Count::work() {
  cout << " Input the name of the file (put in \"/count\"):" << endl;
  cout << " ";
  string path = "count/" + str::readSent(cin);
  ifstream ifs0(path.c_str());
  if (!ifs0) {
    cout << " No such file!" << endl << endl;
    return;
  }
  ifstream ifs;
  ifs.open(path.c_str());
  string word;
  int cnt = 0;
  while (getline(ifs, word)) {
    if (env->masteredVoc->search(word) == -1) {
      ++cnt;
    }
    
  }
  cout << " " << cnt << endl << endl;
}

