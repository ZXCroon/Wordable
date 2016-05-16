#include "main_interface.h"

MainInterface::MainInterface(Env* env, SelectStrategy* sstra, FormStrategy* fstra) :
  Interaction(env), quit(false), sstra(sstra), fstra(fstra) {
}

void MainInterface::work() {
  cout << "  Hi, " << env->getUserName() << ". What do you want to do?" << endl << endl;
  cout << "   Word learning     [l]" << endl;
  cout << "   Word query        [q]" << endl;
  cout << "   Word test         [t]" << endl;
  cout << "   New word counting [c]" << endl;
  cout << "   Settings          [s]" << endl;
  cout << "   Exit              [e]" << endl;
  cout << " ";

  for (;;) {
    string res = str::readSent(cin);
    
    if (res == "e" || res == "E") {
      quit = true;
      return;
    }
    if (res == "l" || res == "L") {
      nextInter = new Learn(sstra, fstra, env);
      break;
    }
    if (res == "q" || res == "Q") {
      nextInter = new LookUpWord(env);
      break;
    }
    if (res == "t" || res == "T") {
      nextInter = new TestWord(env);
      break;
    }
    if (res == "c" || res == "C") {
      nextInter = new Count(env);
      break;
    }
    if (res == "s" || res == "S") {
      nextInter = new Settings(env);
      break;
    }

    cout << " Illegal input! Please re-input: " << endl;
  }
  
  
}

bool MainInterface::toQuit() {
  return quit;
}

Interaction* MainInterface::getNextInter() {
  return nextInter;
}
