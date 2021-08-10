PWD := $(shell pwd)

all: misraCheck build

build:
	cd rust-lib && cargo build && cd .. && gcc src/main.c rust-lib/target/debug/libedr_system_sim.a -o main && ./main

misraCheck:
	cd misraC-Checker && python3 main.py $(PWD)/src/main.c && cd .. && rm -rf $(PWD)/src/main.c.dump $(PWD)/src/main.c.ctu-info 
