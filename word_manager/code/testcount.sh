#!/bin/bash - 
#===============================================================================
#
#          FILE: testcount.sh
# 
#         USAGE: ./testcount.sh 
# 
#   DESCRIPTION: 
# 
#       OPTIONS: ---
#  REQUIREMENTS: ---
#          BUGS: ---
#         NOTES: ---
#        AUTHOR: Aut (yinjing), autyinjing@126.com
#  ORGANIZATION: 
#       CREATED: 2015年06月30日 10:30
#      REVISION:  ---
#===============================================================================

touch info.txt
sed -n '1,$d' info.txt

for ((i=0; i<=26; i++))
do
        echo $i >> info.txt
done

declare -i sum=0

#cat info.txt | awk 'BEGIN{sum=$((sum+$(($0)))); printf "%10d", sum}'

tmp=$(cat info.txt | sed '1,$p')

#echo "Next is for :"
for var in tmp
do
        sum=$((sum+$(($var))))
        echo $var
done

echo "sum = $sum"

exit 0
