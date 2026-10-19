#ifndef __ORB_READER_HEADER_DEFINED__
#define __ORB_READER_HEADER_DEFINED__

#include <stdint.h>
#include <stdbool.h>

#define TOKEN_LENGTH 64

typedef char symbol;
typedef unsigned int token_position;

enum orb_reader_state {
    orb_reader_ready,
    orb_reader_reading,
    orb_reader_done,
    orb_reader_error
};

enum orb_reader_error {
    orb_reader_ok,
    orb_reader_read_before_init,
    orb_reader_token_buffer_overflow,
    orb_reader_invalid_symbol
};

struct orb_reader {
    symbol token[TOKEN_LENGTH + 1];
    token_position index;

    enum orb_reader_state state;
    enum orb_reader_error error;
};

bool orb_reader_check(struct orb_reader reader);

bool orb_reader_is_ready(struct orb_reader reader);
bool orb_reader_is_done(struct orb_reader reader);
bool orb_reader_is_failed(struct orb_reader reader);
bool orb_reader_is_reading(struct orb_reader reader);

void orb_reader_init(struct orb_reader *blank);
void orb_reader_deinit(struct orb_reader *reader);

#endif

