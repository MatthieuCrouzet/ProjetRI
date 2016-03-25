#!/bin/bash

cc rdjpeg.c offline.c -o offline

cat test/test.txt | while read line
do
   #$input="img/$line.jpg";
   #$output="histogrammes/hist_$line.bin";
   ./offline img/$line.jpg histogrammes/hist_$line.bin;
done
cat histogrammes/*.bin > hist.bin


