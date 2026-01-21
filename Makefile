AENEAS ?= aeneas
CHARON ?= charon

CRATES = trusted-base58

LLBC_FILES = $(CRATES:%=charon/%.llbc)

all: rocq

.PHONY: llbc
llbc: $(LLBC_FILES)

charon:
	mkdir -p $@

charon/%.llbc: charon
	$(CHARON) cargo --preset=aeneas --dest-file=$@ -- --package $*

rocq: $(LLBC_FILES)
	$(AENEAS) -backend rocq -split-files $(LLBC_FILES)

#all: 
#	aeneas -backend fstar trusted_base58.llbc
#
#hax:
#	cd crates/base58 && cargo hax into fstar
#	make -C crates/base58/proofs/fstar/extraction
