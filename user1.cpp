#include <iostream>

using namespace std;

int main() {
  string env = "Discord,Calculator";
  setenv("PROC_TO_KILL", env.c_str(), 0);
  system("open -na Calendar");
  system("open -na Discord");
  system("open -na Notes");
  FILE* cmd = popen(string("pgrep Notes").c_str(), "r");
  char buff[100];
  fgets(buff, 100, cmd);
  pid_t pid = strtoul(buff, NULL, 10);
  system("open -na Calculator");
  system("open -na Calculator");
  system("open -na Calculator");
  system("open -na Calculator");
  system("g++ killer1.cpp -o killer && ./killer --name Calendar");
  unsetenv("PROC_TO_KILL");
  system((string("g++ killer1.cpp -o killer && ./killer --id ") + to_string(pid)).c_str());
}
