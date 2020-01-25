#!/bin/bash

g++ --std=c++17 main.cpp -W -Wall -Wextra -llua -ldl -o example -g && ./example
