#ifndef __SYS_FILE_H__
#define __SYS_FILE_H__

#include <ppu-lv2.h>
#include <ppu-asm.h>
#include <lv2/sysfs.h>
#include <ppu-types.h>

LV2_SYSCALL sys_usbd_initialize(unsigned int *initVal)
{
	//register u64 p1;// asm("3");
	lv2syscall1(530, initVal);
	//printf ("%u", *initVal);
	return_to_user_prog(int);
}
#endif
