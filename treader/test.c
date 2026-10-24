#include <assert.h>
#include <string.h>

#include "treader.h"

void accept_value_part() {
    struct orb_treader r;
    orb_treader_init(&r);

    symbol *value = "0x3b1 ";
    for (int i = 0; i < strlen(value); i++) {
        orb_treader_read(&r, value[i]);

        if (value[i] == ' ')
            assert(orb_treader_is_measure_reading(r));
        else
            assert(orb_treader_is_length_reading(r));
    }

    orb_treader_deinit(&r);
}

int main(void) {
    accept_value_part();

    return 0;
}
