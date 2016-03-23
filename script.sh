#!/bin/bash

cat test/test.txt | while read line
do
   ./offline $line >> histogrammes.txt
done


