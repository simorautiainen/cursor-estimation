pushd "$(dirname "$0")"
pushd ..
cmake -B build
cmake --build build
popd
popd