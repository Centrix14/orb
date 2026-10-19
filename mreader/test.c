#include <assert.h>
#include <string.h>

#include "../reader/reader.h"
#include "mreader.h"

void read_single_character_measure() {
    struct orb_reader r;
    orb_reader_init(&r);

    symbol *str = "b;";
    for (int i = 0; i < strlen(str); i++) {
        orb_mreader_read(&r, str[i]);
    }
    assert(orb_reader_is_done(r));

    orb_reader_deinit(&r);
}

void read_multi_character_measure() {
    struct orb_reader r;
    orb_reader_init(&r);

    symbol *str = "mB;";
    for (int i = 0; i < strlen(str); i++) {
        orb_mreader_read(&r, str[i]);
    }
    assert(orb_reader_is_done(r));

    orb_reader_deinit(&r);
}

int main(void) {
    read_single_character_measure();
    read_multi_character_measure();

    return 0;
}
