#!/bin/bash

gcc -c Number.cpp -o Number.a;

gcc -c Vector.cpp -o Vector.so;

g++ -o proj ./Main.cpp Vector.so Number.a;
./proj
