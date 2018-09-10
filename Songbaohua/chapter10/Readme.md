1. 通过执行make可得到second.ko
2. 通过执行gcc -o second_test second_test.c可得到second_test
3. 执行以下命令以加载second设备（秒字符设备）
   insmod second.ko
   mknod /dev/second c 259 0
4. 通过执行./second_test可看到如下显示：

seconds after open /dev/second :3471  
seconds after open /dev/second :3472  
seconds after open /dev/second :3473  
seconds after open /dev/second :3474  
seconds after open /dev/second :3475  

4. 此时在另一终端通过执行dmesg可看到如下显示，这是驱动程序本身打印在系统Log中的信息：

[ 3611.926201] current jiffies is 828396  
[ 3612.925784] current jiffies is 828646  
[ 3613.925379] current jiffies is 828896  
[ 3614.924621] current jiffies is 829146  
[ 3615.924193] current jiffies is 829396  
[ 3616.923848] current jiffies is 829646  