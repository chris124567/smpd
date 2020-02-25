#include <mpd/client.h>

#include "constants.h"
#include "status.h"
#include "util.h"

struct mpd_status *initialize_status(struct mpd_connection *connection) {
    struct mpd_status *status;

    status = NULL;
    mpd_send_status(connection);
    status = mpd_recv_status(connection);
    if (status == NULL) {
        die(connection, RECV_STATUS_FAIL);
    }
    mpd_check_error(connection);
    return status;
}
