#include <mpd/client.h>

#include "constants.h"
#include "log.h"
#include "song.h"
#include "status.h"
#include "util.h"

void print_current_song(struct mpd_connection *connection) {
    struct mpd_song *song;

    song = mpd_run_current_song(connection);
    if (song == NULL) {
        die(connection, RECV_SONG_FAIL);
    }
    mpd_check_error(connection);

    const char *artist = mpd_song_get_tag(song, MPD_TAG_ARTIST, 0);
    const char *title = mpd_song_get_tag(song, MPD_TAG_TITLE, 0);

    if (artist && title) {
        printf("%s - %s\n", artist, title);
    }

    mpd_song_free(song);

#ifdef DEBUG
    log_info("Got current song information");
#endif
}

void print_current_song_metadata(struct mpd_connection *connection) {
    int i;
    struct mpd_song *song;

    song = mpd_run_current_song(connection);
    if (song == NULL) {
        die(connection, RECV_SONG_FAIL);
    }

    for (i = 0; i < 10; ++i) {
        const char *field_name = mpd_tag_name(i);
        const char *field_value = mpd_song_get_tag(song, i, 0);

        if (field_value) {
            printf("%s: %s\n", field_name, field_value);
        } else {
            printf("%s: %s\n", field_name,
                   NULL_STRING); /* if field does not exist */
        }
    }
    mpd_song_free(song);
    mpd_check_error(connection);

#ifdef DEBUG
    log_info("Got current song metadata");
#endif
}