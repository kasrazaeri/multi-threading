#!/bin/bash

echo m = enter the number of files you want to create:
read m
echo n = enter the number of alphabets you want to write in files:
read n
echo Enter the word :
read word

start=`date +%s%N`
for ((j=1;; j++)); do
        touch file$j &
	if [ $j == $m ]; then break; fi 
done
for ((j=1;; j++)); do
	(tr -dc a-z </dev/urandom | head -c $n >> file$j) &
	if [ $j == $m ]; then break; fi
done
wait
for ((j=1;; j++)); do
	(grep -o $word  "file$j"  | wc -l) &  
        if [ $j == $m ]; then break; fi    
done
end=`date +%s%N`
wait
echo This process lasts $(($end - $start)) nanoseconds.

