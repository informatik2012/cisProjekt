#!/bin/bash
DIRECTORY=frames/

if [ ! -d "$DIRECTORY" ]; then
  `mkdir $DIRECTORY`
fi

for currentFrame in {0..250}
do
  pdflatex -interaction batchmode -jobname="currentFrame${currentFrame}" "\"\def\currentFrame{$currentFrame} \input{animation.tex}\""
  convert -density 600 -resize 1024x768 -colorspace YUV currentFrame.pdf ${DIRECTORY}${currentFrame}.jpg &
done
avconv -r 25 -b 10000k -i ${DIRECTORY}%d.jpg -pass 1 -y test.mp4 && avconv -r 25 -b 10000k -i ${DIRECTORY}%d.jpg -pass 2 -y test.mp4
rm ${DIRECTORY}/*.*
