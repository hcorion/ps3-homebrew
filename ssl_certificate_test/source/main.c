// Certificate test

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h> 

#include <net/net.h>
#include <http/http.h>
#include <http/https.h>
#include <ssl/ssl.h>

#include <sysmodule/sysmodule.h>

#define HTTP_POOL_SIZE      (64  * 1024)
#define SSL_POOL_SIZE       (256 * 1024)


uint8_t httpPool[HTTP_POOL_SIZE];
uint8_t sslPool[SSL_POOL_SIZE];

int loadCert(size_t size, unsigned long long flag)
{
	char* buf = (char*)malloc(size);
	int ret = sslCertificateLoader(flag, buf, size, NULL);
	if (ret != 0)
	{
		printf("sslCertificateLoader failed: %d\n", ret);
	}
	char word[size];
	strcpy(word, buf);
	printf("%s\n", word);
	printf("-----------next-----------\n");
	free(buf);
	return ret;
}

int main(int argc,char *argv[])
{
	int ret;
	
	printf("I have no idea what I'm doing...\n");
	sysModuleLoad(SYSMODULE_NET);
	sysModuleLoad(SYSMODULE_SSL);
	sysModuleLoad(SYSMODULE_HTTP);
	sysModuleLoad(SYSMODULE_HTTPS);
	
	ret = netInitialize();
	if (ret < 0) {
		printf("sys_net_initialize_network() failed (%d)\n", ret);
	}
	
	// Initialization
	// Init HTTP
	ret = httpInit(httpPool, HTTP_POOL_SIZE);
	if (ret < 0)
	{
		printf("unable to start httpInit... (0x%x)\n", ret);
	}
	//ret = cellHttpInitCookie();
	
	//Init SSL
	ret = sslInit(sslPool, SSL_POOL_SIZE);
	if (ret < 0)
	{
		printf("unable to start SslInit... (0x%x)\n", ret);
	}
	
	// Time for certificates
	//117440519
	// Motorstorm uses 117440519
	printf("CELL_SSL_LOAD_CERT_NORMAL: %llu\n", CELL_SSL_LOAD_CERT_NORMAL);
	printf("CELL_SSL_LOAD_CERT_ALL: %llu\n", CELL_SSL_LOAD_CERT_ALL);
	
	httpsData *caList = NULL;
	size_t size = 0;
	//char *buf = NULL;
	caList = (httpsData *)malloc(sizeof(httpsData)*2);
	
	
	
//	if (NULL == buf)
//	{
//		printf("can't malloc cert buffer\n");
//	}
	
	ret = sslCertificateLoader(CELL_SSL_LOAD_CERT_NORMAL, NULL, 0, &size);
	printf("ret: %d\n", ret);
	printf("size: %u\n", size);
	//loadCert(size, CELL_SSL_LOAD_CERT_SCE01);
	//loadCert(size, CELL_SSL_LOAD_CERT_SCE02);
	//loadCert(size, CELL_SSL_LOAD_CERT_SCE03);
	//loadCert(size, CELL_SSL_LOAD_CERT_SCE04);
	//loadCert(size, CELL_SSL_LOAD_CERT_SCE05);
	loadCert(size, CELL_SSL_LOAD_CERT_BALTIMORE_CT);
	loadCert(size, CELL_SSL_LOAD_CERT_CLASS1_PCA_G2_V2);
	loadCert(size, CELL_SSL_LOAD_CERT_CLASS1_PCA_G3_V2);
	loadCert(size, CELL_SSL_LOAD_CERT_CLASS1_PCA_SS_V4);
	loadCert(size, CELL_SSL_LOAD_CERT_CLASS2_PCA_G2_V2);
	loadCert(size, CELL_SSL_LOAD_CERT_CLASS2_PCA_G3_V2);
	loadCert(size, CELL_SSL_LOAD_CERT_CLASS2_PCA_SS_V4);
	loadCert(size, CELL_SSL_LOAD_CERT_CLASS3_PCA_G2_V2);
	loadCert(size, CELL_SSL_LOAD_CERT_CLASS3_PCA_G3_V2);
	loadCert(size, CELL_SSL_LOAD_CERT_CLASS3_PCA_SS_V4);
	loadCert(size, CELL_SSL_LOAD_CERT_CLASS4_PCA_G2_V2);
	loadCert(size, CELL_SSL_LOAD_CERT_CLASS4_PCA_G3_V2);
	loadCert(size, CELL_SSL_LOAD_CERT_ENTRUST_NET_SS_CA);
	loadCert(size, CELL_SSL_LOAD_CERT_EQUIFAX_SEC_CA);
	loadCert(size, CELL_SSL_LOAD_CERT_EQUIFAX_SEC_EBUS1);
	loadCert(size, CELL_SSL_LOAD_CERT_GEOTRUST_GCA);
	loadCert(size, CELL_SSL_LOAD_CERT_GLOBALSIGN_RCA);
	loadCert(size, CELL_SSL_LOAD_CERT_GTE_CT_G_RCA);
	loadCert(size, CELL_SSL_LOAD_CERT_GTE_CT_ROOT);
	loadCert(size, CELL_SSL_LOAD_CERT_RSA1024_V1);
	loadCert(size, CELL_SSL_LOAD_CERT_RSA2048_V3);
	loadCert(size, CELL_SSL_LOAD_CERT_RSA_SECURE_SERVER);
	loadCert(size, CELL_SSL_LOAD_CERT_THAWTE_PREM_SCA);
	loadCert(size, CELL_SSL_LOAD_CERT_THAWTE_SCA );
	loadCert(size, CELL_SSL_LOAD_CERT_VALICERT_CLASS2);
	loadCert(size, CELL_SSL_LOAD_CERT_VERISIGN_TSA_CA);
	loadCert(size, CELL_SSL_LOAD_CERT_AAA_CERT_SERVICES);
	loadCert(size, CELL_SSL_LOAD_CERT_ADDTRUST_EXT_CA);
	loadCert(size, CELL_SSL_LOAD_CERT_UTN_USERFIRST_HW);
	loadCert(size, CELL_SSL_LOAD_CERT_EQUIFAX_SEC_G_EBUS1);
	loadCert(size, CELL_SSL_LOAD_CERT_CLASS3_PCA_G5);
	loadCert(size, CELL_SSL_LOAD_CERT_SHA256);
	
	//Invalid cert tests
	
	ret = loadCert(size, 0);
	void* buf = malloc(size);
	ret = sslCertificateLoader(0, buf, size, NULL);
	printf("loadCert 0: %d\n", ret);
	void* buf2 = malloc(size);
	ret = sslCertificateLoader(0x0400000000000000ULL, buf2, size, NULL);
	printf("loadCert 0x0400000000000000: %d\n", ret);
	void* buf3 = malloc(size);
	ret = sslCertificateLoader(0x0800000000000000ULL, buf3, size, NULL);
	printf("loadCert 0x0800000000000000: %d\n", ret);
	ret = sslCertificateLoader(CELL_SSL_LOAD_CERT_ALL << 1, NULL, 0, &size);
	printf("loadCert CELL_SSL_LOAD_CERT_ALL << 1: %d\n", ret);

	return 0;
}
