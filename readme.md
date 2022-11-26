# Lab work 6: Simple HTTP server
Authors (team): <a href="https://github.com/bogdanmagometa">Bohdan Mahometa</a>,
<a href="https://github.com/viktorpovazhuk">Viktor Povazhuk</a><br>
## Prerequisites

Tools:
- cmake, GCC

### Compilation


#### Compile with `./compile.sh`

Execute the following command in the project root directory:
```bash
$ ./compile.sh
```

The executable will be built and copied to `./bin/http_server`.

#### Compile manually with cmake

Run the following in the project root directory:
```bash
$ mkdir build
$ cmake -S . -B build
$ cmake --build build
```

The executable will be available by the path `./build/http_server`.

### Installation

Just move the executable wherever you want.

### Usage

Assuming the `http_server` executable is available by the path `./bin/http_server`:
```bash
$ ./bin/http_server &
$ firefox localhost:1337
```

You will see the html page displayed.

### Important!

### Results

We implemented simple HTTP server.

# Additional tasks

The server returns arbitrary HTML bage.
