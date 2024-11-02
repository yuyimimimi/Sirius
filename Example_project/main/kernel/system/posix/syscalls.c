#include <stdbool.h>
#include <stdlib.h>
#include <stdarg.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <reent.h>
#include <sys/fcntl.h>
#include "sdkconfig.h"
#include "esp_rom_uart.h"
#include "esp_console.h"

static int  syscall_not_implemented(struct _reent *r, ...)
{
    __errno_r(r) = ENOSYS;
    return -1;
}

static int  syscall_not_implemented_aborts(void)
{
    abort();
}

ssize_t __attribute__((weak))  _write_r_console(struct _reent *r, int fd, const void * data, size_t size)
{
    const char* cdata = (const char*) data;
    if (fd == STDOUT_FILENO || fd == STDERR_FILENO) {
        for (size_t i = 0; i < size; ++i) {
            esp_rom_uart_tx_one_char(cdata[i]);
        }
        return size;
    }
    __errno_r(r) = EBADF;
    return -1;
}

ssize_t __attribute__((weak))  _read_r_console(struct _reent *r, int fd, void * data, size_t size)
{
    char* cdata = (char*) data;
    if (fd == STDIN_FILENO) {
        size_t received;
        for (received = 0; received < size; ++received) {
            int status = esp_rom_uart_rx_one_char((uint8_t*) &cdata[received]);
            if (status != 0) {
                break;
            }
        }
        if (received == 0) {
            errno = EWOULDBLOCK;
            return -1;
        }
        return received;
    }
    __errno_r(r) = EBADF;
    return -1;
}

static ssize_t  _fstat_r_console(struct _reent *r, int fd, struct stat * st)
{
    if (fd == STDOUT_FILENO || fd == STDERR_FILENO) {
        memset(st, 0, sizeof(*st));
        /* This needs to be set so that stdout and stderr are line buffered. */
        st->st_mode = S_IFCHR;
        return 0;
    }
    __errno_r(r) = EBADF;
    return -1;
}

static int _fsync_console(int fd)
{
    if (fd == STDOUT_FILENO || fd == STDERR_FILENO) {
#ifdef CONFIG_ESP_CONSOLE_UART
        esp_rom_uart_flush_tx(CONFIG_ESP_CONSOLE_UART_NUM);
#elif defined(CONFIG_ESP_CONSOLE_USB_SERIAL_JTAG)
        esp_rom_uart_flush_tx(CONFIG_ESP_ROM_USB_SERIAL_DEVICE_NUM);
#elif defined(CONFIG_ESP_CONSOLE_USB_CDC)
        esp_rom_uart_flush_tx(CONFIG_ESP_ROM_USB_OTG_NUM);
#endif
        return 0;
    }
    errno = EBADF;
    return -1;
}


int __attribute__((weak)) system(const char* str)
{
    int a = 0;
    int *i =&a;
    esp_console_run(str,i);
    return 0;
}

int __attribute__((weak))  fcntl(int fd, int cmd, ...)
{
    va_list args;
    va_start(args, cmd);
    int arg = va_arg(args, int);
    va_end(args);
    struct _reent* r = __getreent();
    return _fcntl_r(r, fd, cmd, arg);
}

/* No-op function, used to force linking this file,
   instead of the syscalls implementation from libgloss.
 */
void __attribute__((weak))  newlib_include_syscalls_impl(void)
{
}
