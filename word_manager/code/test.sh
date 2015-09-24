#!/bin/bash - 
#===============================================================================
#
#          FILE: test.sh
# 
#         USAGE: ./test.sh 
# 
#   DESCRIPTION: 
# 
#       OPTIONS: ---
#  REQUIREMENTS: ---
#          BUGS: ---
#         NOTES: ---
#        AUTHOR: Aut (yinjing), autyinjing@126.com
#  ORGANIZATION: 
#       CREATED: 2015年06月29日 20:55
#      REVISION:  ---
#===============================================================================


cat $1 >> dest.txt
cat dest.txt | sort -fb | uniq > _dest.txt
rm dest.txt
mv _dest.txt dest.txt
