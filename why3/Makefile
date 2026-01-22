all:
	why3 prove base58.mlw --prover=z3 --memlimit=8192 --timelimit=10

extract: c/base58.c c/xorshift.c

c/%.c: %.mlw
	mkdir -p c
	why3 extract --driver=c $*.C -L . > $@.tmp && mv $@.tmp $@ || rm -f $@.tmp
# why3 prove base58.mlw --prover=z3 --memlimit=8192 --timelimit=60
