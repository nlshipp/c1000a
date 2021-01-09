#ifndef TSL_MSG_H
#define TSL_MSG_H

#include "tsl_common.h"
#include "tsl_list.h"

typedef enum{
        tsl_msg_event_tr69_boot = 1,
        tsl_msg_event_tr69_acs_conf_change,
        tsl_msg_event_tr60_periodic_inform_change,
        tsl_msg_event_tr69_active_notification,
        tsl_msg_event_cfg_save,
} tsl_event_t;

typedef tsl_rv_t (*tsl_msg_func)(tsl_int_t event);

typedef struct tsl_msg_s{
        tsl_char_t sock_file[32];
        tsl_msg_func cb_func;
        tsl_int_t master_id;
        tsl_int_t quit;
}tsl_msg_t;

#define TSL_MSG_SOCK_APP_TR69        "/var/sock_tr69"
#define TSL_MSG_SOCK_APP_CFG         "/var/sock_cfg"

tsl_rv_t   tsl_msg_client_send(tsl_char_t *p_sock_file, tsl_int_t event);
tsl_msg_t *tsl_msg_server_create(tsl_char_t *p_sock_file, tsl_msg_func cb_func);
tsl_void_t tsl_msg_server_cleanup(tsl_msg_t *p_msg);
tsl_rv_t   tsl_msg_server_service(tsl_msg_t *p_msg);

#endif
