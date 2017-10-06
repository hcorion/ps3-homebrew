#include <sysmodule/sysmodule.h>
#include <ppu-lv2.h>
#include <ppu-asm.h>
#include <lv2/sysfs.h>
#include <ppu-types.h>
#include <stdio.h>
#include "net_syscall.h"
#include <net/netctl.h>

// 4 Clienthax

int main()
{
	printf("loading net \n");
	sysModuleLoad(SYSMODULE_NET);
	printf("loading netctl \n");
	sysModuleLoad(SYSMODULE_NETCTL);
	
	netCtlInit();
	char* funkyaddr = malloc(256);
	uint8_t buffer[256];
	signed int cmd = 53;
	
	printf("calling syscall \n");
	int result = sys_net_infoctl(cmd, funkyaddr);//dns servers?
	printf("syscall done %x \n", result);

	
	//for(int i = 0; i < 256 i++)
	//{
	//	unsigned char* x = testaddr + (i);
	//	printf("[%d] = 0x%X \n", i, *x);
	//}
//	printf("%d ret\n", result);
	

	return 0;
}
