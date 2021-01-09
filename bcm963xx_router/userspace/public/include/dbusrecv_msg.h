#ifndef __DBUSRECV_MSG_H__
#define __DBUSRECV_MSG_H__

#include <dbus/dbus.h>
#include <dbus/dbus-mainloop.h>

typedef DBusHandlerResult (*callbk_filter_func)(DBusConnection *connection, DBusMessage *message, void *user_data);

typedef struct _dbusrecv_cfg
{    
    char *myname;    
}dbusrecv_cfg_st, *pdbusrecv_cfg_st;

typedef struct _dbusrecv_hdl
{
    dbusrecv_cfg_st dbusrecv_cfg;
    DBusError error;
    DBusLoop *dbusloop;
    DBusConnection *connection;        
    callbk_filter_func filter_func;
    int is_addfilter;
}dbusrecv_hdl_st, *pdbusrecv_hdl_st;

dbusrecv_hdl_st *dbusrecv_init(char *myname, callbk_filter_func filter_func);
int dbusrecv_addrules(dbusrecv_hdl_st *p_dbusrecv_hdl, char *interface, char *method);
int dbusrecv_listen(dbusrecv_hdl_st *p_dbusrecv_hdl);
int dbusrecv_getmsg(DBusMessage *message, char **pp_buf, int *p_length);
int dbusrecv_uninit(dbusrecv_hdl_st *p_dbusrecv_hdl);

#endif
