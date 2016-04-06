# The MIT License (MIT)

# Copyright (c) 2016 Yanzheng Li

# Permission is hereby granted, free of charge, to any person obtaining a copy of
# this software and associated documentation files (the "Software"), to deal in
# the Software without restriction, including without limitation the rights to
# use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
# the Software, and to permit persons to whom the Software is furnished to do so,
# subject to the following conditions:

# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.

# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
# FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
# COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
# IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
# CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.


## Makefile for installing all dependencies.

## -----------------------------------------------------------------------------

TOP_DIR=$(CURDIR)
SNEAKER_DIR=$(TOP_DIR)/sneaker
BENCHMARK_DIR=$(TOP_DIR)/benchmark
AVRO_DIR=$(TOP_DIR)/avro
AVRO_CPP_DIR=$(AVRO_DIR)/lang/c++
AVRO_PY_DIR=$(AVRO_DIR)/lang/py
BENCHMARK_HEADER_INSTALL_PATH=/usr/local/include/benchmark/

## -----------------------------------------------------------------------------

ifeq ($(TRAVIS_OS_NAME), linux)
BASE_TARGETS=cmake_target avro sneaker
else
BASE_TARGETS=avro sneaker
endif

## -----------------------------------------------------------------------------

.PHONY: all
ifeq ($(full), 1)
all: $(BASE_TARGETS) benchmark
else
all: $(BASE_TARGETS)
endif

## -----------------------------------------------------------------------------

.PHONY: sneaker
sneaker:
	$(MAKE) -C sneaker fast=1
	$(MAKE) -C sneaker install

## -----------------------------------------------------------------------------

.PHONY: benchmark
benchmark:
	cd $(BENCHMARK_DIR) && cmake -DCMAKE_BUILD_TYPE=Release -DBENCHMARK_ENABLE_LTO=true
	$(MAKE) -C benchmark
	sudo cp -f $(BENCHMARK_DIR)/src/libbenchmark.a /usr/local/lib/
	sudo mkdir -p $(BENCHMARK_HEADER_INSTALL_PATH)
	sudo cp -vr $(BENCHMARK_DIR)/include/benchmark/* $(BENCHMARK_HEADER_INSTALL_PATH)

## -----------------------------------------------------------------------------

.PHONY: cmake_target
cmake_target:
	wget "https://cmake.org/files/v3.2/cmake-3.2.3.tar.gz" --no-check-certificate -v -O cmake-3.2.3.tar.gz
	tar -zxf cmake-3.2.3.tar.gz
	cd cmake-3.2.3 && ./bootstrap -- -DCMAKE_RULE_MESSAGES=OFF >/dev/null && \
		make --no-print-directory --quiet && \
		sudo make install --no-print-directory --quiet >/dev/null

## -----------------------------------------------------------------------------

.PHONY: avro
avro:
	cd $(AVRO_CPP_DIR) && cmake -G "Unix Makefiles" && $(MAKE)
	sudo cp -f $(AVRO_CPP_DIR)/libavrocpp_s.a /usr/local/lib
ifeq ($(TRAVIS_OS_NAME), linux)
	sudo cp -f $(AVRO_CPP_DIR)/libavrocpp.so /usr/local/lib
	sudo cp -f $(AVRO_CPP_DIR)/libavrocpp.so.1.7.7.0 /usr/local/lib
else
	sudo cp -f $(AVRO_CPP_DIR)/libavrocpp.dylib /usr/local/lib
endif
	sudo cp -f $(AVRO_CPP_DIR)/avrogencpp /usr/local/bin
	sudo cp -f $(AVRO_CPP_DIR)/precompile /usr/local/bin
	sudo mkdir -p /usr/local/include/avro
	sudo cp -rf $(AVRO_CPP_DIR)/api/* /usr/local/include/avro/
	cd $(AVRO_PY_DIR) && sudo python setup.py install

## -----------------------------------------------------------------------------