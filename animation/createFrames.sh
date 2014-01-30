#!/bin/bash
DIRECTORY=frames/
FAIL=0

if [ ! -d "$DIRECTORY" ]; then
  mkdir $DIRECTORY
fi

cd $DIRECTORY
for currentFrame in {0..250}
do
  pdflatex -interaction batchmode -jobname="frame${currentFrame}" "\"\def\currentFrame{$currentFrame} \input{../countdown/animation.tex}\"" &
done



for currentState in {0..101}
do
  for repetition in {1..25}
  do
    currentFrame=$(expr 250 + $(expr 25 \* $currentState) + $repetition)
    pdflatex -interaction batchmode -jobname="frame${currentFrame}" "\"\def\currentState{$currentState} \input{../particlesState/animationBW.tex}\"" &
    #convert -density 600 -resize 1024x768 -colorspace YUV frame${currentFrame}.pdf ${currentFrame}.jpg &
  done
done

for job in `jobs -p`
do
  echo $job
  wait $job || let "FAIL+=1"
done


for currentFrame in {0..2800}
do
  convert -density 600 -resize 1024x768 -colorspace YUV frame${currentFrame}.pdf ${currentFrame}.jpg &
done



cd ..

avconv -r 25 -b 10000k -i ${DIRECTORY}%d.jpg test.mp4
#avconv -r 25 -b 10000k -i ${DIRECTORY}%d.jpg -pass 1 -y test.mp4 && avconv -r 25 -b 10000k -i ${DIRECTORY}%d.jpg -pass 2 -y test.mp4
rm ${DIRECTORY}/*.*
