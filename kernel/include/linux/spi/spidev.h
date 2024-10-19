#ifndef _LINUX_SPI_SPI_H
#define _LINUX_SPI_SPI_H

#include <linux/socket.h>
#include <linux/types.h>


#define SPI_IOC_RD_MODE _IOR('k', 0, __u8)
#define SPI_IOC_WR_MODE _IOW('k', 1, __u8)
#define SPI_IOC_RD_BITS_PER_WORD _IOR('k', 2, __u8)
#define SPI_IOC_WR_BITS_PER_WORD _IOW('k', 3, __u8)
#define SPI_IOC_RD_MAX_SPEED_HZ _IOR('k', 4, __u8)
#define SPI_IOC_WR_MAX_SPEED_HZ _IOW('k', 5, __u8)

typedef enum spi_trans_flags {
    SPI_XFER_BEGIN = 0,
    SPI_XFER_END = 1,
} spi_trans_flags_t;

struct spi_ioc_transfer {
    unsigned long *tx_buf;
    unsigned long *rx_buf;
    __u32 len;
    __u16 speed_hz;
    __u8  delay_usecs;
    __u8  bits_per_word;
    __u16 cs_change;
    spi_trans_flags_t flags;           // CS 引脚在空闲时为高电平
};


#endif /* _LINUX_SPI_SPI_H */