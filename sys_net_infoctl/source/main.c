#include <sysmodule/sysmodule.h>
#include <ppu-lv2.h>
#include <ppu-asm.h>
#include <lv2/sysfs.h>
#include <ppu-types.h>
#include <stdio.h>
#include <net/netctl.h>
#include "net_syscall.h"


int main()
{
	printf("loading net \n");
	sysModuleLoad(SYSMODULE_NET);
	printf("loading netctl \n");
	sysModuleLoad(SYSMODULE_NETCTL);
	
	// Net initializating nonsense
	netInitialize();
	// netCtlInit, just in case.
	netCtlInit();
	//char* funkyaddr = malloc(256);
	
	// Possible cmds, 53, 9, 5
	
	{
		uint8_t buffer[256];
	int cmd = 53;
	printf("calling syscall \n");
	int result = sys_net_infoctl(cmd, &buffer);//dns servers?
	printf("syscall done %x \n", result);

	
	for(int i = 0; i < 256; i++)
	{
		unsigned char* x = buffer + (i);
		printf("[%d] = 0x%X \n", i, *x);
	}
	}
	
	{
	uint8_t buffer[256];
	int cmd = 9;
	printf("calling syscall \n");
	int result = sys_net_infoctl(cmd, &buffer);//dns servers?
	printf("syscall done %x \n", result);

	
	for(int i = 0; i < 256; i++)
	{
		unsigned char* x = buffer + (i);
		printf("[%d] = 0x%X \n", i, *x);
	}
	}
	
	{
	uint8_t buffer[256];
	int cmd = 5;
	printf("calling syscall \n");
	int result = sys_net_infoctl(cmd, &buffer);//dns servers?
	printf("syscall done %x \n", result);

	
	for(int i = 0; i < 256; i++)
	{
		unsigned char* x = buffer + (i);
		printf("[%d] = 0x%X \n", i, *x);
	}
	}
	

	return 0;
}
