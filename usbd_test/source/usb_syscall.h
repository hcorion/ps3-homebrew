
#ifndef __USB_SYSCALL_H__
#define __USB_SYSCALL_H__

#include <ppu-lv2.h>
#include <usb/usb.h>

enum RECEIVE_EVENT_VALUES
{
	SYS_USBD_DEVICE_STATUS_FREE = 0,
	SYS_USBD_DEVICE_STATUS_UNK, // Unknown what this status state represents
	SYS_USBD_DEVICE_STATUS_CLAIMED,
};

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

LV2_SYSCALL sys_usbd_receive_event(unsigned int handle, u64 *unk1, u64 *unk2, u64 *unk3)
{
	lv2syscall4(540, handle, unk1, unk2, unk3);
	return_to_user_prog(int);
}

LV2_SYSCALL sys_usbd_register_extra_ldd(unsigned int handle, void *lddOps, unsigned int strLen, unsigned short vendorID, unsigned short productID, unsigned short unk1)
{
	lv2syscall6(559, handle, lddOps, strLen, vendorID, productID, unk1);
	return_to_user_prog(unsigned long long int);
}

LV2_SYSCALL sys_usbd_attach(unsigned int handle, unsigned int lddhandle, unsigned int device_id_high, unsigned int device_id_low)
{
	lv2syscall4(542, handle, lddhandle, device_id_high, device_id_low);
	return_to_user_prog(int);
}

LV2_SYSCALL sys_usbd_open_default_pipe(unsigned int handle, unsigned int device_handle)
{
	lv2syscall2(538, handle, device_handle);
	return_to_user_prog(int);
}

LV2_SYSCALL sys_usbd_open_pipe(u32 handle, u32 device_handle, u32 unk1, u32 unk2, u32 unk3, u32 endpoint_address, u32 type)
{
	lv2syscall7(537, handle, device_handle, unk1, unk2, unk3, endpoint_address, type);
	return_to_user_prog(int);
}

LV2_SYSCALL sys_usbd_transfer_data(u32 handle, u32 pipe, void* in_buf, u32 in_len, usbDeviceRequest* out_buf, u32 out_len)
{
	lv2syscall6(543, handle, pipe, in_buf, in_len, out_buf, out_len);
	return_to_user_prog(s64);
}
LV2_SYSCALL sys_usbd_get_transfer_status(u32 handle, u32 a2, u32 a3, u32* result, u32* count)
{
	lv2syscall5(545, handle, a2, a3, result, count);
	return_to_user_prog(s32);
}
#endif