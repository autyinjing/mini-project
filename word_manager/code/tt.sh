#!/bin/bash - 
#===============================================================================
#
#          FILE: tt.sh
# 
#         USAGE: ./tt.sh 
# 
#   DESCRIPTION: 
# 
#       OPTIONS: ---
#  REQUIREMENTS: ---
#          BUGS: ---
#         NOTES: ---
#        AUTHOR: Aut (yinjing), autyinjing@126.com
#  ORGANIZATION: 
#       CREATED: 2015年06月30日 13:52
#      REVISION:  ---
#===============================================================================


function print()
{
        echo $#
        echo $@
        echo $*
}

print hello world nani ?
