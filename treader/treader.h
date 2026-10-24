#ifndef __ORB_TYPE_READER_HEADER_DEFINED__
#define __ORB_TYPE_READER_HEADER_DEFINED__

#include <stdint.h>
#include <stdbool.h>

#include "../reader/reader.h"
#include "../vreader/vreader.h"
#include "../aux/aux.h"

enum orb_treader_state {
    orb_treader_reading_measure,
    orb_treader_reading_length,
    orb_treader_done = orb_reader_done,
    orb_treader_error = orb_reader_error
};

struct orb_treader {
    struct orb_reader vreader;
    struct orb_reader mreader;

    enum orb_treader_state state;
};

bool orb_treader_is_reading_length(struct orb_treader reader);
bool orb_treader_is_reading_measure(struct orb_treader reader);

void orb_treader_init(struct orb_treader *blank);
void orb_treader_deinit(struct orb_treader *reader);

void orb_treader_read(struct orb_treader *reader, char symbol);

#endif
