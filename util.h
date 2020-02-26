#ifndef UTIL_H
#define UTIL_H
void __attribute__((noreturn))
die(struct mpd_connection *connection, struct mpd_status *status,
    struct mpd_song *song, const char *msg);
void mpd_check_error(struct mpd_connection *connection,
                     struct mpd_status *status, struct mpd_song *song);
#endif
