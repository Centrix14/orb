CC = gcc

TESTFLAGS = -O0 -ggdb -Wall --pedantic-errors
TESTSRC = test.c
TESTBIN = t

DIR = .
GENERAL_MODULES = reader/reader.c aux/aux.c

reader-test:
	$(CC) $(TESTFLAGS) -o reader/t reader/test.c reader/reader.c reader/mock.c aux/aux.c
	reader/t

vreader-test: DIR = vreader
vreader-test: SRC = $(DIR)/vreader.c $(GENERAL_MODULES)
vreader-test:
	$(CC) $(TESTFLAGS) -o $(DIR)/$(TESTBIN) $(DIR)/$(TESTSRC) $(SRC)
	$(DIR)/$(TESTBIN)

mreader-test:
	$(CC) $(TESTFLAGS) -o mreader/t mreader/test.c reader/reader.c mreader/mreader.c aux/aux.c
	mreader/t

test: reader-test vreader-test mreader-test
