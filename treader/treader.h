#ifndef __ORB_TYPE_READER_HEADER_DEFINED__
#define __ORB_TYPE_READER_HEADER_DEFINED__

#include <stdint.h>
#include <stdbool.h>

#include "../reader/reader.h"
#include "../aux/aux.h"

struct orb_treader {
    struct orb_reader vreader;
    struct orb_reader mreader;
};

bool orb_treader_is_measure_reading(struct orb_treader reader);
bool orb_treader_is_length_reading(struct orb_treader reader);

void orb_treader_init(struct orb_treader *blank);
void orb_treader_deinit(struct orb_treader *reader);

void orb_treader_read(struct orb_treader *reader, char symbol);

#endif
