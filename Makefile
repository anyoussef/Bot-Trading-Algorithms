.PHONY: build run clean

build:
	cmake -B build && cmake --build build

run: build
	./build/alpaca_client

clean:
	rm -rf build
