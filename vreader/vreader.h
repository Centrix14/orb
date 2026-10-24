#ifndef __ORB_VALUE_READER_HEADER_DEFINED__
#define __ORB_VALUE_READER_HEADER_DEFINED__

#include <stdint.h>
#include <stdbool.h>

#include "../reader/reader.h"
#include "../aux/aux.h"

void orb_vreader_read(struct orb_reader *reader, char symbol);

#endif
