PWD := $(shell pwd)

all: misraCheck build

build:
	pushd rust-lib && cargo build && popd && gcc src/main.c rust-lib/target/debug/libedr_system_sim.a -o main && ./main

misraCheck:
	pushd misraC-Checker && python3 main.py $(PWD)/src/main.c && popd && rm -rf $(PWD)/src/main.c.dump $(PWD)/src/main.c.ctu-info 