#include <stdint.h>
#include <stdbool.h>

#include "vreader.h"

bool orb_vreader_is_ready(struct orb_vreader reader) {
    return (reader.token[0] == '\0')
        && (reader.state == orb_vreader_ready)
        && (reader.error == orb_vreader_ok);
}

bool orb_vreader_is_done(struct orb_vreader reader) {
    return (reader.state == orb_vreader_done)
        && (reader.error == orb_vreader_ok);
}

bool orb_vreader_is_failed(struct orb_vreader reader) {
    return (reader.state == orb_vreader_reading)
        && (reader.error != orb_vreader_ok);
}

bool orb_vreader_is_reading(struct orb_vreader reader) {
    return (reader.state == orb_vreader_reading)
        && (reader.error == orb_vreader_ok);
}

bool orb_vreader_check(struct orb_vreader reader) {
    int8_t condition =
        orb_vreader_is_ready(reader)
        | orb_vreader_is_done(reader) << 1
        | orb_vreader_is_failed(reader) << 2
        | orb_vreader_is_reading(reader) << 3;

    return (condition == 0b0001)
        | (condition == 0b0010)
        | (condition == 0b0100)
        | (condition == 0b1000);
}
