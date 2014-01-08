#include <dbus/dbus.h>
#include <sys/select.h>
#include <unistd.h>
#include <stdio.h>


#define TEST_SERVICE            "com.woojoy.test_dbus"
#define TEST_PATH               "/com/woojoy/test_dbus"
#define MATCH_RULE              "type='signal'"

/*below is the signal filter to receive the others signal,ofcourse you should change the MATCH_RULE,so filter the signals you donot care*/
static DBusHandlerResult message_filter(DBusConnection *connection, DBusMessage *message, void *data)
{
                const char *interface = dbus_message_get_interface(message);
                printf("in test_dbus the interface is %s \n",interface);
                const char *member= dbus_message_get_member(message);
                printf("in test_dbus the member is %s \n",member);

                return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
}

/*below is the message handler,here you should accept the others remote method invoke I just printf some info*/
DBusHandlerResult message_handler(DBusConnection *connection,
                                                                  DBusMessage *message,
                                                                                 void *user_data)
{
                printf("this is test_dbus message_handler\n");
                return (DBUS_HANDLER_RESULT_HANDLED);
}
/*here is to register to dbus server,so that it can send the info to us*/
static void
connect_hook(DBusConnection *connection, void *data)
{
                DBusError error;
                DBusObjectPathVTable vtable = { .message_function = message_handler, };
                dbus_error_init(&error);
                if (!dbus_bus_request_name(connection, TEST_SERVICE, 0, &error)) {
                                printf("dbus_bus_request_name error\n");
                                return;
                }
                dbus_bus_add_match(connection, MATCH_RULE, &error);
                if (dbus_error_is_set(&error)) {
                                printf("after dbus_bus_add_match error\n");
                                return;
                }

                if (!dbus_connection_register_object_path(connection, TEST_PATH, &vtable, NULL)) {
                                printf("dbus_connection_register_object_path error\n");
                                return;
                }

                dbus_error_free(&error);
                return;
}


int main(int argc,char **argv)
{
                DBusError derror;
                dbus_error_init(&derror);
                DBusConnection *dbus_connection = dbus_bus_get(DBUS_BUS_SYSTEM, &derror);
                if (dbus_connection == NULL) {
                                fprintf(stderr,"System DBus connection failed: %s", derror.message);
                                dbus_error_free(&derror);
                                return -1;
                }

                /*above is to get the dbusconnection,which actually is a socket fd*/
                connect_hook(dbus_connection,NULL);
                 /*above is to register to dbus server*/
                if (!dbus_connection_add_filter(dbus_connection, message_filter, NULL, NULL)) {
                                printf("after dbus_connection_add_filter error\n");
                                return -1;
                }
                  /*here is add some filter which will get the message before message_handler*/
                int fd=-1;
                dbus_connection_get_unix_fd(dbus_connection, &fd);
                printf("the fd after dbus_connection_get_unix_fd is %d\n",fd);
                 /*below is the main loop to get from the dbus server,and then dispatch the info */
                while(1){
                                fd_set rd_fds;
                                FD_ZERO( &rd_fds );
                                FD_SET( fd, &rd_fds );
                                int result=select(fd+1, &rd_fds, NULL, NULL, NULL);
                                if(result < 0){
                                                printf("select error\n");
                                                break;
                                }
                                if (FD_ISSET (fd, &rd_fds)){
                                                printf("there is something to read\n");
                                                do {
                                                                dbus_connection_read_write_dispatch(dbus_connection, 0);
                                                } while (dbus_connection_get_dispatch_status(dbus_connection) == DBUS_DISPATCH_DATA_REMAINS);
                                                continue;
                                }
                }

                return 0;
}