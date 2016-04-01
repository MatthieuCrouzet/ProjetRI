#!/bin/bash

cc rdjpeg.c read_image.c -o read_image
cc rdjpeg.c calculate_dist.c -o calculate_dist

cat test/img.txt | while read line
do
   ./read_image img/$line.jpg histogrammes/$line.bin;
done
cat histogrammes/*.bin >> hist.bin
./calculate_dist $1 hist.bin

