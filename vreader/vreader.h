#ifndef __ORB_VALUE_READER_HEADER_DEFINED__
#define __ORB_VALUE_READER_HEADER_DEFINED__

#include <stdint.h>
#include <stdbool.h>

#define TOKEN_LENGTH 64

typedef char symbol;

enum orb_vreader_state {
    orb_vreader_ready,
    orb_vreader_reading,
    orb_vreader_done,
    orb_vreader_error
};

enum orb_vreader_error {
    orb_vreader_ok,
    orb_vreader_wrong_symbol
};

struct orb_vreader {
    symbol token[TOKEN_LENGTH];

    enum orb_vreader_state state;
    enum orb_vreader_error error;
};

bool orb_vreader_check(struct orb_vreader reader);

bool orb_vreader_is_ready(struct orb_vreader reader);
bool orb_vreader_is_done(struct orb_vreader reader);
bool orb_vreader_is_failed(struct orb_vreader reader);
bool orb_vreader_is_reading(struct orb_vreader reader);

#endif
