// Certificate test

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h> 
#include <inttypes.h>

#include <net/net.h>
#include <http/http.h>
#include <http/https.h>
#include <ssl/ssl.h>

#include <sysmodule/sysmodule.h>
#include <lv2/sysfs.h>

#define HTTP_POOL_SIZE      (64  * 1024)
#define SSL_POOL_SIZE       (256 * 1024)


uint8_t httpPool[HTTP_POOL_SIZE];
uint8_t sslPool[SSL_POOL_SIZE];
#define MOUNT_POINT "/host_root/tmp/"
#define CELL_FS_DEFAULT_CREATE_MODE_1 0000700

int loadCert(uint32_t size, uint64_t flag)
{
	char* buf = (char*)malloc(size+50);
	memset(buf, '\1', size+50);
	int ret = sslCertificateLoader(flag, buf, (uint32_t)size, NULL);
	if (ret != 0)
	{
		printf("sslCertificateLoader failed: %d\n", ret);
	}
	char word[size];
	strcpy(word, buf);
	
	// Testing
	for (int i = 0; i < size+50; i++)
	{
		if (buf[i] == '\1')
		{
			printf("End of array is: %d\n", i);
			break;
		}
	}
	
	//Write to file.
	
	//if (!isMounted(MOUNT_POINT)) // Not sure what the PSL1GHT call is for this.
	if (false)
	{
        printf("Woops, %s isn't mounted", MOUNT_POINT);
    }
    sysFsMkdir(MOUNT_POINT"certtest", CELL_FS_DEFAULT_CREATE_MODE_1);
	uint64_t fd = 0;
	sysFsOpen(MOUNT_POINT"certtest/cert.txt",
                     SYS_O_RDWR|SYS_O_CREAT, &fd, NULL, 0);
	uint64_t sw = 0;
	sysFsWrite(fd, (const void *)word, (uint64_t)size, &sw);
	//sysFsStat(MOUNT_POINT"/sample/cert.txt");
    //sysFsFstat(fd);
	
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
	sysModuleLoad(SYSMODULE_LV2DBG);
	sysModuleLoad(SYSMODULE_FS);
	
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
	uint32_t size = 0;
	
	ret = sslCertificateLoader(562948804079679, NULL, 0, &size);
	printf("ret: %d\n", ret);
	printf("size: %"PRIu32"\n", size);
	//printf("sizeof(uint32_t): %"PRIu32"\n", sizeof(uint32_t));
	//printf("sizeof(size_t): %"PRIu32"\n", sizeof(size_t));
	
	loadCert(size, 562948804079679);
	
	
	return 0;
	loadCert(size, CELL_SSL_LOAD_CERT_SCE02);
	loadCert(size, CELL_SSL_LOAD_CERT_SCE03);
	loadCert(size, CELL_SSL_LOAD_CERT_SCE04);
	loadCert(size, CELL_SSL_LOAD_CERT_SCE05);
	loadCert(size, CELL_SSL_LOAD_CERT_NORMAL);
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
