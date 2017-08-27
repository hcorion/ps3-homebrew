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

//typedef struct httpUri httpUri ;

int main(int argc,char *argv[])
{
	int ret;
	
	printf("I have no idea what I'm doing...\n");
	sysModuleLoad(SYSMODULE_HTTP_UTIL);
	char* string;
	uint32_t poolSize = 0;
	httpUri uri;
	string = "https://John:Dow@github.com:80/corporateshark/LUrlParser";
	printf("Before httpUtilParseUri\n");
	ret = httpUtilParseUri(NULL, string, NULL, 0, &poolSize);
	if (ret < 0)
		printf("Error while parsing URI, %s: %d\n",string, ret);
	void* uriPool = malloc(poolSize);
	printf("After httpUtilParseUri\n");
	ret = httpUtilParseUri(&uri, string, uriPool, poolSize, NULL);
	if (ret < 0)
		printf("Error while parsing URI, %s: %d\n",string, ret);
	//printf("test: %s",(char*)uriPool);
	printf("scheme: %s\n",uri.scheme);
	printf("hostname: %s\n",uri.hostname);
	printf("username: %s\n",uri.username);
	printf("password: %s\n",uri.password);
	printf("path: %s\n",uri.path);
	printf("port: %d\n",uri.port);
	free(uriPool);
	return 0;
}
