This folder is used to store the source code of each module.
The driver source code does not need to be modified, please configure the device driver by modifying the device tree file.
The module_init macro is the only interface to the kernel, you can add or comment out the module_init macro to control the loading of the module, and you can comment out the unnecessary modules.

本文件夹用于存放各个模块的源代码
驱动源代码不需要进行任何修改，请通过修改设备树文件来配置设备驱动
module_init初始化宏是面向内核的唯一接口，你可以通过添加或者注释掉module_init宏来控制模块的加载，不需要的模块可以注释掉。

このフォルダは各モジュールのソースコードを格納するために使用されます。
ドライバーソースコードは変更する必要はありません。デバイスツリーファイルを変更することでデバイスドライバーを構成できます。
module_initマクロはカーネルに対する唯一のインターフェイスです。モジュールの読み込みを制御するために、追加またはコメントアウトすることができます。不要なモジュールをコメントアウトすることもできます。
