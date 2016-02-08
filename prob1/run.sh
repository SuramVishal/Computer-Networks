#!/bin/bash
gcc -pthread sselect.c
gcc -pthread cc1.c -o c1
gcc -pthread cc2.c -o c2
gcc -pthread cc3.c -o c3
./a.out &
gnome-terminal -e "./c1"
gnome-terminal -e "./c2"
gnome-terminal -e "./c3"
