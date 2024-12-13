# C-WIRE
This program processes data for an electricity distribution.

**PREING-2 Computer Science Project**. **Developed by the MI-5 group A team**

## Contributors

- Romain MICHAUT-JOYEUX
- Nathan CHOUPIN
- Guirec VETIER

## Prerequisites

- You need `GnuPlot` program to obtain graphs.
- To install it on Ubuntu/Debian distributions, type `sudo apt install gnuplot`.
- You also need `make` to compile the program, to install it type `sudo apt install make`.

## Usage

To run the program, use `./c-wire.sh <path_file.csv> <station_type> <consumer_type> [central_id]`.

Usage example : `./c-wire.sh ./input/DATA_CWIRE.csv hva comp 2`.

Use the `-h` parameter to get full help.
- Note : you must place your input file in /input directory and name it **DATA_CWIRE.csv**.

## Description

This project analyzes energy station data to determine whether each station is experiencing overproduction or underproduction. It also evaluates the proportion of energy consumed by companies and individuals. The goal is to provide insights into station capacity and energy consumption efficiently, even with large datasets.

The program consists of two main parts: a Shell script and a C program that work together to process input data and filter relevant information.

### Shell Script (`c-wire.sh`)

- The script has **required** input arguments:
1. The path to the input CSV file.
2. The station type to analyze (`hvb`, `hva`, or `lv`).
3. The consumer type to analyze (`comp`, `indiv`, or `all`).

**Warning** : The following combinations are forbidden: `hvb all`, `hvb indiv`, `hva all`, and `hva indiv`.

- The script has **optionnal** input arguments:

4. An **identifier of a central station** can be provided to make the script focuses on the analysis of a single power plant.
5. An optional `-h` flag provides detailed help and instructions on using the script.

The script sends the sorted information to the executable program using a **pipe**, which is the fastest way to do it.

It compiles the C program if it’s missing and calls it with the provided parameters.

The script will create graphs from the data files calculated by the C program, using `GnuPlot`.

### C Program (`program_c`)

The C program uses an **AVL tree data structure** to efficiently store and update station information in memory.

It calculates the energy consumption for HV-B, HV-A, and LV stations.

The program processes the input data, updates station capacities and consumer sums, and generates CSV output files like `lv_all.csv`.

In the case of `lv all`, it creates `lv_all_minmax.csv` containing the 10 LV stations with the highest and lowest energy consumption.

## Content

- The script `c-wire.sh` allows you to enter options to identify specific stations, checks the integrity of all files and sorts the data useful for station processing. It launches compilation using `make` and produces graphics using `GnuPlot`. It ensures the existence of required directories (`tmp`, `graphs`) or creates them as needed.

- The script `basics.c` contains all basic function such as security functions. The library `basics.h` contains all the libraries needed to run the program and the structure definitions.

- `calculations.c` calculates the energy consumption for HV-B, HV-A, and LV stations.

- `input.c` contains functions to get the sorted data from `c-wire.sh` using a pipe.

- `main.c` is the heart of the program. This script executes all program functions and returns a value to indicate that execution has gone well.

- `output.c` contains functions for creating output files in CSV format.

- `settings.h` contains multiple constants used to guarantee program security and optimization.

- `tree.c` contains functions for AVL tree management.