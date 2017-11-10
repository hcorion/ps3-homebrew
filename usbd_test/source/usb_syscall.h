#ifndef __USB_SYSCALL_H__
#define __USB_SYSCALL_H__

#include <ppu-lv2.h>
#include <ppu-asm.h>
#include <lv2/sysfs.h>
#include <ppu-types.h>

LV2_SYSCALL sys_usbd_initialize(unsigned int *initVal)
{
	lv2syscall1(530, initVal);
	return_to_user_prog(int);
}
LV2_SYSCALL sys_usbd_get_device_list(unsigned int handle, void *device_list, char unknown)
{
	lv2syscall3(532, handle, device_list, unknown);
	return_to_user_prog(int);
}
LV2_SYSCALL sys_usbd_get_descriptor_size(unsigned int handle, unsigned int unk1)
{
	lv2syscall2(533, handle, unk1);
	return_to_user_prog(int);
}

LV2_SYSCALL sys_usbd_get_descriptor(unsigned int handle, unsigned int unk1, void *descriptor, signed long descSize)
{
	lv2syscall4(534, handle, unk1, descriptor, descSize);
	return_to_user_prog(int);
}

LV2_SYSCALL sys_usbd_receive_event(unsigned int handle, unsigned long long int *unk1, unsigned long long int *unk2, unsigned long long int *unk3)
{
	lv2syscall4(540, handle, unk1, unk2, unk3);
	return_to_user_prog(int);
}

LV2_SYSCALL sys_usbd_register_extra_ldd(unsigned int handle, void *lddOps, unsigned int strLen, unsigned short vendorID, unsigned short productID, unsigned short unk1)
{
	lv2syscall6(559, handle, lddOps, strLen, vendorID, productID, unk1);
	return_to_user_prog(unsigned long long int);
}
#endif
