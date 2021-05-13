#include <iostream>
#include <unistd.h>

using namespace std;

int main() {
  int p[2];
  string* proc = new string[3];
  proc[0] = "./a";
  proc[1] = "./b";
  proc[2] = "./c";
  for(int i = 0; i < 2; i++) {
    if(pipe(p) < 0) return 1;

    if(fork() == 0) {
      dup2(p[1], 1);
      execlp(proc[i].c_str(), proc[i].c_str(), NULL);
      perror("exec");
      abort();
    }

    dup2(p[0], 0);
    close(p[1]);
  }

  execlp(proc[2].c_str(), proc[2].c_str(), NULL);
  perror("exec");
  abort();
  return 0;
}