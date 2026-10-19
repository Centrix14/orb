DIR = .

CC = gcc

TESTFLAGS = -O0 -ggdb -Wall --pedantic-errors
TESTSRC = test.c
TESTBIN = t

reader-test:
	$(CC) $(TESTFLAGS) -o reader/t reader/test.c reader/reader.c reader/mock.c aux/aux.c
	reader/t

vreader-test: DIR = vreader
vreader-test: MODULE = vreader.c
vreader-test:
	$(CC) $(TESTFLAGS) -o $(DIR)/$(TESTBIN) $(DIR)/$(TESTSRC) $(DIR)/$(MODULE)
	$(DIR)/$(TESTBIN)

test: reader-test vreader-test
