#include "program.h"

Program::Program() {
}

Program::~Program() {
  delete env;
}

void Program::show() {
  login();
  for (;;) {
    //TODO
    //RandomSelection* rs = new RandomSelection(env);
    SmartSelection* ss = new SmartSelection(env);
    RemOrNotForm* ronf = new RemOrNotForm();
    MainInterface mi(env, ss, ronf);
    mi.work();
    if (mi.toQuit()) {
      break;
    }
    mi.getNextInter()->work();
  }
}

void Program::login() {
  cout << endl << endl << endl;
  cout << " -------------- " << endl;
  cout << "  ~ Wordable ~  " << endl;
  cout << " -------------- " << endl << endl;
  cout << "  Your name: " << endl;
  cout << "  ";
  userName = str::readSent(cin);

  FileStrBridge* fsb = new FileStrBridge("./user/userlist.dat");
  SimpleInfo* userList = new SimpleInfo(fsb);
  if (userList->search(userName) == -1) {
    userList->add(userName);
    NewUser nu(userName);
    nu.create();
  }
  delete(userList);
  delete(fsb);

  env = new Env(userName);
  cout << endl << endl;
}

int main() {
  Program pg;
  pg.show();
  return 0;
}
