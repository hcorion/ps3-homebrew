#include <usb/usb.h>
#include <sysmodule/sysmodule.h>
#include "usb_syscall.h"
#include <ppu-lv2.h>
#include <ppu-asm.h>
#include <lv2/sysfs.h>
#include <ppu-types.h>
#include <stdio.h>
int main()
{
	// sys_usbd_initiallize returns: 
	//805322496
	//805308161
	sysModuleLoad(SYSMODULE_USB);
	// Init
	unsigned int uuid = 0;
	sys_usbd_initialize(&uuid);
	// Get device list
	char* funkyaddr = malloc (50);
	printf("0x%x\n", funkyaddr);
	char thatchar = 0x7f;
	int numOfDevices = sys_usbd_get_device_list(uuid, funkyaddr, thatchar);
	printf("Number of devices: %d\n", numOfDevices);
	
	for (int i = 0; i < 50; i++)
	{
		unsigned char* x = funkyaddr + (i);
		printf("0x%x\n", *x);
	}
	free(funkyaddr);
	// Descriptor test
	unsigned int unk1 = 65538;
	int descSize = sys_usbd_get_descriptor_size(uuid, unk1);
	// Returns 50, unk1 doesn't change.
	printf("unk1=%d, descSize=%d\n", unk1, descSize);
	// time to actually get the descriptor
	char* descriptor = malloc (50);
	printf("0x%x\n", funkyaddr);
	/*
	 * 00 00 00 00 d0 08 0a 48 32 0d c1 a8 00 00 00 81 
20 01 00 b4 20 01 00 b4 00 00 00 00 00 00 00 80 
00 00 00 00 00 00 01 00 00 00 00 00 00 00 01 00 
00 00
	 */
	//descriptor[4] = 0xd0;
	//descriptor[5] = 0x08;
	//descriptor[6] = 0x0A;
	//descriptor[7] = 0x48;
	char array[50] = {0x00, 0x00, 0x00, 0x00, 0xd0, 0x08, 0x0a, 0x48, 0x32, 0x0d, 0xc1, 0xa8, 0x00, 0x00, 0x00, 0x81, 
0x20, 0x01, 0x00, 0xb4, 0x20, 0x01, 0x00, 0xb4, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 
0x00, 0x00};
	memcpy(descriptor, array, 50);
	int ret = sys_usbd_get_descriptor(uuid, unk1, descriptor, descSize);
	printf("unk1=%d, descSize=%d ret=%d\n", unk1, descSize, ret);
	for (int i = 0; i < 50; i++)
	{
		unsigned char* x = descriptor + (i);
		printf("0x%x\n", *x);
	}
	free(descriptor);
	return 0;
}
