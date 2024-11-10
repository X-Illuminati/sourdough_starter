CC=gcc
CFLAGS=-Wall -O2
OUTDIR=out
PROG=sample
TESTFLAGS=

.PHONY: all
all: $(OUTDIR)/$(PROG)

.PHONY: clean
clean: | $(OUTDIR)
	rm -f $(OUTDIR)/*
	rmdir $(OUTDIR)

$(OUTDIR):
	mkdir $(OUTDIR)

$(OUTDIR)/$(PROG): $(PROG).c | $(OUTDIR)
	$(CC) $(CFLAGS) $< -o $@

.PHONY: test
testcases:=$(wildcard test/*.tc)
test: $(testcases:test/%.tc=$(OUTDIR)/%.tc.out)

.SECONDARY: $(testcases:test/%.tc=$(OUTDIR)/%.tc.out)
$(OUTDIR)/%.tc.out: test/%.tc $(OUTDIR)/$(PROG)
	$(OUTDIR)/$(PROG) -i $< -o $@ $(TESTFLAGS)
	cat $@

