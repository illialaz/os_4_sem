#include <iostream>
 #include "Number.h"
 #include "Vector.h"

 int main()
 {
     Number a(3);
     Number b(4);
     Vector c(a, b);
     Vector d(b, b);
     std::cout << a + b << "\n";
     std::cout << "Hello World!\n";
     std::cout << c + d << "\n";
     std::cout << c.r() << " " << c.u() << "\n";
     return 0;
 }