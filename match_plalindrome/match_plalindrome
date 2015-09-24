#!/bin/bash - 
#===============================================================================
#
#          FILE: match_plalindrome.sh
# 
#         USAGE: ./match_plalindrome.sh 
# 
#   DESCRIPTION: 
# 
#       OPTIONS: ---
#  REQUIREMENTS: ---
#          BUGS: ---
#         NOTES: ---
#        AUTHOR: Aut (yinjing), autyinjing@126.com
#  ORGANIZATION: 
#       CREATED: 2015年06月30日 19:13
#      REVISION:  ---
#===============================================================================

# 1 判断命令格式是否正确
if [ "$#" -ne 1 ];
then
        echo "Usage: $0 filename"
        exit 1
fi

# 2 全局变量的声明和设置
filename=$1             #要查找的文件名
tmpfile=tmp.txt         #临时文件的文件名
declare -i count        #回文串的重复部分长度

# 3 由于原文件中的内容可能不是每行一个单词，所以这里要使用一个临时文件将原文件的信息转换为每行一个单词
cat $filename | tr '[ ,.?:!]' '\n' > $tmpfile    #将所有的标点符号及空格替换为换行符
sed -i '/^$/d' $tmpfile         #删除所有空行

# 4 默认查找长度为3到20的回文串
for ((len=3; len<=20; len++))   #循环查找各个长度的回文串
do
        basepattern='/^\(.\)'   #基础模式
        count=$(( $len / 2 ))   #计算重复部分的长度
        
        for ((i=1; i<$count; i++))      #设置正则表达式
        do
                basepattern=$basepattern'\(.\)'
        done

        if [ $(( $len % 2 )) -ne 0 ];     #判断字符串长度是奇数还是偶数并设置对称轴
        then
                basepattern=$basepattern'.'
        fi

        for ((count; count>0; count--)) #设置反向引用
        do
                basepattern=$basepattern'\'"$count"
        done

        basepattern=$basepattern'$/p'   #添加打印参数

        sed -n "$basepattern" $tmpfile
done

# 5 删除临时文件
rm $tmpfile

exit 0
