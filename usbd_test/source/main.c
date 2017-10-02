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
	sys_usbd_get_device_list(uuid, funkyaddr, thatchar);
	
	for (int i = 0; i < 20; i++)
	{
		unsigned char* x = funkyaddr + (i);
		printf("0x%x\n", *x);
	}
	free(funkyaddr);
	return 0;
}
