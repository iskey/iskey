#ifndef __RTSP_SERVER__H
#define __RTSP_SERVER__H

#include <glib.h>
#include <ev.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct rtsp_socket_listener{
	int fd;
	ev_io io;
}rtsp_socket_listener;

#endif //End of __RTSP_SERVER__H
