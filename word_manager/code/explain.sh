#/bin/bash - 
#===============================================================================
#
#          FILE: explain.sh
# 
#         USAGE: ./explain.sh 
# 
#   DESCRIPTION: 简易单词管理程序
# 
#       OPTIONS: ---
#  REQUIREMENTS: ---
#          BUGS: ---
#         NOTES: ---
#        AUTHOR: Aut (yinjing), autyinjing@126.com
#  ORGANIZATION: 
#       CREATED: 2015年06月29日 16:23
#      REVISION:  ---
#===============================================================================

# 1 可执行文件的查找路径设置
PATH=/bin:/sbin:/usr/bin:/usr/sbin:/usr/local/bin:/usr/local/sbin:~/bin
export PATH

# 2 相关的全局变量声明和设置
home_path=~/.word_manager               #相关文件的主目录
lib_path=$home_path/.word_lib.txt       #词库文件的路径

# 3 相关目录和文件的设置
if [ ! -d "$home_path" ]; then
        mkdir $home_path        #~/.word_manager
        touch $lib_path         #~/.word_manager/.word_lib.txt
fi

# 4 相关函数实现
function query()                #直接查询单词信息
{
        ret=$(cat $lib_path | grep "$1")
        if [ -z "$ret" ]; then
                echo "$1 not be found!"
        else
                echo "$ret"
        fi
}

function update_lib()           #对词库进行排序去重，目前还没有想到更好的方法,只能利用临时文件
{
        cat $lib_path | sort -fb | uniq > ~/.word_manager/._word_lib.txt
        rm $lib_path
        mv ~/.word_manager/._word_lib.txt $lib_path
}

function print_count()
{
        ret=$(wc -l $lib_path | cut -d ' ' -f1 | grep '[[:digit:]]')
        echo "当前词库共有$ret个单词"
}

function add_to_lib()           #添加单词到词库
{
        word=$1\ $2             #将新的单词信息保存为一整行
        echo "$word" >> $lib_path    #~/.word_manager/.word_lib.txt
        update_lib
        echo "成功将 $word 导入词库!"
        print_count
}

function add_from_file()        #通过文件导入词库
{
        cat $1 >> $lib_path     #~/.word_manager/.word_lib.txt
        update_lib
        echo "成功将 $1 内的单词导入词库！"
        print_count
}

function browse_lib()
{
        echo ""
        more $lib_path
        echo ""
        print_count
}

function print_help()
{
        echo ""
        echo "用法: explain [选项] [单词|文件名] [单词信息]"
        echo ""
        echo "选项:"
        echo "  不带选项: 查询单词并打印出查询结果"
        echo "  -a     : 将单词信息导入词库,后跟单词和单词信息"
        echo "  -f     : 从文件导入词库,后跟要导入的文件名"
        echo "  -c     : 统计词库中的单词总数"
        echo "  -b     : 浏览词库中单词信息"
        echo "  --help : 显示帮助信息"
        echo ""
}

# 5 主程序部分
if [ "$#" -lt 1 ]; then         #首先判断命令格式是否正确
        print_help
        exit 1
fi

opt=$(echo $* | cut -d ' ' -f1 | grep '^-')     #解析选项
case $opt in
        "")
                query $1
                ;;
        "-a")
                if [ "$#" -eq "3" ]; then
                        add_to_lib $2 $3
                else
                        echo "正确格式：explain -a word wordinfo"
                        exit 3
                fi
                ;;
        "-f")
                if [ -f "$2" ]; then
                        add_from_file $2
                else
                        echo "不存在的文件 $2"
                        exit 4
                fi
                ;;
        "-c")
                print_count
                ;;
        "-b")
                browse_lib
                ;;
        "--help")
                print_help
                ;;
        *)
                echo "未知的选项，输入 explain --help 查看帮助信息"
                exit 2
esac

exit 0
