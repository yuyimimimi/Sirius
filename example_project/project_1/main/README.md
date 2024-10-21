My name is yuyimimimi ,Who made this linux like system for esp series.

Thanks that you can use it for your project.

                                          This project is use GPL v2.0 license.
                                          and not support any business project.

I will teach you how to run This project on your esp series mcu.

you need use espidf 5.2.1 version.

This Templete project is default set to esp32-c3 which has 8mb flash size.

make sure you have 8mb flash size.
if lass than 8mb,you need change partition table.
p_0 table is important, do not change name ,and must use littlefs. you can change size.

set: Partition Table > Partition Table set to  Custom partition table CSV
set: Virtual file system > Maximum Number of Virtual Filesystems set to 20

if you have 8mb flash size,and using esp32-c3. you needn't set anythings.
open shell and press "udf.py build"
Then download the bin file to your esp series mcu.

you can use putty or other tool To connect to console.
you will see some error message. but don't worry.wait some time.
and you will see recovery mode.

user reset_device command to reset your esp series mcu.your device will default initialize.
Then reboot your device.use "ls" you can see many files and directories.
"cd boot" to change directory to boot partition.

"ls" you can see "dev.dts"
"kilo dev.dts" to edit device tree file.
you need peaste your device tree file here. device tree is in /project/main/file 

press "ctrl+S" to save and press "ctrl+Q" to exit.
use "reboot" command to restart system.
