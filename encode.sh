#!/bin/sh

wdir='fufelvid_frames'
rawsize=518400 # 1920 * 1080 / 8 * 2 ????

rm -rf $wdir/*
mkdir -p $wdir

split -x -a 8 -b $rawsize - $wdir/frame.

for f in $wdir/frame*; do ./data2ff < $f | ./ff2png > $f.png; done

ffmpeg -i $wdir/frame.*.png -r 0.20 -c:v libx264rgb file.mp4


