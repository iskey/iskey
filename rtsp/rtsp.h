#ifndef __RTSP_SERVER__H
#define __RTSP_SERVER__H

#include <glib.h>
#include <ev.h>
#include <stdio.h>
#include <stdbool.h>
#include "xlog.h"

typedef struct rtsp_socket_listener{
	int fd;
	ev_io io;
}rtsp_socket_listener;

extern void rtsp_client_incoming_cb(struct ev_loop *loop, ev_io *w, int revents);

#endif //End of __RTSP_SERVER__H
