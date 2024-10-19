文件介绍：
Python_demo   : 用于提供一些python的示例代码,可以在单片机中使用 python [filename.py] 运行
bootlogo      : 用于显示启动logo,如果不用可以不添加
esp_console.c : 在espconsole的基础上插入钩子函数用于bash终端提供目录显示等。需要espidf5.2.1版本。请用它替换你得espidf库中的同名文件。
platforme.dts : 设备树文件，用于配置设备树参数。
profile       : 系统的环境变量配置文件，用于配置系统环境变量。


