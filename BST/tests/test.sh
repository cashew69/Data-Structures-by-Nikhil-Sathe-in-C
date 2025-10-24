#!/bin/bash

min=1
max=99
../code/a.out -create $(for i in {1..10}; do echo -n "$(( RANDOM % (max - min + 1) + min )) "; done)

