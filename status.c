#include "status.h"

#include <mpd/client.h>

#include "constants.h"
#include "util.h"

struct mpd_status *initialize_status(struct mpd_connection *connection) {
    struct mpd_status *status;

    status = NULL;
    mpd_send_status(connection);
    mpd_check_error(connection, status, NULL);
    status = mpd_recv_status(connection);
    if (status == NULL) {
        die(connection, NULL, NULL, RECV_STATUS_FAIL);
    }
    mpd_check_error(connection, status, NULL);
    return status;
}
