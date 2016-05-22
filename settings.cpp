#include "settings.h"

FormSetting::FormSetting(Env* env) : Interaction(env) {
}

void FormSetting::work() {
  cout << "  0. \"Remember or not\"" << endl;
  cout << " ";

  int num;
  for (;;) {
    string res = str::readSent(cin);
    if (str::isNumber(res)) {
      num = str::strToInt(res);
      // TODO:...
      if (num == 0) {
        break;
      }
    }
    cout << " Illegal input! Please re-input:" << endl;
    cout << " ";
  }
  env->basic->setFormStrategy(num);
}


DifficultySetting::DifficultySetting(Env* env): Interaction(env) {
}

void DifficultySetting::work() {
  cout << "  Difficulty [0-" << DIFFI_NUM - 1
       << "] (input " << -1 << " to turn into random mode, "
       << DIFFI_NUM << " smart mode" << endl;
  cout << " ";

  int num;
  for (;;) {
    string res = str::readSent(cin);
    if (str::isNumber(res)) {
      num = str::strToInt(res);
      if (num >= -1 && num <= DIFFI_NUM) {
        break;
      }
    }

    cout << " Illegal input! Please re-input:" << endl;
    cout << " ";
  }

  env->basic->setSelectStrategy(num);
}




Settings::Settings(Env* env) : Interaction(env) {
}

void Settings::work() {
  for (;;) {
    cout << "  Difficulty of words to learn [d]" << endl;
    cout << "  Learning form [f]" << endl;
    cout << "  Quit [q]" << endl;
    cout << endl;
    cout << " ";

    for (;;) {
      string res = str::readSent(cin);
      if (res == "q" || res == "Q") {
        return;
      }
      if (res == "d" || res == "D") {
        DifficultySetting ds(env);
        ds.work();
        break;
      }
      if (res == "f" || res == "F") {
        FormSetting fs(env);
        fs.work();
        break;
      }

      cout << " Illegal input! Please re-input: ";
      cout << " ";
    }
  }
}
