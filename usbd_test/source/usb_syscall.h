#ifndef __USB_SYSCALL_H__
#define __USB_SYSCALL_H__

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
//sys_usbd_get_device_list(u32 handle, vm::ptr<void> device_list, char unknown)
LV2_SYSCALL sys_usbd_get_device_list(unsigned int handle, void *device_list, char unknown)
{
	lv2syscall3(532, handle, device_list, unknown);
	//printf ("%u", *initVal);
	return_to_user_prog(int);
}
LV2_SYSCALL sys_usbd_get_descriptor_size(unsigned int handle, unsigned int unk1)
{
	lv2syscall2(533, handle, unk1);
	//printf ("%u", *initVal);
	return_to_user_prog(int);
}
#endif
