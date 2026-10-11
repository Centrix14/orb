DIR = .

CC = gcc

TESTFLAGS = -O0 -ggdb -Wall --pedantic-errors
TESTSRC = test.c
TESTBIN = t

vreader-test: DIR = vreader
vreader-test: MODULE = vreader.c
vreader-test:
	$(CC) $(TESTFLAGS) -o $(DIR)/$(TESTBIN) $(DIR)/$(TESTSRC) $(DIR)/$(MODULE)
	$(DIR)/$(TESTBIN)

test: vreader-test
