all:
	cd crates/base58 && cargo hax into fstar
	make -C crates/base58/proofs/fstar/extraction
