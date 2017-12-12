#include <usb/usb.h>
#include <sysmodule/sysmodule.h>
#include <ppu-lv2.h>
#include <ppu-asm.h>
#include <lv2/sysfs.h>
#include <sys/file.h>
#include <ppu-types.h>
#include <stdio.h>

int main()
{
    char str[] = "";
    unsigned int ret = sysFsUnlink(str);
    printf("sys_fs_unlink("") returned: %u\n", ret);
    sysFSStat blarg;
    ret = sysLv2FsStat(0x0, &blarg);
    printf("sys_fs_stat(0x0) returned: %u\n", ret);
	return 0;
}
