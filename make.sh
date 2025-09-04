#!/bin/sh
make clean
make all
echo `pwd` && sleep 5
cd code/application/external/ && make clean&&make all && echo `pwd` && sleep 5
cd ../../../ && make all && echo `pwd` && sleep 5

