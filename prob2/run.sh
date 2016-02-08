#!/bin/bash
gcc  server.c -o s
gcc  c1.c -o c1
gcc  s.c -o service
gnome-terminal -e "./s"
gnome-terminal -e "./c1"
gnome-terminal -e "./service"
