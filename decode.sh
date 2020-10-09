#!/bin/sh

wdir='fufelvid_frames'

rm -rf $wdir
mkdir -p $wdir

ffmpeg -i file.mp4 -vf fps=1 $wdir/frame.%08d.png

for f in $wdir/frame.*.png; do ./png2ff < $f | ./ff2data > $f.data; done

cat $wdir/*.data > file.out

