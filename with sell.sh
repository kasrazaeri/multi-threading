#!/bin/sh
echo m = enter the number of files you want to create:
read m
echo n = enter the number of alphabets you want to write in files:
read n

read -p "enter number of substrings you want to check in files: " num
if [ $num -gt 1 ]; then
	for ((i=1;; i++)); do
		read -p "enter substring number ($i) : " a[$i]
		if [ $i == $num ]; then break; fi
	done
else
	echo enter your substring :
	read a[1]
fi

start=`date +%s.%N`


for ((j=1;; j++)); do
	touch text.file$j 
	if [ $j == $m ]; then break; fi 
	
done

for ((j=1;; j++)); do 
	tr -dc a-z </dev/urandom | head -c $n >> text.file$j 
	if [ $j == $m ]; then break; fi
done 
count=0
for ((j=1;; j++)); do
	for ((i=1;; i++)); do
		echo substring number $i repeats in text.file$j for :
		grep -o ${a[$i]} text.file$j | wc -l 
		
		if [ $i == $num ]; then break; fi
	done
	
	if [ $j == $m ]; then break; fi
done


end=`date +%s.%N`

runtime=$( echo "$end - $start" | bc -l) 
echo this process lasts for $runtime seconds.


