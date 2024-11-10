# Sourdough Starter
Template structure for new projects.
Don't forget to review and update the [LICENSE](LICENSE) file.

## File Listing
* [LICENSE](LICENSE) - CC0 license
* [.gitignore](.gitignore) - basic git ignore rules
* [sample.sh](sample.sh) - basic Bourne Shell script
* [sample.py](sample.py) - basic Python language script
* [sample.c](sample.c) - basic C language source file
* [Makefile](Makefile) - input for GNU make
  - supports typical build targets all, clean, and test
* [test/](test)
  + contains various test cases in .tc files

## Building
To build the application:
```sh
make
```

To execute the unit tests:
```sh
make test
```

Output will be in the `out/` directory, you can safely delete it or run:
```sh
make clean
```

