#ifndef STATUS_H
#define STATUS_H

#include <mpd/client.h>

struct mpd_status *initialize_status(struct mpd_connection *connection);
#endif
