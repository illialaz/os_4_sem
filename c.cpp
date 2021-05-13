#include <iostream>

using namespace std;

int main() {
  int tmp = 0;
  int sum = 0;
  cin >> tmp;
  while(tmp != 0) {
    sum += tmp;
    cin >> tmp;
  }
  cout << sum << "\n";
  return 0;
}