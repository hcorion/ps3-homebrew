#include <usb/usb.h>
#include <sysmodule/sysmodule.h>
#include "usb_syscall.h"
#include <ppu-lv2.h>
#include <ppu-asm.h>
#include <lv2/sysfs.h>
#include <ppu-types.h>
#include <stdio.h>
#include <string.h>

void skylandersDump()
{
	u32 handle = 0;
	sys_usbd_initialize(&handle);
	char* device_list = malloc (50);
	sys_usbd_get_device_list(handle, device_list, 0x7f);
	char* name = "HID Device Driver";
	// Vendor ID and product ID for skylanders portal respectively
	const u16 portal_vid = 0x1430;
	const u16 portal_pid = 0x0150;
	u64 lddHandle = sys_usbd_register_extra_ldd(handle, name, strlen(name), portal_vid, portal_pid, portal_pid);
	u64 arg1 = 0, arg2 = 0, arg3 = 0;
	while (arg1 != SYS_USBD_DEVICE_STATUS_UNK)
	{
		sys_usbd_receive_event(handle, &arg1, &arg2, &arg3);
		printf("sys_usbd_receive_event(arg1=%ld, arg2=%ld, arg3=%ld)\n", arg1, arg2, arg3);
	}
	sys_usbd_attach(handle, lddHandle, arg2, arg2);
	sys_usbd_open_default_pipe(handle, arg2);
	// Yay magic numbers
	sys_usbd_open_pipe(handle, arg2, 0x1, 0x0, 0x0, 0x81, 0x3);
	usbDeviceRequest req;
	req.bmRequestType = 0x0;
	req.bRequest = 0x9;
	req.wValue = 0x1;
	req.wIndex = 0x0;
	req.wLength = 0x0;
	sys_usbd_transfer_data(handle, 0x0, NULL, 0, &req, 0x8);
	printf("sys_usbd_transfer_data: mbRequestType=0x%x, bRequest=0x%x, wValue=0x%x, wIndex=0x%x, wLength=0x%x\n",
		   req.bmRequestType, req.bRequest, req.wValue, req.wIndex, req.wLength);
	u32 result = 0;
	u32 count = 0;
	sys_usbd_get_transfer_status(handle, 0x0, 0x2, &result, &count);
	printf("sys_usbd_get_transfer_status: result=%d, count=%d\n", result, count);
	char* in_buf = malloc(0x20);
	sys_usbd_transfer_data(handle, 0x1, in_buf, 0x20, NULL, 0);
	for (int i = 0; i < 0x20; i++)
	{
		printf("0x%x\n", *(in_buf + i));
	}
}

int main()
{
	sysModuleLoad(SYSMODULE_USB);
	
	//////////
	// Init //
	//////////
	skylandersDump();
	return 0;


	// Old code
	
	/*unsigned int uuid = 0;
	sys_usbd_initialize(&uuid);
	// sys_usbd_initiallize returns: 
	//805322496
	//805308161
	/////////////////////
	// Get device list //
	/////////////////////
	char* funkyaddr = malloc (50);
	printf("device_list addr: 0x%x\n", funkyaddr);
	char thatchar = 0x7f;
	int numOfDevices = sys_usbd_get_device_list(uuid, funkyaddr, thatchar);
	
	printf("Number of devices: %d\n", numOfDevices);
	
	int crazyman = 0;
	while (crazyman < 40)
	{
		char word[22];
		memset(word, '\0', sizeof(word));
		int length = 0;
		for (int i = 0; i < 4; i++)
		{
			
			unsigned char* x = funkyaddr + (crazyman);
			crazyman += 1;
			length += sprintf(word + length, "0x%x ", *x);
		}
		word[21] = '\0';
		// If there is no data, don't bother printing it.
		if (strcmp(word, "0x0 0x0 0x0 0x0 "))
		{
			printf("%s\n", word);
		}
	}
	free(funkyaddr);
	
	//////////////////////
	// Descriptor tests //
	//////////////////////
	for (unsigned int i = 2; i <= numOfDevices+1; i++)
	{
		unsigned int oldI = 0;
		if (i == 2)
		{
			oldI = 2;
			i = 65538;
		}
		else if (i == 3)
		{
			oldI = i;
			i = 65539;
		}
		
		printf("Device: %u\n", i);
		
		int descSize = sys_usbd_get_descriptor_size(uuid, i);
		
		printf("descriptor_size: i=%d, descSize=%d\n", i, descSize);
		
		if (descSize < 0)
		{
			printf("sys_usbd_get_descriptor_size failed with 0x%x\n", descSize);
			continue;
		}
		
		// time to actually get the descriptor
		char* descriptor = malloc (descSize);
		printf("Descriptor: 0x%x\n", descriptor);
		printf("descSize as hex: 0x%x\n", descSize);
		printf("uuid: %u\n", uuid);
		
		int ret = sys_usbd_get_descriptor(uuid, i, descriptor, descSize);
		printf("get_descriptor: i=%d, descSize=%d ret=%d\n", i, descSize, ret);
		for (int i = 0; i < descSize; i++)
		{
			unsigned char* x = descriptor + (i);
			printf("0x%x\n", *x);
		}
		free(descriptor);
		
		if (oldI != 0)
		{
			i = oldI;
		}
	}
	
	//////////////////////////////
	// Register Extra Ldd Tests //
	//////////////////////////////
	//sys_usbd_register_extra_ldd(handle=805322496, lddOps=0xe5a4b0, unk1=17, vendorID=5168, productID=336, unk2=336)
	char* blargStringTM = malloc(30);
	blargStringTM = "HID Device Driver";
	unsigned long long int ret = sys_usbd_register_extra_ldd(uuid, blargStringTM, 17, 5168, 336, 336);
	printf("sys_usbd_register_extra_ldd: ret = %llu\n", ret);
	
	/////////////////////////
	// receive event tests //
	/////////////////////////
	// It seems like receive event only works after register_extra_ldd
	for (int i = 0; i < 2; i++)
	{
		unsigned long long int unk1 = 0;
		unsigned long long int unk2 = 0;
		unsigned long long int unk3 = 0;
		printf("Before receive_event\n");
		ret = sys_usbd_receive_event(uuid, &unk1, &unk2, &unk3);
		printf("After receive_event\n");
		printf("sys_usbd_receive_event: ret=%d, unk1=%llu, unk2=%llu, unk3=%llu\n", ret, unk1, unk2, unk3);
	}
	
	int descSize = sys_usbd_get_descriptor_size(uuid, 6);
		
	printf("descriptor_size: descSize=%d\n", descSize);
	// time to actually get the descriptor
	char* descriptor = malloc (descSize);
	printf("Descriptor: 0x%x\n", descriptor);
	
	ret = sys_usbd_get_descriptor(uuid, 6, descriptor, descSize);
	printf("get_descriptor: descSize=%d ret=%d\n", descSize, ret);
	for (int i = 0; i < descSize; i++)
	{
		unsigned char* x = descriptor + (i);
		printf("0x%x\n", *x);
	}
	return 0;*/
}