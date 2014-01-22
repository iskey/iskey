#include "rtsp.h"
#include <netdb.h>

/**
 * @brief Allocate and initialise a new RTSP session object
 *
 * @param rtsp The RTSP client for which to allocate the session
 *
 * @return A pointer to a newly allocated RTSP session object
 *
 * @see rtsp_session_free();
 */
RTSP_session *rtsp_session_new(RTSP_Client *rtsp)
{
    RTSP_session *new = rtsp->session = g_slice_new0(RTSP_session);

    new->session_id = g_strdup_printf("%08x%08x",
                                      g_random_int(),
                                      g_random_int());
    new->play_requests = g_queue_new();

    return new;
}

void rtsp_session_free(RTSP_session *session)
{

}
