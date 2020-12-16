# TypedArchiver

TypedArchiver is a simple archive utility for TAF (Typed Archive Format) files.

## Usage
- `typedarchiver -w [filename]` will write an example file to the file name.
- `typedarchiver -r [filename]` will read a TAF file and print blocks and their data to the console output.

## Compiling
`compile.bat` and `compile.sh` scripts are included for compilation.
On Windows you need to have MinGW installed to run the script.

You can also compile all source files in GCC with:

`gcc src/*.c -o typedarchiver`
