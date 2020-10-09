#!/bin/sh

function usage() {
	echo usage: ./encode.sh input output
	exit
}

in="$1"
out="$2"
[ -z "$in" ]  && usage
[ -z "$out" ] && usage

wdir='fufelvid_frames'
rawsize=259200 # 1920 * 1080 / 8

mkdir -p $wdir
rm -f $wdir/*

split --numeric-suffixes=1 -a 8 -b $rawsize "$in" $wdir/frame.

for f in $wdir/frame.*; do ( echo $f >&2; ./data2ff < $f | ./ff2png > $f.png);
done

echo $in $out
ffmpeg -r 4 -i $wdir/frame.%08d.png -c:v libx264rgb "$out"

rm -rf "$wdir"
