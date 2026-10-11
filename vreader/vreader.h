#ifndef __ORB_VALUE_READER_HEADER_DEFINED__
#define __ORB_VALUE_READER_HEADER_DEFINED__

#include <stdint.h>
#include <stdbool.h>

#define TOKEN_LENGTH 64

typedef char symbol;
typedef unsigned int token_position;

enum orb_vreader_state {
    orb_vreader_ready,
    orb_vreader_reading,
    orb_vreader_done,
    orb_vreader_error
};

enum orb_vreader_error {
    orb_vreader_ok,
    orb_vreader_read_before_init,
    orb_vreader_token_buffer_overflow,
    orb_vreader_invalid_symbol
};

struct orb_vreader {
    symbol token[TOKEN_LENGTH + 1];
    token_position index;

    enum orb_vreader_state state;
    enum orb_vreader_error error;
};

bool orb_vreader_check(struct orb_vreader reader);

bool orb_vreader_is_ready(struct orb_vreader reader);
bool orb_vreader_is_done(struct orb_vreader reader);
bool orb_vreader_is_failed(struct orb_vreader reader);
bool orb_vreader_is_reading(struct orb_vreader reader);

void orb_vreader_init(struct orb_vreader *blank);
void orb_vreader_deinit(struct orb_vreader *reader);
void orb_vreader_read(struct orb_vreader *reader, char symbol);

#endif
