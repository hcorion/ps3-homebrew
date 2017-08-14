 
// This sample application will connect to a specified IP using the PS3's
// network and send a small message. It will try sending it with both
// TCP and UDP.

#include <net/net.h>

#include <stdio.h>
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


int main(int argc, const char* argv[])
{
	printf("I have no idea what I'm doing...\n");
	printf("Initializing network... %d\n", netInitialize());
	int s = socket(2, 6, 0);
	int x = setsockopt(0, 65535, 4096, 0xd00209e0, 4);
	netClose(0);
	//timeout tv_sec: 0, timeout tv_usec: 2147746548
	//struct timeval timeout = {0, 2147746548};
	struct timeval timeout = {2, 10};
	
	time_t startRawTime, endRawTime;
	printf("before select\n");
	time ( &startRawTime );
	int ret = select(0, NULL, NULL, NULL, &timeout);
	time ( &endRawTime );
	printf("After select\n");

	printf("error: %#x\n", errno);
	printf ("%.0fs\n", difftime (endRawTime, startRawTime));
	printf("x: %d socket: %d ret: %d\n", x, s, net_errno);
	netDeinitialize();
	return 0;
}
