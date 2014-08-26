# Makefile for building the hardhat project.
#
# Griff, 2014
#
# Targets:
#
# 	$ make build	runs `ino build` with the correct arguments to build for the
# 					arduino micro.
# 	$ make upload	run `ino upload` with the correct arguments to flash the
# 					latest build to the arduino micro.
# 	$ make test		build for the test environment and run test.cpp:main()
# 	$ make clean	clean both the ino and test build areas.
#

MODEL=micro
CFLAGS=-Os

all: test build upload

build: .build/

.build/: src/*
	@echo "BUILD"
	ino build -m $(MODEL) #--cppflags="$(CFLAGS)"

upload: .build/
	@echo "UPLOAD"
	sudo ino upload -m $(MODEL)

test: clean_test
	@echo "TEST"
	gcc -DTEST src/*.cpp -o test/test
	mkdir test/obj
	mv *.o test/obj
	chmod +x test/run_test
	./test/run_test

clean: clean_ino clean_test

clean_ino:
	@echo "CLEAN INO"
	rm -rf .build/

clean_test: 
	@echo "CLEAN TEST"
	rm -rvf test/*

