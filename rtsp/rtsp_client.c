#include "rtsp.h"
#include <netdb.h>

void rtsp_client_incoming_cb(struct ev_loop *loop, ev_io *w, int revents)
{
	xlog(LOG_ERR, "incoming.");
	int client_sd= -1;
	rtsp_socket_listener *listen= w->data;

	struct sockaddr_storage peer, bound;
	socklen_t peer_len= sizeof(struct sockaddr_storage), bound_len= sizeof(struct sockaddr_storage);

	if((client_sd= accept(listen->fd, (struct sockaddr*)&peer, &peer_len))< 0){
		xlog(LOG_ERR, "accept failed.")
		return;
	}

	if(getsockname(client_sd, (struct sockaddr*)&bound, &bound_len)< 0){
		xlog(LOG_ERR, "get sockname error");
		goto err;
	}

	//ev_io_stop(loop, w);

	return;
err:
	close(client_sd);
	return;
}