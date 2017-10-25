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
	//////////////////////////////
	// Register Extra Ldd Tests //
	//////////////////////////////
	//sys_usbd_register_extra_ldd(handle=805322496, lddOps=0xe5a4b0, unk1=17, vendorID=5168, productID=336, unk2=336)
	char* blargStringTM = "HID Device Driver";
	int ret = sys_usbd_register_extra_ldd(uuid, blargStringTM, 17, 5168, 336, 336);
	printf("sys_usbd_register_extra_ldd: ret = %d\n", ret);
	
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
			//printf("0x%x\n", *x);
		}
		free(descriptor);
		
		if (oldI != 0)
		{
			i = oldI;
		}
	}
	
	/////////////////////////
	// receive event tests //
	/////////////////////////
	// It seems like receive event only works after register_extra_ldd
	for (int i = 0; i < 5; i++)
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
	return 0;
}
