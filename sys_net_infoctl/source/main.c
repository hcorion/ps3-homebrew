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
	unsigned char buffder[256];
	netCtlGetInfo(0x10, buffder);
	// Possible cmds, 53, 9, 5
	
	{
	unsigned int* buffer1 = malloc(256);
	unsigned char* test = malloc(20);
	buffer1[1] = test;
	test[0] = 0x25;
	test[1] = 0x14;
	test[2] = 0xE7;
	test[3] = 0xD8;
	test[7] = 1;
	int cmd = 53;
	printf("calling syscall \n");
	int result = sys_net_infoctl(cmd, &buffer1);//dns servers?
	printf("syscall done %x \n", result);

	
	for(int i = 0; i < 256; i++)
	{
		unsigned char* x = ((unsigned char*)buffer1) + (i);
		printf("[%d] = 0x%X \n", i, *x);
	}
	}
	
	{
	unsigned char* buffer2 = malloc(256);
	int cmd = 9;
	printf("calling syscall \n");
	int result = sys_net_infoctl(cmd, &buffer2);//dns servers?
	printf("syscall done %x \n", result);

	
	for(int i = 0; i < 256; i++)
	{
		unsigned char* x = buffer2 + (i);
		printf("[%d] = 0x%X \n", i, *x);
	}
	}
	
	{
	unsigned char* buffer3 = malloc(256);
	int cmd = 5;
	printf("calling syscall \n");
	int result = sys_net_infoctl(cmd, &buffer3);//dns servers?
	printf("syscall done %x \n", result);

	
	for(int i = 0; i < 256; i++)
	{
		unsigned char* x = buffer3 + (i);
		printf("[%d] = 0x%X \n", i, *x);
	}
	}
	

	return 0;
}
