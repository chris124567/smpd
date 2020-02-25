#ifndef UTIL_H
#define UTIL_H
void __attribute__((noreturn))
die(struct mpd_connection *connection, const char *msg);
void mpd_check_error(struct mpd_connection *connection);
#endif
