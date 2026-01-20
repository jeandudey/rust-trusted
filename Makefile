all: charon
	aeneas -backend fstar trusted_base58.llbc

hax:
	cd crates/base58 && cargo hax into fstar
	make -C crates/base58/proofs/fstar/extraction
