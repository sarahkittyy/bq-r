# bq-r

platformer WIP repo

## dependencies

* `SFML 2.5`
* `C++20`
* `CMake v3.13+`

## building client

clone the repo & update submodules

```
git clone https://github.com/sarahkittyy/bq-r.git
cd bq-r
git submodule update --init --recursive
```

then build the binary

```
mkdir build
cd build
cmake ..
make
```

output is located in `./build`, run with the cwd in the root directory so any assets are read from there.

```
cd ..
./build/bq-r
```

## backend

Soon:tm:
