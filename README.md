本项目由于技术债务过重，已经停止维护

如果你对在单片机上模拟linux内核感兴趣，你可以看看这个项目:https://github.com/yuyimimimi/microkernel


感谢你看到这个项目，如果你也想使用类似于嵌入式linux的方式开发你的基于espidf平台的单片机项目。你可以试试它。

如果你更习惯裸机程序，也可以把它当作辅助插件。不强制使用框架开发

示例项目中有移植教程，直接基于示例项目开发就行

如果喜欢请务必点击start

本项目经常更新，请注意变动
现在的内核过度混乱而且移植不够友好重构中。。。


关于项目：

本项目的宗旨是让单片机可以以尽可能贴近嵌入式linux的方式开发单片机。我为它加入了简易的设备树支持，并提供了各种尽可能贴近linux的内核api，还兼容posix，推荐使用posix规范的标准的控制台程序作为用户程序的功能模块并尽可能使用posix api

当然，它也同时兼容espidf的api，你可也以轻松移植你原有的裸机项目。

它有一套模仿linux的驱动框架，可以使用设备树调整驱动程序的平台差异。

目前已经支持大部分linux的常用shell指令。并且提供了环境变量管理，内核日志系统。

在这套软件中你可以通过模块框架，以模块化的方式开发控制台软件，驱动设备等，并将它们完全交给系统管理。之后你可以使用系统调用或者子系统api操作。此外它也可以使用python3语法开发功能。它支持c语言，C++与python混合编程。

它复刻了一些linux的内核api，用户api。你可以像linux一般使用它们。最好参考示例，因为它们可能和linux本身有部分不同。api本身也必定不如linux本身完整。目前只实现了最重要的部分

python语言的支持是通过pikapython项目实现的。你要是对这个项目有兴趣请务必转到它们的网站:[PikaPython 开发文档 — PikaPython 0.1 documentation](https://pikapython.com/doc/) 这是个很有趣的项目。而且使用标准的python3语法，拥有丰富的组件，良好的可移植性。如果你需要在你的项目中结核性使用python和c语言。请务选择它。

你如果不会安装espidf，可以使用带ESPIDF的VM虚拟机。环境已经配置好了,开箱即用:
http://47.94.220.165/index.php/2024/08/27/esp-idf5-2-2-%e5%b8%a6%e9%9b%86%e6%88%90%e5%bc%80%e5%8f%91%e7%8e%af%e5%a2%83%e7%9a%84windows%e8%99%9a%e6%8b%9f%e6%9c%ba/

关于移植：

直接使用示例工程就行。不建议自己移植



关于使用：

1.它可以使用字符设备驱动将驱动设备映射为文件系统的结点让你可以以文件读写的方式访问设备驱动。并且使用简单的设备树管理设备差异。使用module_init宏作为模块面向内核的唯一接口。并尽可能相似的方式模仿了linux的内核模块api。部分api由于平台问题性能问题进行了妥协。请注意差异

您可以查看./example_modules/drivers目录查看驱动程序模块的开发框架。以及简易设备树的的结构。main.c中展示模块的注册方式。你可以通过删除或添加初始化宏实现模块的添加。

2.它提供了linux风格的命令行工具，你可以使用基础的shell指令进行文件管理，文本编辑，脚本执行，任务管理，控制台程序的调用。使用help可以查看使用方式。

AppInit_init可用于console程序模块的添加。你可以查看./example_modules查看控制台程序模块的框架并在main.c中查看注册方式

3.不建议自行移植kernel文件夹。如果要使用该项目建议直接复制example_project中的项目模板并直接在vscode中打开。readme.md会告诉你应该怎么进行移植。

4.由于这是初版工程，许多方面还是比较粗糙，功能不是很完善，请各位理解。

5.示例工程的main目录下有中文英文版的移植指南。它的移植很简单

6.支持部分posix api以及unix系统api。




最新版本的终端效果：

<img width="621" alt="image" src="https://github.com/user-attachments/assets/21ab0e77-ea94-470d-96e8-b2dc4c12baab">










补充：

  1.目前设备子系统还不完善，它们的开发是一个漫长的过程...所以现在还不能完全和linux一样使用完全跨平台的设备子系统。

 
 2.你不需要对模块进行代码上的修改。模块的添加只需要参考mian.c。这些初始化宏是面向内核的
 唯一接口。模块间是高度解耦的，所以不需要在意它们之间的任何依赖方式。模块的添加删除是不会影响系统运行的，除非初始化阶段就有bug。

 3.所有字符设备驱动程序会被映射到dev目录下。你可以使用shell指令在console中查看。
 
 4.profile和dts文件非常重要，配置错误或者缺失等可能会导致系统崩溃，不过不用担心，多次奔溃后它会自动进入recovery mode中。你可以在这个模式下进行修复。
 
 5.项目可能存在一些bug，请理解.它还不是很完善

  6.新的虚拟文件系统正在构建中，目前的字符设备驱动是使用espidf本身的vfs二次封装魔改的。由于它基于spiffs，所以限制很多而且只支持扁平的目录结构

有任何疑问、希望提交代码可以访问我的邮箱

yu3174096586@gmail.com 
b站:
Siriusさん
支持的shell指令列表:

echo            cat            reboot         ls          clear         pwd 

cd              mkdir          history        uname       rm            rmdir  

free            kilo           vi             touch       jobs          ps  

kill            uptime         stat           sleep       printf        mv

cp              head           tail           date        whoami        i2cdetect  

python          help           sh             printenv     export       unset

env            dmesg           lv_demo
更新日志:

2024/11/2添加/kernel/config 文件夹

2024/11/2添加system() posix函数支持

2024/11/7更新内核日志系统

2024/11/12 更新日志系统，移植lvgl库，并加入显示设备管理子系统支持，
           支持运行线性没有控制流语句的shell脚本(控制流语句还有bug,所以
           不建议使用)，加入更多指令，修复部分bug。
           


