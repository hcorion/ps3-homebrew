// HttpUtilParseUri test

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h> 

#include <http/util.h>

#include <sysmodule/sysmodule.h>

#define HTTP_POOL_SIZE      (64  * 1024)
#define SSL_POOL_SIZE       (256 * 1024)


uint8_t httpPool[HTTP_POOL_SIZE];
uint8_t sslPool[SSL_POOL_SIZE];

int main(int argc,char *argv[])
{
	int ret;
	
	printf("I have no idea what I'm doing...\n");
	sysModuleLoad(SYSMODULE_HTTP_UTIL);
	httpUtilParseUri();
	char* string;
	size_t poolSize = 0;
	
	string = "https://github.com";
	ret = httpUtilParseUri(NULL, string, NULL, 0, &poolSize);
	if (ret < 0)
		printf("Error while parsing URI, %s: %d",string, ret);
	uriPool = malloc(poolSize);
	ret = httpUtilParseUri(&uri, string, uriPool, poolSize, NULL);
	free(uriPool);
	if (ret < 0)
		printf("Error while parsing URI, %s: %d",string, ret);
}
