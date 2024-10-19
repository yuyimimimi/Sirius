# SiriusOS

感谢你看到这个项目，如果你也想使用类似于linux的方式开发你的espidf项目。你可以试试它。

您如果不太了解，可以查看我的个人博客:[http://47.94.220.165/index.php/2024/10/20/siriusos-0-1-0-%e7%89%88%e6%9c%ac/](http://47.94.220.165/index.php/2024/10/20/siriusos-0-1-0-%e7%89%88%e6%9c%ac/)
它会展示一些直观的使用。


它基于espidf模仿了linux的行为，只需要esp32系列任何单片机的最小系统模组就能运行，不需要任何外围硬件。它通过实现linux内核的api，能让你以linux的风格开发高度模块化且灵活的espidf项目。功能展示：
注:这里的0.07版本是我测试时使用的测试版本号。

<img width="459" alt="Screenshot 2024-10-19 141415" src="https://github.com/user-attachments/assets/f53123e5-9ca9-4852-84e7-31ca6a307d9b">

<img width="369" alt="Screenshot 2024-10-19 141553" src="https://github.com/user-attachments/assets/09d74e90-7bbd-447b-b5dc-e04b04d1f342">

<img width="429" alt="image" src="https://github.com/user-attachments/assets/aaf68913-8898-405c-bc92-a28eb4b71368">

<img width="447" alt="image" src="https://github.com/user-attachments/assets/cbb450fd-d021-4e4e-9fb7-d8f7fb11d98a">


关于使用：


1.它可以使用字符设备驱动将驱动设备映射为文件系统的结点让你可以以文件读写的方式访问设备驱动。并且使用简单的设备树管理设备差异。使用module_init等宏作为模块面向内核的唯一接口。并尽可能相似的方式模仿了linux的内核模块api。

您可以查看./example_modules/drivers目录查看驱动程序模块的开发框架。以及简易设备树的节点的结构。main.c中展示模块的注册方式。你可以通过删除或添加初始化宏实现模块的添加。

2.它提供了linux风格的命令行工具，你可以使用基础的shell指令进行文件管理，文本编辑，脚本执行，控制台程序的调用。使用help可以查看使用方式。
AppInit_init可用于console程序模块的添加。你可以查看./example_app查看控制台程序模块的框架并在main.c中查看注册方式

3.不建议自行移植kernel文件夹。如果要使用该项目简易直接复制example_project中的项目模板并直接在vscode中打开。readme.md会告诉你应该怎么进行移植。

4.由于这是初版工程，许多方面还是比较粗糙，功能不是很完善，请各位理解。

5.example_project/project/build中有已经完成编译的固件.如果你不知道是否有必要移植，你可以使用espidf插件打开并直接点击烧录按钮烧录以体。烧录后初次开机会进入recovery mode模式。此时系统是无法正常工作的，因为它高度依赖文件系统的资源文件。您可以查看readme.md获取配置方式。所有资源文件模板都在file文件夹中。你可以将它们复制到文件系统中。

profile文件会告诉系统应该使用怎么样的目录结构。你可以参考它构建文件系统中的资源信息。项目目前还是测试阶段并不完善，目前文件还是无法直接在编译时打包。您可以使用内核中内置的kilo文本编辑器实现文件内容的上传。注意，如果你要自己编译固件一定要使用espidf5.2.1版本。


补充：
 1.目前设备子系统还不完善，它们的开发是一个漫长的过程...
 
 2.你不需要对模块进行任何代码上的修改。模块的添加只需要参考mian.c。这些初始化宏是面向内核的
 唯一接口。模块间是高度解耦的，所以不需要在意它们之间的任何依赖方式。模块的添加删除是不会影响系统运行的，除非初始化阶段就有bug。


 3.所有驱动程序会被映射到dev目录下。你可以使用shell指令在onsole中查看。
 
 4.profile和dts文件非常重要，配置错误或者缺失等可能会导致系统崩溃，不过不用担心，奔溃后它会自动进入recovery mode中。你可以在这个模式下进行修复。
 
 5.项目可能存在一些bug，请理解.它还不是很完善



本项目禁止一切商业行为

本项目禁止一切商业行为

本项目禁止一切商业行为

有任何疑问或者希望提交代码，创建分支，可以访问我的邮箱

yu3174096586@gmail.com 

或者qq:3174096586

与我联系




