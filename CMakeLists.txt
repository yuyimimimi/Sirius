file(GLOB_RECURSE SOURCES                ./*.c)
#系统初始化文件
file(GLOB_RECURSE init                   ./kernel/init/*.c)
file(GLOB_RECURSE GPIO_HAL                 ./kernel/toos/arch/espidf/drivers/gpio/*.c)
file(GLOB_RECURSE ENV                      ./kernel/toos/env/*.c)                     #环境变量管理
file(GLOB_RECURSE SCRIPTS_STORE            ./kernel/toos/data_scripts/*.sh)           #脚本文件处理目录，用于负责键值对文件增删改查
file(GLOB_RECURSE DTS                      ./kernel/toos/dts/*.c)                     #简易的设备树解析器
file(GLOB_RECURSE system_memory_management ./kernel/mm/*.c)

# 命令行工具
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

file(GLOB_RECURSE gpio_subsystem           ./kernel/drivers/gpio/*.c)              
file(GLOB_RECURSE display_farmerwork       ./kernel/drivers/video/src/*.c)         
file(GLOB_RECURSE ESP_CONSOLE              ./kernel/drivers/tty/console/*.c)

#文件系统
file(GLOB_RECURSE FS_FAT                   ./kernel/fs/Fatfs/*.c)
file(GLOB_RECURSE FS_VFS_SRC               ./kernel/fs/vfs/*.c)                    
file(GLOB_RECURSE FS_VFS                   ./kernel/fs/*.c) 

#ESP-IDF组件
file(GLOB_RECURSE ESP_SPI_FAT            ./kernel/toos/arch/espidf/esp_spi_fat/*.c)
file(GLOB_RECURSE ESP_SPIFFS             ./kernel/toos/arch/espidf/esp_spi_spiffs/*.c)
file(GLOB_RECURSE ESP_LITTLEFS           ./kernel/toos/arch/espidf/esp_spi_littlefs/*.c)
file(GLOB_RECURSE ESP_FS                 ./kernel/toos/arch/esidf/*.c)

idf_component_register(    
        SRCS    ${SOURCES} 
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
                ${display_farmerwork}
                ${system_memory_management}
                ${GPIO_HAL}
                ${FS_VFS_SRC}
                ${ENV}
                ${SCRIPTS_STORE}
                ${DTS}
    INCLUDE_DIRS 
                 #内核api目录
                 "kernel/include"                            #内核接口目录 
                 #工具目录
                 "kernel/toos/arch/espidf/include"           #esp-idf组件目录
                 "kernel/toos/include"                       #内核工具接口目录
                 "kernel/drivers/video/include"             
                 "kernel/drivers/include"
                 "kernel/init"
                 "kernel/arch/rsicv/include"  
)



