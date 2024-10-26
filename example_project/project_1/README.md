My name is YimingYu ,Who made this linux like system for esp series.

Thanks that you can use it for your project.

                                          This project is use GPL v2.0 license.
                                          and not support any business project.

I will teach you how to run This project on your esp series mcu.

you need use espidf 5.2.1 version.

first you need change esp_console.c file of espidf. new esp_console.c is in /main/file/esp_console.c 
then add "#define ADD_HOOK_SUPPORT_FOR_CONSOLE" into esp_console.h file.

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
