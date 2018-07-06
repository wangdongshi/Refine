|--　Makefile<br>
|--　include<br>
|　　|--　lddbus.h　　　　　　　示例代码中，#include　"lddbus.h"。<br>
|--　lddbus<br>
|　　|--　Makefile<br>
|　　|--　lddbus.c　　　　　　　CHAPTER_14.4:虚拟总线实现<br>
|--　misc-modules<br>
|　　|--　Makefile<br>
|　　|--　complete.c　　　　　CHAPTER_5.4.　Completions　机制<br>
|　　|--　faulty.c　　　　　　　CHAPTER_4.5.1.　oops　消息<br>
|　　|--　hello.c　　　　　　　　CHAPTER_2.2：超级用户可以加载和卸载模块示例。<br>
|　　|--　hellop.c　　　　　　　CHAPTER_2.8.　模块参数<br>
|　　|--　jiq.c　　　　　　　　　　CHAPTER_7.6.1.　共享队列<br>
|　　|--　jit.c　　　　　　　　　　CHAPTER_7.4.1.　定时器　API<br>
|　　|--　kdataalign.c　　　CHAPTER_11.4.4.　数据对齐展示编译器如何强制对齐<br>
|　　|--　kdatasize.c　　　　CHAPTER_11.1：标准C类型的使用。显示长整型和指针在64位平台上的不同大小。<br>
|　　|--　seq.c　　　　　　　CHAPTER_4.3.1.4.　seq_file　接口<br>
|　　|--　silly.c　　　　　　CHAPTER_9.4.5.　在1MB之下的ISA　内存<br>
|　　|--　sleepy.c　　　　　CHAPTER_6.2.2.　简单睡眠<br>
|--　misc-progs<br>
|　　|--　Makefile<br>
|　　|--　asynctest.c　　　　CHAPTER_6.4.　异步通知<br>
|　　|--　dataalign　　　　　CHAPTER_11.4.4.　数据对齐展示编译器如何强制对齐<br>
|　　|--　dataalign.c　　　　CHAPTER_11.4.4.　数据对齐展示编译器如何强制对齐<br>
|　　|--　datasize　　　　　CHAPTER_11.1：标准C类型的使用。<br>
|　　|--　datasize.c　　　　CHAPTER_11.1：标准C类型的使用。<br>
|　　|--　gdbline　　　　　　CHAPTER_4.6.1.　使用gdb。为给定的模块可以创建这个命令<br>
|　　|--　inp　　　　　　　　CHAPTER_9.2.3.　从用户空间的I/O存取。从命令行读写端口的小工具,　在用户空间.<br>
|　　|--　inp.c<br>
|　　|--　load50　　　　　　CHAPTER_7.3.1.1.　忙等待。这个程序派生出许多什么都不做的进程,　但是以一种CPU-密集的方式来做.<br>
|　　|--　load50.c<br>
|　　|--　mapcmp　　　　　　Simple　program　to　compare　two　mmap'd　areas.<br>
|　　|--　mapcmp.c<br>
|　　|--　mapper　　　　　　CHAPTER_15.2.6.　重新映射　RAM<br>
|　　|--　mapper.c<br>
|　　|--　nbtest　　　　　　CHAPTER_6.2.6.　测试　scullpipe　驱动<br>
|　　|--　nbtest.c<br>
|　　|--　netifdebug　　　　CHAPTER_17.3.3.　接口信息<br>
|　　|--　netifdebug.c<br>
|　　|--　outp　　　　　　　CHAPTER_9.2.3.　从用户空间的I/O存取。从命令行读写端口的小工具,　在用户空间.<br>
|　　|--　outp.c<br>
|　　|--　polltest　　　　　Test　out　reading　with　poll()<br>
|　　|--　polltest.c<br>
|　　|--　setconsole　　　　CHAPTER_4.2.2.　重定向控制台消息<br>
|　　|--　setconsole.c<br>
|　　|--　setlevel　　　　　CHAPTER_4.2.1.　printk<br>
|　　|--　setlevel.c<br>
|--　pci<br>
|　　|--　Makefile<br>
|　　|--　pci_skel.c　　CHAPTER_12.1.5.　注册一个PCI驱动<br>
|--　sbull<br>
|　　|--　Makefile<br>
|　　|--　sbull.c　　　　CHAPTER_16.1.　注册<br>
|　　|--　sbull.h<br>
|　　|--　sbull_load<br>
|　　|--　sbull_unload<br>
|--　scull　　　　　　　CHAPTER_3.　字符驱动。scull(Simple Character Utility for Loading Localities)<br>
|　　|--　Makefile<br>
|　　|--　access.c<br>
|　　|--　main.c<br>
|　　|--　main.c.bak<br>
|　　|--　pipe.c<br>
|　　|--　pipe.c.bak<br>
|　　|--　scull.h<br>
|　　|--　scull.init<br>
|　　|--　scull_load<br>
|　　|--　scull_unload<br>
|--　scullc　　　　　　CHAPTER_8.2.1.　基于slab高速缓存的scull:scullc<br>
|　　|--　Makefile<br>
|　　|--　main.c<br>
|　　|--　mmap.c<br>
|　　|--　scullc.h<br>
|　　|--　scullc_load<br>
|　　|--　scullc_unload<br>
|--　sculld　　　　　　CHAPTER_14.4.2.3.　设备结构嵌入<br>
|　　|--　Makefile<br>
|　　|--　main.c<br>
|　　|--　mmap.c<br>
|　　|--　sculld.h<br>
|　　|--　sculld_load<br>
|　　|--　sculld_unload<br>
|--　scullp　　　　　　CHAPTER_8.3.1.　使用整页的scull:　scullp，该例子在后面第15章还会使用。<br>
|　　|--　Makefile<br>
|　　|--　main.c<br>
|　　|--　mmap.c<br>
|　　|--　scullp.h<br>
|　　|--　scullp_load<br>
|　　|--　scullp_unload<br>
|--　scullv　　　　　　CHAPTER_8.4.1.　使用虚拟地址的scull:　scullv，该例子在后面15.2.7.　重映射内核虚拟地址还有介绍<br>
|　　|--　Makefile<br>
|　　|--　main.c<br>
|　　|--　mmap.c<br>
|　　|--　scullv.h<br>
|　　|--　scullv_load<br>
|　　|--　scullv_unload<br>
|--　short　　　　　　CHAPTER_10　演示中断<br>
|　　|--　Makefile<br>
|　　|--　short.c<br>
|　　|--　short_load<br>
|　　|--　short_unload<br>
|--　shortprint　　　CHAPTER_10　写缓冲区示例<br>
|　　|--　Makefile<br>
|　　|--　shortprint.c<br>
|　　|--　shortprint.h<br>
|　　|--　shortprint_load<br>
|　　|--　shortprint_unload<br>
|--　simple　　　　　CHAPTER_15.2.　mmap设备操作。simple(Simple Implementation Mapping Pages with Little Enthusiasm)<br>
|　　|--　Makefile<br>
|　　|--　simple.c<br>
|　　|--　simple_load<br>
|　　|--　simple_unload<br>
|--　skull　　　　　LDD2：skull.c对ISAI/O的内存探测分析<br>
|　　|--　Makefile<br>
|　　|--　skull_clean.c<br>
|　　|--　skull_init.c<br>
|--　snull　　　　　　CHAPTER_17.2.　连接到内核<br>
|　　|--　Makefile<br>
|　　|--　snull.c<br>
|　　|--　snull.h<br>
|　　|--　snull_load<br>
|　　|--　snull_unload<br>
|--　tty　　　　　　　CHAPTER_18.　TTY驱动<br>
|　　|--　Makefile<br>
|　　|--　tiny_serial.c<br>
|　　|--　tiny_tty.c<br>
|--　usb　　　　　　　CHAPTER_13.　USB驱动<br>
|　　|--　Makefile<br>
|　　|--　usb-skeleton.c<br>