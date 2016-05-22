#include "program.h"

Program::Program() {
}

Program::~Program() {
  delete env;
}

void Program::show() {
  login();
  for (;;) {
    
    SelectStrategyFactory ssf(env);
    FormStrategyFactory fsf(env);

    SelectStrategy* ss = ssf.produce(env->basic->getSelectStrategy());
    FormStrategy* fs = fsf.produce(env->basic->getFormStrategy());

    MainInterface mi(env, ss, fs);
    
    /*
    RandomSelection* rs = new RandomSelection(env);
    RemOrNotForm* ronf = new RemOrNotForm();
    MainInterface mi(env, rs, ronf);
    */
    
    mi.work();
    if (mi.toQuit()) {
      delete ss;
      delete fs;
      break;
    }
    mi.getNextInter()->work();
    delete ss;
    delete fs;
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
    User nu(userName);
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
