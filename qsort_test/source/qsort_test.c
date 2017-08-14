 
// This sample application will connect to a specified IP using the PS3's
// network and send a small message. It will try sending it with both
// TCP and UDP.

#include <net/net.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <malloc.h>
#include <string.h>
#include <errno.h>
#include <sys/time.h>
#include <time.h>
#include <ppu-asm.h>

#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int compare (const void* a, const void* b)
{
	printf("a: %d b: %d \n", *(unsigned int*)a, *(unsigned int*)b);
  return ( *(unsigned int*)a - *(unsigned int*)b );
}

int main(int argc, const char* argv[])
{
	printf("I have no idea what I'm doing...\n");
	unsigned int arr[] = {4, 3, 5, 2, 1, 3, 2, 3};
	printf("dat: %u\n", *(unsigned int*)arr);
	printf("base: 0x%x\n", arr);
	printf("compare: 0x%x\n", compare);
	unsigned int da = 3;
	unsigned int dr = 5;
	printf("compare: 0x%d\n", compare((void*)&da, (void*)&dr));
	size_t n = sizeof( arr ) / sizeof( *arr );
	sysQsort(arr, n, sizeof(unsigned int), compare);
	int x;
	for (x=0; x<n; x++)
     printf ("%d \n",arr[x]);
	
	return 0;
}


