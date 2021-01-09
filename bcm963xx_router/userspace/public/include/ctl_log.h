#ifndef _CTL_LOG_H
#define _CTL_LOG_H

#include <sys/time.h>
#include <time.h>



extern int CTL_LOG_LEVEL;

#if 0
#define SHOWDATE()	do { \
	time_t the_time; \
	tm *tm_ptr;  \
	(void) time(&the_time); \
	tm_ptr = localtime(&the_time); \
	fprintf( stdout, "[%02d:%02d:%02d] ", \
			tm_ptr->tm_hour,tm_ptr->tm_min,tm_ptr->tm_sec ); \
} while(0)
#else
#define SHOWDATE()	
#endif

#if defined( _BHR2 )
#define ctllog_debug(arg...)    do { \
					SHOWDATE(); \
					fprintf(stdout,"DEBUG %s:%d ",__FILE__,__LINE__);\
					fprintf(stdout,##arg);\
					fprintf(stdout,"\n" );\
				} while(0)

#define ctllog_notice(arg...)   do { \
					SHOWDATE(); \
					fprintf(stdout,"NOTICE %s:%d ",__FILE__,__LINE__);\
					fprintf(stdout,##arg);\
					fprintf(stdout,"\n" );\
				} while(0)

#define ctllog_warn(arg...)	    do { \
					SHOWDATE(); \
					fprintf(stdout,"WARNING %s:%d ",__FILE__,__LINE__);\
					fprintf(stdout,##arg);\
					fprintf(stdout,"\n" );\
				} while(0)
				
#define ctllog_error(arg...)    do { \
					SHOWDATE(); \
					fprintf(stdout,"ERROR %s:%d ",__FILE__,__LINE__);\
					fprintf(stdout,##arg);\
					fprintf(stdout,"\n" );\
				} while(0)

/* for BHR1 */
#elif defined( SUPPORT_BHR1 )

#define RG_OS_CONSOLE "/dev/console"

#define ctllog_debug(arg...)    do { \
    FILE* fp = fopen(RG_OS_CONSOLE, "w"); \
    if (!fp) return (-1); \
    fprintf(stdout,"DEBUG %s:%d ",__FILE__,__LINE__);\
    fprintf(stdout,##arg);\
    fprintf(stdout,"\n" );\
    fclose(fp);\
} while(0)

#define ctllog_notice(arg...)    do { \
    FILE* fp = fopen(RG_OS_CONSOLE, "w"); \
    if (!fp) return (-1); \
    fprintf(stdout,"NOTICE %s:%d ",__FILE__,__LINE__);\
    fprintf(stdout,##arg);\
    fprintf(stdout,"\n" );\
    fclose(fp);\
} while(0)

#define ctllog_warn(arg...)    do { \
    FILE* fp = fopen(RG_OS_CONSOLE, "w"); \
    if (!fp) return (-1); \
    fprintf(stdout,"WARNING %s:%d ",__FILE__,__LINE__);\
    fprintf(stdout,##arg);\
    fprintf(stdout,"\n" );\
    fclose(fp);\
} while(0)

#define ctllog_error(arg...)    do { \
    FILE* fp = fopen(RG_OS_CONSOLE, "w"); \
    if (!fp) return (-1); \
    fprintf(stdout,"ERROR %s:%d ",__FILE__,__LINE__);\
    fprintf(stdout,##arg);\
    fprintf(stdout,"\n" );\
    fclose(fp);\
} while(0)

#elif defined(SUPPORT_PK5000)

#include <fcntl.h>

#define LED_KPRINTF 8
#define kprintf(arg...) do { \
	    char tmp_text[51]={0}; int fp=0;\
	    fp = open("/dev/led", O_RDWR);\
	    if (fp) {\
			        snprintf(tmp_text, sizeof(tmp_text)-1, ##arg); \
			        ioctl(fp,LED_KPRINTF,&tmp_text);\
			        close(fp);  } \
} while(0)


#define ctllog_debug     kprintf
#define ctllog_error     kprintf

#define ctllog_notice    kprintf
#define ctllog_warn(arg...) 

#else
enum CLOG_LEVEL{
    CLOG_LEVEL_NULL,
    CLOG_LEVEL_ERR,
    CLOG_LEVEL_WARN,
    CLOG_LEVEL_NOTICE,
    CLOG_LEVEL_DEBUG
};

#define ctllog_debug(arg...)	do { \
                    if(CTL_LOG_LEVEL<CLOG_LEVEL_DEBUG)\
                        break;\
					SHOWDATE(); \
					fprintf(stdout,"DEBUG %s:%d ",__FILE__,__LINE__);\
					fprintf(stdout,##arg);\
					fprintf(stdout,"\n" );\
				} while(0)

#define ctllog_notice(arg...)	do { \
                    if(CTL_LOG_LEVEL<CLOG_LEVEL_NOTICE)\
                        break;\
					SHOWDATE(); \
					fprintf(stdout,"NOTICE %s:%d ",__FILE__,__LINE__);\
					fprintf(stdout,##arg);\
					fprintf(stdout,"\n" );\
				} while(0)


#define ctllog_warn(arg...)	do { \
                    if(CTL_LOG_LEVEL<CLOG_LEVEL_WARN)\
                        break;\
					SHOWDATE(); \
					fprintf(stdout,"WARNING %s:%d ",__FILE__,__LINE__);\
					fprintf(stdout,##arg);\
					fprintf(stdout,"\n" );\
				} while(0)

#define ctllog_error(arg...)	do { \
                    if(CTL_LOG_LEVEL<CLOG_LEVEL_ERR)\
                        break;\
					SHOWDATE(); \
					fprintf(stdout,"ERROR %s:%d ",__FILE__,__LINE__);\
					fprintf(stdout,##arg);\
					fprintf(stdout,"\n" );\
				} while(0)
#endif

#ifndef SUPPORT_PK5000
#define V6_DEBUG	
#else
#define V6_DEBUG(args...)	do { \
								kprintf("%s,%d:",__func__,__LINE__);\
								kprintf(args); \
							}while(0)
#endif


#define ctllog_verbose		printf

#endif
