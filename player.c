#include <mpd/client.h>

#include "constants.h"
#include "log.h"
#include "player.h"
#include "status.h"
#include "util.h"

void toggle_repeat_mode(struct mpd_connection *connection) {
    bool old_status;
    struct mpd_status *status;

    status = initialize_status(connection);
    old_status = mpd_status_get_repeat(status);
    mpd_check_error(connection, status, NULL);
    mpd_run_repeat(connection,
                   !old_status); /* do the opposite of whatever we have */
    mpd_check_error(connection, status, NULL);
    mpd_status_free(status);

#ifdef DEBUG
    log_info("Toggled repeat mode from %d to %d", old_status, !old_status);
#endif
}

void toggle_playing(struct mpd_connection *connection) {
    enum mpd_state playing_state;
    struct mpd_status *status;

    status = initialize_status(connection);
    playing_state = mpd_status_get_state(status);
    mpd_check_error(connection, status, NULL);
    if (playing_state == MPD_STATE_PLAY) {
        mpd_run_pause(connection, true);
    } else {
        mpd_run_play(connection);
    }
    mpd_check_error(connection, status, NULL);
    mpd_status_free(status);

#ifdef DEBUG
    log_info("Toggled playing state");
#endif
}

void song_set_position(struct mpd_connection *connection, int position) {
    if (position < 0) {
        die(connection, NULL, NULL, REMOVE_NEGATIVE_FAIL);
    }

    mpd_send_seek_current(connection, (float)position,
                          false); /* safe, we check if negative above */
    mpd_check_error(connection, NULL, NULL);

#ifdef DEBUG
    log_info("Set position to %d", position);
#endif
}

void song_set_relative_position(struct mpd_connection *connection,
                                int relative_offset) {
    mpd_send_seek_current(connection, (float)relative_offset, true);
    mpd_check_error(connection, NULL, NULL);

#ifdef DEBUG
    log_info("Changed relative position by %d", relative_offset);
#endif
}
