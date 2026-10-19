#include <assert.h>
#include <string.h>

#include "reader.h"
#include "mock.h"

void init_deinit_integration() {
    struct orb_reader r;

    orb_reader_init(&r);
    assert(orb_reader_is_ready(r));

    orb_reader_deinit(&r);
    assert(orb_reader_is_done(r));
}

void init_deinit_correctness() {
    struct orb_reader r;

    orb_reader_init(&r);
    assert(orb_reader_check(r));

    orb_reader_deinit(&r);
    assert(orb_reader_check(r));
}

void read_after_init() {
    struct orb_reader r;

    orb_reader_init(&r);

    orb_mock_read(&r, '1');
    assert(orb_reader_is_reading(r));

    orb_reader_deinit(&r);
}

void read_only_after_init_1() {
    struct orb_reader r;

    orb_reader_init(&r);
    orb_reader_deinit(&r);

    orb_mock_read(&r, '1');

    assert(!orb_reader_is_reading(r));
    assert(orb_reader_is_failed(r));
}

void read_only_after_init_2() {
    struct orb_reader r;

    orb_mock_read(&r, '1');

    assert(!orb_reader_is_reading(r));
    assert(orb_reader_is_failed(r));
}

void token_bounds_checked() {
    struct orb_reader r;
    orb_reader_init(&r);

    for (int i = 0; i <= TOKEN_LENGTH + 1; i++) {
        orb_mock_read(&r, '1');

        if (i == TOKEN_LENGTH + 1)
            assert(!orb_reader_is_reading(r));
    }

    orb_reader_deinit(&r);
}

void done_reading() {
    struct orb_reader r;
    orb_reader_init(&r);

    orb_mock_read(&r, ';');
    assert(orb_reader_is_done(r));

    orb_reader_deinit(&r);
}

void refuse_read_after_done() {
    symbol *str = "12 7";

    struct orb_reader r;
    orb_reader_init(&r);

    for (int i = 0; i < strlen(str); i++) {
        orb_mock_read(&r, str[i]);

        if (str[i] == ' ')
            assert(orb_reader_is_done(r));
        else if (str[i] == '7')
            assert(orb_reader_is_failed(r));
        else
            assert(orb_reader_is_reading(r));
    }

    orb_reader_deinit(&r);
}

int main(void) {
    init_deinit_integration();
    init_deinit_correctness();

    read_after_init();
    read_only_after_init_1();
    read_only_after_init_2();

    token_bounds_checked();

    done_reading();

    refuse_read_after_done();

    return 0;
}
