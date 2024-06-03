## foobar-examples

This is a simple module where you should put your examples.

To compile an example, you can use this command from the project_dir: 
```bash
./helper-scripts/project-impl/compile-examples.sh "atmega32" "hello_foobar.c"
```
> This will basically compile and link the example `hello_foobar` with the library foobar and assemble the output into 
> `hello_foobar.c.elf` at `./foobar-examples/build/atmega32`.

To upload the code, you can use avr-objcopy to convert to HEX file first, then upload using avrdude: 
1) Adjust the upload properties at `./helper-scripts/project-impl/variables.sh`.

2) Upload using:
```bash
./helper-scripts/project-impl/upload-to-chip.sh "hello_foobar.c.elf" "./foobar-examples/src/hello_foobar.c"
```
> This will copy the object code (instruction code) at hello_foobar.c.elf into a new format hello_foobar.c.elf.hex 
> and uploads the hex file to the mcu flash memory.