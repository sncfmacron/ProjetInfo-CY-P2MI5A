# C-WIRE
This program processes data for an electricity distribution.

**PREING-2 INFORMATIQUE III PROJECT**.
**Developed by MI-5 group A**

## Contributors

- Romain MICHAUT-JOYEUX
- Nathan CHOUPIN
- Guirec VETIER

## Prerequisites

- You need **make** and **gcc** program to compile and **GnuPlot** to obtain graphs. 
- To install `make` and `gcc` on Ubuntu/Debian distributions, use `sudo apt install make gcc`.
- To install `GnuPlot` on Ubuntu/Debian distributions, use `sudo apt install gnuplot`.

## Usage & compilation
The __c-wire script__ make compilation if the **program_c** is absent and automatically execute the program_c.

To run the program, use `./c-wire.sh [FILE_PATH.csv] [STATION_TYPE] [CONSUMER_TYPE] <POWER_PLANT_ID>`.

## OPTIONS
**[FILE_PATH.csv]**   Location of the input file (**required**)

**[STATION_TYPE]**    Type of station to process: 'hva', 'hvb' or 'lv' (**required**)

**[CONSUMER_TYPE]**   Type of consumer to process: 'all', 'comp' or 'indiv' (**required**)

<POWER_PLANT_ID>  Filters the results for a specific power plant ID (*optional*)

`-h`              Displays help manual (can be placed anywhere)
### WARNING 
    The following combinations are forbidden:
      * hvb all
      * hvb indiv
      * hva all
      * hva indiv

## EXAMPLES
Example 1: `./c-wire.sh input/DATA_CWIRE.csv hva comp`. 

Example 2: `./c-wire.sh input/DATA_CWIRE.csv lv indiv 4`.

Example 3: `./c-wire.sh input/DATA_CWIRE.csv lv all`.

## Overview
- The script `c-wire.sh` allows you to enter options to identify specific stations, checks the integrity of all files and sorts the useful data for station processing. It launches compilation using `make` and produces graphics using `GnuPlot` in case of **lv all**. It ensures the existence of required directories (`tmp`, `graphs`, `output`) or creates them as needed.

- The script `basics.c` contains all basic function such as security functions. The library `basics.h` contains all the libraries needed to run the program and the structure definitions.

- `input.c` contains functions to get the sorted data from `c-wire.sh`.

- `main.c` is the heart of the program. This script executes all program functions and returns a value to indicate that execution has gone well.

- `output.c` contains functions for creating output files in CSV format.

- `settings.h` contains multiple constants used to guarantee program security and optimization.

- `tree.c` contains functions for AVL tree management.

- The script `gnuplot_LVminmax.gp` is used to generate bar graphs of the 10 most and 10 least loaded stations from the program's output data, if the user types the combination “lv all”.
