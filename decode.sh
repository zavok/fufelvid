#!/bin/sh

function usage() {
	echo usage: ./decode.sh input output
	exit
}

in="$1"
out="$2"
[ -z "$in" ]  && usage
[ -z "$out" ] && usage

wdir='fufelvid_frames'
mkdir -p $wdir
rm -f $wdir/*

ffmpeg -i "$in" $wdir/frame.%08d.png

for f in $wdir/frame.*.png; do ./png2ff < $f | ./ff2data > $f.data; done

cat $wdir/*.data > "$out"

rm -rf "$wdir"
