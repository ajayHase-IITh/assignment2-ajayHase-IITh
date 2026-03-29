#!/bin/sh

if [ "$#" -ne 2 ]; then
	echo "Usage: $0 <filesdir> <searchstr>"
	exit 1
fi

filedir="$1"
searchstr="$2"

if [ ! -d "$filedir" ]; then
	echo "Error: $filedir is not a directory"
	exit 1
fi

filesCount=$(find "$filedir" -type f | wc -l)
matchCount=$(grep -rF "$searchstr" "$filedir" 2>/dev/null | wc -l)

echo "The number of files are $filesCount and the number of matching lines are $matchCount" 
