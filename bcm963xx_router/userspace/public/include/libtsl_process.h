#ifndef LIBTSL_PROCESS_H
#define LIBTSL_PROCESS_H

struct tr69_process_s{
        char path[32];
        char argv[64];
};

#define APP_TR69 "./tr69"
#define APP_DATA_CENTER "./data_center"

#if 0
struct tr69_process_s tr69_process_tb[]={
	{
                APP_TR69,
                APP_TR69
	},
        {
                APP_DATA_CENTER,
                APP_DATA_CENTER
	},
};
#endif

/**************************************************************************
 *	[FUNCTION NAME]:
 *	        tsl_process_start
 *
 *	[DESCRIPTION]:
 *	        start a new process        
 *
 *	[ARGUMENT]:
 *	        char *p_path
 *	        char *p_argv
 *
 *	[RETURN]
 *              >= 0          SUCCESS
 *              <  0          ERROR
 **************************************************************************/
int tsl_process_start(char *p_path, char *p_argv);


/**************************************************************************
 *	[FUNCTION NAME]:
 *	        tsl_process_stop
 *
 *	[DESCRIPTION]:
 *	        stop the process
 *
 *	[ARGUMENT]:
 *	        char *p_path
 *
 *	[RETURN]
 *              >= 0          SUCCESS
 *              <  0          ERROR
 **************************************************************************/
int tsl_process_stop(char *p_path);


/**************************************************************************
 *	[FUNCTION NAME]:
 *	        tsl_process_restart
 *
 *	[DESCRIPTION]:
 *	        restart the process        
 *
 *	[ARGUMENT]:
 *	        char *p_path
 *
 *	[RETURN]
 *              >= 0          SUCCESS
 *              <  0          ERROR
 **************************************************************************/
int tsl_process_restart(char *p_path);


/**************************************************************************
 *	[FUNCTION NAME]:
 *	        tsl_process_init
 *
 *	[DESCRIPTION]:
 *	        initinate the process control dameon
 *
 *	[ARGUMENT]:
 *	        struct tr69_process_s *p_process_tb
 *	        int numb
 *
 *	[RETURN]
 *              >= 0          SUCCESS
 *              <  0          ERROR
 **************************************************************************/
int tsl_process_init(struct tr69_process_s *p_process_tb, int numb);


/**************************************************************************
 *	[FUNCTION NAME]:
 *	        tsl_process_start
 *
 *	[DESCRIPTION]:
 *	        cleanup the process control daemon 
 *
 *	[ARGUMENT]:
 *	        
 *
 *	[RETURN]
 *              >= 0          SUCCESS
 *              <  0          ERROR
 **************************************************************************/
int tsl_process_cleanup();


#endif
