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
	sysModuleLoad(SYSMODULE_USB);
	
	//////////
	// Init //
	//////////
	unsigned int uuid = 0;
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
	
	unsigned char unk1 = 2;
	int descSize = sys_usbd_get_descriptor_size(uuid, unk1);
	// Returns 50, unk1 doesn't change.
	printf("descriptor_size: unk1=%d, descSize=%d\n", unk1, descSize);
	// time to actually get the descriptor
	char* descriptor = malloc (descSize);
	printf("Descriptor: 0x%x\n", descriptor);
	/*char array[50] = {0x00, 0x00, 0x00, 0x00, 0xd0, 0x08, 0x0a, 0x48, 0x32, 0x0d, 0xc1, 0xa8, 0x00, 0x00, 0x00, 0x81, 
	0x20, 0x01, 0x00, 0xb4, 0x20, 0x01, 0x00, 0xb4, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 
	0x00, 0x00};*/
	//memcpy(descriptor, array, 50);
	int ret = sys_usbd_get_descriptor(uuid, unk1, descriptor, descSize);
	printf("get_descriptor_size: unk1=%d, descSize=%d ret=%d\n", unk1, descSize, ret);
	for (int i = 0; i < 50; i++)
	{
		unsigned char* x = descriptor + (i);
		printf("0x%x\n", *x);
	}
	free(descriptor);
	return 0;
}
