#include <sysmodule/sysmodule.h>
#include <ppu-lv2.h>
#include <ppu-asm.h>
#include <ppu-types.h>
#include <stdio.h>
#include <sys/thread.h>
#include <time.h>
#include <sys/systime.h>

struct timespec diff(struct timespec start, struct timespec end);

static void thread_start(void *arg)
{
    //*arg = 0xBEEF;
    u32* test = arg;
    *test = 0xBEEF;
	sysThreadExit(0);
}

int main()
{
    for (int i = 0; i < 10; i++)
    {
        u64 retval;
        s32 ret;
        sys_ppu_thread_t id;
        u64 prio = 1500;
        size_t stacksize = 0x1000;
        char *threadname = "myThread";
        volatile u32 threadarg = 0x1337;
        
        struct timespec start, end;
        
        sysGetCurrentTime(&start.tv_sec, &start.tv_nsec);
        ret = sysThreadCreate(&id,thread_start,(void*)&threadarg,prio,stacksize,THREAD_JOINABLE,threadname);
        while(threadarg != 0xBEEF) {}
        sysGetCurrentTime(&end.tv_sec, &end.tv_nsec);
        printf("It took roughly %ld seconds and %ld nanoseconds\n", diff(start, end).tv_sec, diff(start, end).tv_nsec);
        printf("Or, %.6f milliseconds\n", ((float)diff(start, end).tv_nsec) * 0.000001f);
        
        ret = sysThreadJoin(id,&retval);
    }
    
    
	printf("Exiting thread test\n");
	return 0;
}

struct timespec diff(struct timespec start, struct timespec end)
{
	struct timespec temp;
	if ((end.tv_nsec-start.tv_nsec)<0) {
		temp.tv_sec = end.tv_sec-start.tv_sec-1;
		temp.tv_nsec = 1000000000+end.tv_nsec-start.tv_nsec;
	} else {
		temp.tv_sec = end.tv_sec-start.tv_sec;
		temp.tv_nsec = end.tv_nsec-start.tv_nsec;
	}
	return temp;
}
