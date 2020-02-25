#include <mpd/client.h>
#include <stdlib.h>

#include "log.h"
#include "util.h"

void __attribute__((noreturn))
die(struct mpd_connection *connection, const char *msg) {
    log_fatal("%s", msg);
    if (connection != NULL) {
        mpd_connection_free(connection);
    }
    exit(EXIT_FAILURE);
}

void mpd_check_error(struct mpd_connection *connection) {
    if (mpd_connection_get_error(connection) != MPD_ERROR_SUCCESS) {
        die(connection, mpd_connection_get_error_message(connection));
    }
}