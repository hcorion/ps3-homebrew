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
	unsigned int test = 0;
	sys_usbd_initialize(&test);
	printf("%u\n", test);
	unsigned int test2 = 0;
	sys_usbd_initialize(&test2);
	printf("%u\n", test2);
	/*usbInit();
	for (int i = 0; i < 50; i++)
	{
		unsigned char* x = 0xd0100760 + (i);
		printf("0x%x\n", *x);
	}
	sleep(10);
	return 0;*/
	return 0;
}
