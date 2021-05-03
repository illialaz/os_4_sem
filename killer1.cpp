#include <iostream>
#include <sstream>
#include "string.h"
#include "signal.h"

using namespace std;

void killProcessByName(char* name) {
  string str = "pgrep " + string(name);
  FILE* cmd;
  pid_t pid = 1;
  pid_t prev = 0;
  char buff[100];
  while(pid != prev) {
    cmd = popen(str.c_str(), "r");
    fgets(buff, 100, cmd);
    prev = pid;
    pid = strtoul(buff, NULL, 10);
    kill(pid, SIGKILL);
  }
}

int main(int argc, char** argv) {
  const char* name = "PROC_TO_KILL";
  const int buffSize = 65535;
  char buffer[buffSize];
  char* tmp = getenv(name);
  if(tmp != nullptr) {
    strcpy(buffer, getenv(name));
    std::stringstream ss(buffer);
    while (ss.getline(reinterpret_cast<char*>(&buffer), buffSize, ',')) {
        killProcessByName(buffer);
    }
  }

  if (argc < 3) return 0;

  if(strcmp(argv[1], "--id") == 0) kill(atoi(argv[2]), SIGKILL);
  if (strcmp(argv[1], "--name") == 0) killProcessByName(argv[2]);
  return 0;
}
