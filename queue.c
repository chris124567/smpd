#include <mpd/client.h>
#include <stdlib.h>

#include "constants.h"
#include "log.h"
#include "queue.h"
#include "status.h"
#include "util.h"

#define BOLDWHITE "\033[1m\033[37m"
#define RESET "\033[0m"

void clear_queue(struct mpd_connection *connection) {
    mpd_run_clear(connection);
    mpd_check_error(connection);

#ifdef DEBUG
    log_info("Cleared queue");
#endif
}

void delete_from_queue(struct mpd_connection *connection, int slot) {
    if (slot < 0) {
        die(connection, REMOVE_NEGATIVE_FAIL);
    }
    mpd_run_delete(
        connection,
        (unsigned)slot); /* safe, we check if its greater than 0 above */
    mpd_check_error(connection);

#ifdef DEBUG
    log_info("Deleted slot %d from queue", slot);
#endif
}

void print_queue(struct mpd_connection *connection) {
    int pos;
    int count;
    struct mpd_song *song;
    struct mpd_status *status;

    pos = count = 0;
    status = initialize_status(connection);

    pos = mpd_status_get_song_pos(status);
    if (pos == -1) {
        mpd_status_free(status);
        die(connection, NOTHING_PLAYING_FAIL);
    }
    mpd_check_error(connection);

    mpd_send_list_queue_meta(connection);
    mpd_check_error(connection);
    while ((song = mpd_recv_song(connection)) != NULL) {
        mpd_check_error(connection);
        if (song) {
            const char *artist = mpd_song_get_tag(song, MPD_TAG_ARTIST, 0);
            const char *title = mpd_song_get_tag(song, MPD_TAG_TITLE, 0);
            const char *album = mpd_song_get_tag(song, MPD_TAG_ALBUM, 0);

            printf(
                "%s%d %s %.50s - %.50s [%.50s]%s\n",
                (count == pos) ? BOLDWHITE : "", count,
                (count == pos) ? ">" : "-", artist ? artist : NULL_STRING,
                title ? title : NULL_STRING, album ? album : NULL_STRING,
                RESET); /* character limits to remove clutter with long names */
            mpd_song_free(song);
        }
        count++;
    }

    mpd_status_free(status);

#ifdef DEBUG
    log_info("Printed playlist");
#endif
}

void queue_relative_change(struct mpd_connection *connection, int step) {
    while (step != 0) {
        if (step > 0) {
            mpd_run_next(connection);
            mpd_check_error(connection);
            --step;
        }
        if (step < 0) {
            mpd_run_previous(connection);
            mpd_check_error(connection);
            ++step;
        }
    }

#ifdef DEBUG
    log_info("Changed relative queue position by %d", step);
#endif
}

void shuffle_queue(struct mpd_connection *connection) {
    mpd_run_shuffle(connection);
    mpd_check_error(connection);

#ifdef DEBUG
    log_info("Shuffled queue");
#endif
}