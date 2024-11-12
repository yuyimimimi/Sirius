My name is YimingYu ,Who made this linux like system for esp series.

Thanks that you can use it for your project.

                                          This project is use GPL v2.0 license.
                                          
I will teach you how to run This project on your esp series mcu.

you need use espidf 5.2.1 version.

make sure you have 8mb flash size.
if lass than 8mb,you need change partition table.

I just tested it on esp32-s3 and esp32-c3.
This Templete project is default set to esp32-c3 which has 8mb flash size.

if you have 8mb flash size,and using esp32-c3. open shell and press "udf.py build"
Then  download the bin file to your esp series mcu.

you can use putty or other tool To connect to console.you can see recovery mode,use shell command to 
create file,edit file。 all file that you need is in /main/file folder.

use reboot command to restart system. you can see system booting message.

if your platfrom is not standard,you need change some code.

open this project in espidf cmd. and type "idf.py menuconfig" to config your project.
first set your board and flash size. 
set: Partition Table > Partition Table set to  Custom partition table CSV
set: Virtual file system > Maximum Number of Virtual Filesystems set to 20

if your flash size is lass than 8mb,you need change partition table.
p_0 table is important, do not change name ,and must use littlefs. you can change size.

then you can use "idf.py build" to build your project.

path /kernel/config is kernel config file. you can modify it according to your need.


中文版移植指南:

注意，要使用espidf5.2.1。其它版本我没有测试过。

示例项目是基于立创实战派开发板的，采用esp32C3 8mbflash .可以直接编译烧录，如果使用其它esp32需要进行一些调整。
首先需要在espidf中选择芯片型号。由于espidf修改芯片后kconfig会重置，所以需要重新配置。

 
如果你有psram最好开启它。然后需要配置flash大小。

开启自定义分区表。
（Partition Table
Partition Table
Custom partition table CSV
Custom partition CSV file
）
 
 模板项目的分区表使用8mbflash。你可以适当调整p_0和p_2分区大小以匹配你的flash
 p_0会挂载为/etc p_2会挂挂载为/home 。如果不需要/home可以直接删除那一行，不需要修改代码。

 之后将虚拟文件系统的挂载点(Maximum Number of Virtual Filesystems)设置为20。

 然后就可以编译烧录了。烧录后你会发现不断报错，因为缺少必要的资源文件。不过不用担心，多等待一会儿。它会进入recoverymode
. 在命令行中输入help，你可以看到resetdevice指令。使用它，它会建立基础的文件系统并生成默认的配置文件并重启。
重启后你会进入普通启动模式。使用shell指令

cd /etc/boot

 kilo dev.dts
进入file文件夹找到设备树配置文件，复制粘贴配置信息并按照你的需求进行修改。层次结构不能搞错。(由于串口速率限制以及esp32性能限制。文本编辑器不会很流畅，一次只能复制一小段，有些esp32会出现丢包)
然后使用reboot指令重启设备。你可以看到设备的启动日志并在/dev目录下找到设备结点。

移植就完毕了


/kernel/config 目录下有一些内核配置选项，可以根据自己的需求进行修改,它们是静态配置，类似于kernel.config文件。

关于功能:
about function

1.如果使用system()没有反应，请前往/espidf-v5.2.1(按照你实际安装的版本号)/components/newlib/syscalls.c 注释掉system()函数定义或者使用_sysyem()代替,但是你需要额外声名。


1.if you use system() function,please comment it in /espidf/components/newlib/syscalls.c

