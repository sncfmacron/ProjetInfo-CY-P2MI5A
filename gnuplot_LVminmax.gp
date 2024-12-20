# gnuplot_LVminmax


red = "#ff0000"
green = "#669900"

# Define the separator

set datafile separator ":"

# Set graphic size in pixels and graphic file name

set terminal pngcairo size 1920,1080
set output 'graphs/graphLV_minmax.png'

# Setup bar graph

set style data histogram
set style histogram cluster gap 1
set style fill solid

set boxwidth 0.9
set grid ytics

set xtics 1

set xlabel "Station LV"
set ylabel "Capacity / Used capacity (kWh)"
set title "20 Stations sorted by used capacity"

set xlabel "Station LV" offset -90,0

# Define abscissa and ordinate ranges

set yrange [0:12*maxLoad]
set xrange [0:21]

# Offset x-axis labels to manage long LV IDs

set xtics rotate by 45
set xtics offset -2,-2.3

# Setup the caption

plot 'output/lv_all_minmax.csv' using 2:xtic(1) title 'Underproduction' linecolor rgb green, \
    'output/lv_all_minmax.csv' using 3 title 'Overproduction' linecolor rgb red