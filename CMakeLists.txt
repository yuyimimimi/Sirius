# 收集所有源文件
file(GLOB_RECURSE SOURCES                ./*.c)
# 收集驱动源文件
file(GLOB_RECURSE DriverS     
         ./packages/drivers/*.c  
         ./packages/drivers/button/*.c
         ./packages/drivers/i2c/*.c
         )

#系统架构相关源文件
#file(GLOB_RECURSE ARCH_SOURCES_MM_S      ./kernel/arch/xtensa/mm/*.S)
file(GLOB_RECURSE ARCH_SOURCES_MM_S      ./kernel/arch/rsicv/mm/*.S)

#系统初始化文件
file(GLOB_RECURSE init                   ./kernel/init/*.c)
#芯片设备操作资源以及相关描述文件
file(GLOB_RECURSE GPIO_HAL               ./kernel/toos/arch/espidf/drivers/gpio/*.c)
file(GLOB_RECURSE ENV                    ./kernel/toos/env/*.c)                     #环境变量管理
file(GLOB_RECURSE SCRIPTS_STORE          ./kernel/toos/data_scripts/*.sh)           #脚本文件处理目录，用于负责类似于数据库的功能
file(GLOB_RECURSE DTS                    ./kernel/toos/dts/*.c)                     #设备树解析目录

# 收集命令行工具源文件
file(GLOB_RECURSE COMMANDS
    ./toos/shell/src/hello_APP/*.c
    ./toos/shell/src/cat/*.c
    ./toos/shell/src/echo/*.c
    ./toos/shell/src/reboot/*.c
    ./toos/shell/src/ls/*.c
    ./toos/shell/src/clear/*.c
    ./toos/shell/src/pwd/*.c
    ./toos/shell/src/cd/*.c
    ./toos/shell/src/mkdir/*.c
    ./toos/shell/src/history/*.c
    ./toos/shell/src/uname/*.c
    ./toos/shell/src/rm/*.c
    ./toos/shell/src/rmdir/*.c
    ./toos/shell/src/free/*.c
    ./toos/shell/src/kilo/*.c
)
#设备子系统
file(GLOB_RECURSE gpio_subsystem           ./kernel/drivers/gpio/*.c)              #GPIO驱动子系统
file(GLOB_RECURSE display_farmerwork       ./kernel/drivers/video/src/*.c)         #显示屏驱动子系统
file(GLOB_RECURSE ESP_CONSOLE              ./kernel/drivers/tty/console/*.c)       #串口控制台驱动子系统
#文件系统
file(GLOB_RECURSE FS_FAT                   ./kernel/fs/Fatfs/*.c)
file(GLOB_RECURSE FS_VFS_SRC               ./kernel/fs/vfs/*.c)                     #NFS文件系统
file(GLOB_RECURSE FS_VFS                   ./kernel/fs/*.c) 
#系统内存管理
file(GLOB_RECURSE system_memory_management ./kernel/mm/*.c)
#收集ESP-IDF组件源文件
file(GLOB_RECURSE ESP_SPI_FAT            ./kernel/toos/arch/espidf/esp_spi_fat/*.c)
file(GLOB_RECURSE ESP_SPIFFS             ./kernel/toos/arch/espidf/esp_spi_spiffs/*.c)
file(GLOB_RECURSE ESP_LITTLEFS           ./kernel/toos/arch/espidf/esp_spi_littlefs/*.c)
file(GLOB_RECURSE ESP_FS                 ./kernel/toos/arch/esidf/*.c)


file (   GLOB_RECURSE PIKA_PYTHON        

        ./modules/toos/pikapython/pikascript-api/*.c
        ./modules/toos/pikapython/pikascript-core/*.c
        ./modules/toos/pikapython/pikascript-lib/PikaStdLib/*.c
        )

file(   GLOB_RECURSE LVGL     

        ./libs/src/*.c
        ./libs/lvgl_driver/*.c
        ./libs/user_lv_font/*.c
        ./libs/user_lv_img/*.c
        ./libs/demos/*.c
        )

idf_component_register(    
        SRCS    ${SOURCES} 
                ${ARCH_SOURCES_MM_S}
                ${button_Driver}
                ${i2c_Driver}
                ${gpio_subsystem}
                ${FS_FAT}
                ${FS_VFS}
                ${ESP_CONSOLE}
                ${ESP_SPI_FAT}
                ${ESP_SPIFFS}
                ${ESP_LITTLEFS}
                ${ESP_FS}
                ${init}
                ${COMMANDS}
                ${MYAPPS}
                ${display_farmerwork}
                ${system_memory_management}
                ${other_Driver}
                ${GPIO_HAL}
                ${FS_VFS_SRC}
                ${ENV}
                ${SCRIPTS_STORE}
                ${DTS}

        INCLUDE_DIRS 
                 #内核api目录
                 "kernel/include"                            #内核接口目录 
                 #内核工具目录
                 "kernel/toos/arch/espidf/include"           #esp-idf组件目录
                 "kernel/toos/include"                       #内核工具接口目录
                 #设备子系统目录
                 "kernel/drivers/video/include"              #显示屏驱动子系统内部接口
                 "kernel/drivers/include"                    #设备子系统接口目录
                 #内核初始化目录
                 "kernel/init"
                 
                #架构相关接口目录
                 "kernel/arch/xtensa/include"  

                 "modules/toos/pikapython/pikascript-api"
                 "modules/toos/pikapython/pikascript-core"
                 "modules/toos/pikapython/pikascript-lib/PikaStdLib"     
                 
                 "libs/lvgl"
                 "libs" 
)


file (GLOB_RECURSE dts_file 
        "./file/esp32c3.dts"
        )
littlefs_create_partition_image(fs {dts_file} FLASH_IN_PROJECT)
