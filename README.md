# AOCPP

This is my attempt at a standardized way of solving [Advent of Code][] problems with C++. It's opinionated about the way things should be structured. I created it because I wanted to be able to do AoC problems faster and I also wanted to get better at C++.

Additionally, I drew inspiration from some of the great project templates in other languages shown in [Awesome Advent of Code][] repository.

## Quickstart

### Build
```bash
$ git clone https://github.com/crlane/aocpp.git
$ cd aocpp
$ make
```

### Usage

#### Create a New Problem

Creating a new problem creates two files in the source directory, `src/day1.h` and `src/day1.cpp`. These are built from a template and automatically will be included on the next build.

```bash
$ ./bin/advent new 1
$ make
$ ./bin/advent run 1
```

#### Run an Existing Problem with Input

Puzzle input is read from stdin and passed to your solution's `Solve` method.

```bash
$ ./bin/advent run 1 < /path/to/helloworld.txt
Registering solution class for day 1
Called solve for day 1!
Input line:Hello, World!
$
```

#### Run an Existing Problem with Args & Input

Sometimes, the AoC puzzles use a random seed or key in addition to the (usually much longer) puzzle input. You can pass any such keys as arguments after the day number.

```bash
$ ./bin/advent run 1 puzzle_seed < /path/to/day1input.txt
Registering solution class for day 1
Called solve for day 1!
Arg: foo
Arg: bar
Arg: baz
Input line:Hello, World!
```

## Design

### Basics

The basic datatype you need to care about is `ISolution`, an abstract class with one function to implement (`Solve`). The interface is described in [ISolution.h](./src/ISolution.h)

```c++
class ISolution {

    public:
        virtual solve(istream& in, const string& args...) = 0;
}
```

### Automatic Registration

Once your class file is generated, it'll automatically be included in the advent binary on the next build. This is because I use a static factory class to handle dynamic registration. I based much of it [this excellent blogpost](registration blog post).
### Logging

This program uses [Plog] to implement a simple logging interface for your solutions. A logger instance will be created for your solution at object creation. To use it, simply `LOG << "your message"` or `LOGDEBUG << "foo"`. This allows you to use in a very similar manner to `std::cout`.

The `-v` command line option sets the log level to `DEBUG`. Using `-vv` sets log level to `VERBOSE`. Otherwise, the level is `INFO`.


## Dependencies

I've vendored several header only dependencies in the include directory that are used in the program.

- cli options with [cxxopts][]
- logging with [Plog][]
- Templating [Mustache][]

[Advent of Code]: https://https://adventofcode.com/
[Plog]: https://github.com/SergiusTheBest/plog
[cxxopts]: https://github.com/jarro2783/cxxopts
[StackOverflow Post]: https://stackoverflow.com/questions/1260954/how-can-i-keep-track-of-enumerate-all-classes-that-implement-an-interface
[Awesome Advent of Code]: https://github.com/Bogdanp/awesome-advent-of-code#project-templates
[Mustache]: https://github.com/kainjow/Mustache
