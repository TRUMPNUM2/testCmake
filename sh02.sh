#!/bin/bash
echo "test"
PATH=/bin:/sbin:/usr/bin/:/usr/sbin:/usr/local/bin:/usr/local/sbin:~/bin
export PATH
echo "export path"
data1=$(date --date='2 days ago' +%Y%m%d)

echo "time is $data1"
read -p "please input your firstname:" firstname # 第一个参数

read -p "please input your lastname:" lastname # 第一个参数

echo  "your full name is $firstname $lastname"

read -p "please input your filename:" fileuser 

filename=${fileuser:-filename222222222222}
echo "$filename"

echo $(printf %x 18)

user=$(cut -d':' -f1 /etc/passwd)
for username in $user
do
    id $username
    finger $username
done 

# network="192.168.1"
# for sitenu in $(seq 1 100)
# do
#     ping -c 1 -w 1 ${network}.${sitenu} &> /dev/null&&result=0||result=1
#     if ["$result"=0];then
#        echo "text here"
#     else
#         echo "server ${network}.${sitenu} is down"
#     fi 
# done

for ((i=1;i<=10;i++))
do   
echo $(expr $i \* 3 + 1)
done