#include <usb/usb.h>
#include <sysmodule/sysmodule.h>
int main()
{
	sysModuleLoad(SYSMODULE_USB);
	usbInit();
	for (int i = 0; i < 50; i++)
	{
		unsigned char* x = 0xd0100760 + (i);
		printf("0x%x\n", *x);
	}
	sleep(10);
	return 0;
}
