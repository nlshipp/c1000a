#ifndef LIBTSL_MSG_H
#define LIBTSL_MSG_H


typedef enum{
        tsl_msg_event_tr69_boot = 1,
        tsl_msg_event_tr69_acs_conf_change,
        tsl_msg_event_tr60_periodic_inform_change,
        tsl_msg_event_tr69_active_notification,
        tsl_msg_event_cfg_save,
} tsl_event_t;

typedef int (*tsl_msg_func)(int event);

typedef struct tsl_msg_s{
        char sock_file[32];
        tsl_msg_func cb_func;
        int master_id;
        int quit;
}tsl_msg_t;

#define TSL_MSG_SOCK_APP_TR69        "/var/sock_tr69"
#define TSL_MSG_SOCK_APP_CFG         "/var/sock_cfg"

/**************************************************************************
 *	[FUNCTION NAME]:
 *	        tsl_msg_client_send
 *
 *	[DESCRIPTION]:
 *	        send a msg to other process who run the tsl_msg_server_service()
 *
 *	[ARGUMENT]:
 *	        char *p_sock_file
 *	        int  event
 *
 *	[RETURN]
 *              >= 0          SUCCESS
 *              <  0          ERROR
 **************************************************************************/
int   tsl_msg_client_send(char *p_sock_file, int event);


/**************************************************************************
 *	[FUNCTION NAME]:
 *	        tsl_msg_server_create
 *
 *	[DESCRIPTION]:
 *	        create msg server
 *
 *	[ARGUMENT]:
 *	        char *p_sock_file
 *	        tsl_msg_func cb_func
 *
 *	[RETURN]
 *              >= 0          SUCCESS
 *              <  0          ERROR
 **************************************************************************/
tsl_msg_t *tsl_msg_server_create(char *p_sock_file, tsl_msg_func cb_func);


/**************************************************************************
 *	[FUNCTION NAME]:
 *	        tsl_msg_server_cleanup
 *
 *	[DESCRIPTION]:
 *	        cleanup msg server
 *
 *	[ARGUMENT]:
 *	        char *p_sock_file
 *	        int  event
 *
 *	[RETURN]
 *              >= 0          SUCCESS
 *              <  0          ERROR
 **************************************************************************/
void tsl_msg_server_cleanup(tsl_msg_t *p_msg);


/**************************************************************************
 *	[FUNCTION NAME]:
 *	        tsl_msg_server_service
 *
 *	[DESCRIPTION]:
 *	        run the msg service
 *
 *	[ARGUMENT]:
 *	        char *p_sock_file
 *	        int  event
 *
 *	[RETURN]
 *              >= 0          SUCCESS
 *              <  0          ERROR
 **************************************************************************/
int   tsl_msg_server_service(tsl_msg_t *p_msg);

#endif
