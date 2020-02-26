#include <mpd/client.h>
#include <stdlib.h>

#include "log.h"
#include "util.h"

void __attribute__((noreturn))
die(struct mpd_connection *connection, struct mpd_status *status,
    struct mpd_song *song, const char *msg) {
    log_fatal("%s", msg);
    if (connection) {
        mpd_connection_free(connection);
    }
    if (status) {
        mpd_status_free(status);
    }
    if (song) {
        mpd_song_free(song);
    }
    exit(EXIT_FAILURE);
}

void mpd_check_error(struct mpd_connection *connection,
                     struct mpd_status *status, struct mpd_song *song) {
    if (mpd_connection_get_error(connection) != MPD_ERROR_SUCCESS) {
        die(connection, status, song,
            mpd_connection_get_error_message(connection));
    }
}
