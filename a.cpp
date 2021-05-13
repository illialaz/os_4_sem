#include <iostream>

using namespace std;

int main() {
  int tmp = 0;
  cin >> tmp;
  while(tmp != 0) {
    cout << tmp + 3 << " ";
    cin >> tmp;
  }
  cout << 0;
  return 0;
}