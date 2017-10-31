#ifndef __SYS_FILE_H__
#define __SYS_FILE_H__

#include <ppu-lv2.h>
#include <ppu-asm.h>
#include <lv2/sysfs.h>
#include <ppu-types.h>

LV2_SYSCALL sys_net_infoctl(int cmd, void *arg)
{
	lv2syscall2(722, cmd, arg);
	return_to_user_prog(int);
}

LV2_SYSCALL sys_usbd_initialize(unsigned int *initVal)
{
	//register u64 p1;// asm("3");
	lv2syscall1(530, initVal);
	//printf ("%u", *initVal);
	return_to_user_prog(int);
}

//sys_usbd_get_device_list(u32 handle, vm::ptr<void> device_list, char unknown)
LV2_SYSCALL sys_usbd_get_device_list(unsigned int handle, void *device_list, char unknown)
{
	lv2syscall3(532, handle, device_list, unknown);
	//printf ("%u", *initVal);
	return_to_user_prog(int);
}
#endif
