CC = gcc

TESTFLAGS = -O0 -ggdb -Wall --pedantic-errors
TESTSRC = test.c
TESTBIN = t

DIR = .
COMMON_MODULES = reader/reader.c aux/aux.c

reader-test: DIR = reader
reader-test: SRC = $(DIR)/mock.c $(COMMON_MODULES)

vreader-test: DIR = vreader
vreader-test: SRC = $(DIR)/vreader.c $(COMMON_MODULES)

mreader-test: DIR = mreader
mreader-test: SRC = $(DIR)/mreader.c $(COMMON_MODULES)

treader-test: DIR = treader
treader-test: SRC = $(DIR)/treader.c vreader/vreader.c $(COMMON_MODULES)

reader-test vreader-test mreader-test treader-test:
	$(CC) $(TESTFLAGS) -o $(DIR)/$(TESTBIN) $(DIR)/$(TESTSRC) $(SRC)
	$(DIR)/$(TESTBIN)

test: reader-test vreader-test mreader-test treader-test
