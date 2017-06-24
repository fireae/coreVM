#!/bin/sh

pushd src/
find ./ -iname *.h -o -iname *.cc | xargs clang-format -i
popd

pushd tests/
find ./ -iname *.h -o -iname *.cc | xargs clang-format -i
popd

pushd tools/
find ./ -iname *.h -o -iname *.cc | xargs clang-format -i
popd

pushd benchmarks/
find ./ -iname *.h -o -iname *.cc | xargs clang-format -i
popd
