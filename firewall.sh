#!/bin/bash

#push stdin to txt file
cat - > packets_in.txt

#removes any unwanted comments, spaces, and blank lines
sed '/^$/d' "$1" | sed '/^\s*#/d' | \
sed 's/#.*//' | sed 's/'\ '//g' > rules.txt

#filters packets line by line with all 4 filters
while read -r line; do
	cat "packets_in.txt" |
		./firewall.exe "$(echo "$line" | cut -d',' -f1)" | \
		./firewall.exe "$(echo "$line" | cut -d',' -f2)" | \
		./firewall.exe "$(echo "$line" | cut -d',' -f3)" | \
		./firewall.exe "$(echo "$line" | cut -d',' -f4)" >> good_pac.txt

done < rules.txt

#sorts and deletes duplicates 
cat "good_pac.txt" | sort -u  > sorted_good_pac.txt 

#deletes spaces
sed 's/'\ '//g' "sorted_good_pac.txt" 

#removes temp files
rm good_pac.txt rules.txt packets_in.txt sorted_good_pac.txt