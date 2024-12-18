# C-WIRE
This program processes data for an electricity distribution.

**PREING-2 INFORMATIQUE III PROJECT**. **Developed by MI-5 group A**

## Contributors

- Romain MICHAUT-JOYEUX
- Nathan CHOUPIN
- Guirec VETIER

## Prerequisites

- You need **GnuPlot** to obtain graphs and **make** program to compile.
- To install `GnuPlot` on Ubuntu/Debian distributions, use `sudo apt install gnuplot`.
- To install `make` on Ubuntu/Debian distributions, use `sudo apt install make`.

## Usage

To run the program, use `./c-wire.sh <path_file.csv> <station_type> <consumer_type> [central_id]`.

Example : `./c-wire.sh input/DATA_CWIRE.csv hva comp 3`.

Use `-h` parameter to get full help.

## Description

To find out if each energy station is overproducing or underproducing, this project examines data from electricity stations. It also calculates the proportion of energy consumed by companies and individuals. The goal is to provide insights into station capacity and energy electricity efficiently, even with large datasets.

## Options

- The script has **required** options:
1. The path to the input CSV file.
2. The station type to analyze (`hvb`, `hva`, or `lv`).
3. The consumer type to analyze (`comp`, `indiv`, or `all`).

**Warning** : The following combinations are forbidden: `hvb all`, `hvb indiv`, `hva all`, and `hva indiv`.

- The script has **optional** options:

4. An **identifier of a central station** can be provided to make the script focuses on a single power plant.
5. `-h` option provides help on using the script.

## Content (/!\ expliquer plus en détail /!\)

- The script `c-wire.sh` allows you to enter options to identify specific stations, checks the integrity of all files and sorts the useful data for station processing. It launches compilation using `make` and produces graphics using `GnuPlot`. It ensures the existence of required directories (`tmp`, `graphs`, `output`) or creates them as needed.

- The script `basics.c` contains all basic function such as security functions. The library `basics.h` contains all the libraries needed to run the program and the structure definitions.

- `input.c` contains functions to get the sorted data from `c-wire.sh`.

- `main.c` is the heart of the program. This script executes all program functions and returns a value to indicate that execution has gone well.

- `output.c` contains functions for creating output files in CSV format.

- `settings.h` contains multiple constants used to guarantee program security and optimization.

- `tree.c` contains functions for AVL tree management.