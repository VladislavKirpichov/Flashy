.PHONY: all build rebuild check test testextra memtest memtestextra clean

all: clean check build test memtest testextra memtestextra

clean:
	rm -rf build

build:
	./build.sh

rebuild: clean build

check:
	./linters/run.sh

test:
	./test.sh