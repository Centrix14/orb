#include <assert.h>
#include <string.h>

#include "vreader.h"

void init_deinit_integration() {
    struct orb_vreader r;

    orb_vreader_init(&r);
    assert(orb_vreader_is_ready(r));

    orb_vreader_deinit(&r);
    assert(orb_vreader_is_done(r));
}

void init_deinit_correctness() {
    struct orb_vreader r;

    orb_vreader_init(&r);
    assert(orb_vreader_check(r));

    orb_vreader_deinit(&r);
    assert(orb_vreader_check(r));
}

void read_after_init() {
    struct orb_vreader r;

    orb_vreader_init(&r);

    orb_vreader_read(&r, '1');
    assert(orb_vreader_is_reading(r));

    orb_vreader_deinit(&r);
}

void read_only_after_init_1() {
    struct orb_vreader r;

    orb_vreader_init(&r);
    orb_vreader_deinit(&r);

    orb_vreader_read(&r, '1');

    assert(!orb_vreader_is_reading(r));
    assert(orb_vreader_is_failed(r));
}

void read_only_after_init_2() {
    struct orb_vreader r;

    orb_vreader_read(&r, '1');

    assert(!orb_vreader_is_reading(r));
    assert(orb_vreader_is_failed(r));
}

void token_bounds_checked() {
    struct orb_vreader r;
    orb_vreader_init(&r);

    for (int i = 0; i <= TOKEN_LENGTH + 1; i++) {
        orb_vreader_read(&r, '1');

        if (i == TOKEN_LENGTH + 1)
            assert(!orb_vreader_is_reading(r));
    }

    orb_vreader_deinit(&r);
}

void accept_single_digit() {
    symbol c = '1';

    struct orb_vreader r;
    orb_vreader_init(&r);

    orb_vreader_read(&r, c);

    assert(orb_vreader_is_reading(r));
    assert(!strcmp(r.token, "1"));

    orb_vreader_deinit(&r);
}

void refuse_single_non_digit() {
    symbol c = 'a';

    struct orb_vreader r;
    orb_vreader_init(&r);

    orb_vreader_read(&r, c);
    assert(orb_vreader_is_failed(r));

    orb_vreader_deinit(&r);
}

void read_decimal() {
    symbol *str = "123456";

    struct orb_vreader r;
    orb_vreader_init(&r);

    for (int i = 0; i < strlen(str); i++) {
        orb_vreader_read(&r, str[i]);
        assert(orb_vreader_is_reading(r));
    }

    orb_vreader_deinit(&r);
}

void read_valid_hexidecimal() {
    symbol *str = "0x0123456789abcdef";

    struct orb_vreader r;
    orb_vreader_init(&r);

    for (int i = 0; i < strlen(str); i++) {
        orb_vreader_read(&r, str[i]);
        assert(orb_vreader_is_reading(r));
    }

    orb_vreader_deinit(&r);
}

void refuse_invalid_hexidecimal_1() {
    symbol *str = "x123f";

    struct orb_vreader r;
    orb_vreader_init(&r);

    for (int i = 0; i < strlen(str); i++) {
        orb_vreader_read(&r, str[i]);
        assert(orb_vreader_is_failed(r));
    }

    orb_vreader_deinit(&r);
}

void refuse_invalid_hexidecimal_2() {
    symbol *str = "0xffeg";

    struct orb_vreader r;
    orb_vreader_init(&r);

    for (int i = 0; i < strlen(str); i++) {
        orb_vreader_read(&r, str[i]);

        if (i == strlen(str) - 1)
            assert(orb_vreader_is_failed(r));
    }

    orb_vreader_deinit(&r);
}

void read_valid_binary() {
    symbol *str = "0b00101010";

    struct orb_vreader r;
    orb_vreader_init(&r);

    for (int i = 0; i < strlen(str); i++) {
        orb_vreader_read(&r, str[i]);
        assert(orb_vreader_is_reading(r));
    }

    orb_vreader_deinit(&r);
}

void refuse_invalid_binary() {
    symbol *str = "b00101010";

    struct orb_vreader r;
    orb_vreader_init(&r);

    for (int i = 0; i < strlen(str); i++) {
        orb_vreader_read(&r, str[i]);
        assert(orb_vreader_is_failed(r));
    }

    orb_vreader_deinit(&r);
}

void done_reading_1() {
    struct orb_vreader r;
    orb_vreader_init(&r);

    orb_vreader_read(&r, ':');
    assert(orb_vreader_is_done(r));

    orb_vreader_deinit(&r);
}

void done_reading_2() {
    struct orb_vreader r;
    orb_vreader_init(&r);

    orb_vreader_read(&r, ';');
    assert(orb_vreader_is_done(r));

    orb_vreader_deinit(&r);
}

void done_reading_3() {
    struct orb_vreader r;
    orb_vreader_init(&r);

    orb_vreader_read(&r, ' ');
    assert(orb_vreader_is_done(r));

    orb_vreader_deinit(&r);
}

void done_reading_4() {
    symbol *str = "0xa;";

    struct orb_vreader r;
    orb_vreader_init(&r);

    for (int i = 0; i < strlen(str); i++) {
        orb_vreader_read(&r, str[i]);
    }
    assert(orb_vreader_is_done(r));

    orb_vreader_deinit(&r);
}

void refuse_read_after_done() {
    symbol *str = "0xa :";

    struct orb_vreader r;
    orb_vreader_init(&r);

    for (int i = 0; i < strlen(str); i++) {
        orb_vreader_read(&r, str[i]);

        if (str[i] == ':')
            assert(orb_vreader_is_failed(r));
    }

    orb_vreader_deinit(&r);
}

void live() {
    symbol *values = "12 0x3b1 0b1010";

    struct orb_vreader r;
    orb_vreader_init(&r);

    int index = 0, token_counter = 0;
    while (index < strlen(values)) {
        orb_vreader_read(&r, values[index]);

        if (orb_vreader_is_done(r)) {
            switch (token_counter) {
            case 0:
                assert(!strcmp(r.token, "12"));
                break;
            case 1:
                assert(!strcmp(r.token, "0x3b1"));
                break;
            case 2:
                assert(!strcmp(r.token, "0b1010"));
                break;
            }

            orb_vreader_init(&r);
            token_counter++;
        }

        if (orb_vreader_is_failed(r)) {
            assert("Unexpected error occured." == false);
        }

        index++;
    }

    orb_vreader_deinit(&r);
}

int main(void) {
    init_deinit_integration();
    init_deinit_correctness();

    read_after_init();
    read_only_after_init_1();
    read_only_after_init_2();

    token_bounds_checked();

    accept_single_digit();
    refuse_single_non_digit();

    read_decimal();

    read_valid_hexidecimal();
    refuse_invalid_hexidecimal_1();
    refuse_invalid_hexidecimal_2();

    read_valid_binary();
    refuse_invalid_binary();

    done_reading_1();
    done_reading_2();
    done_reading_3();
    done_reading_4();

    live();

    return 0;
}
