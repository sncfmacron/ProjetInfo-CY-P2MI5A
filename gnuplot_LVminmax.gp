# gnuplot_LVminmax.gp : a gnuplot script to make graphics from c-wire output


# Data file usage

datafile = 'output/lv_all_minmax.csv'
set datafile separator ":"

# Setup bar graph

set terminal pngcairo size 1920,1080

set style data histogram
set style histogram cluster gap 1
set style fill solid

set boxwidth 0.9
set grid ytics

set xtics 1

set xlabel "Station LV"
set ylabel "Load (kWh)"

red = "#ff0000"
green = "#669900"

# Offset for x-axis labels to display long LV IDs

set xtics rotate by 45
set xtics offset -2,-2.3

# Define abscissa and ordinate ranges

set yrange [0:*]
set xrange [0:11]

# Setup the first graph (graph_lv_min.png)

set title "Ten stations with the minimum load"
set output 'graphs/graph_lv_min.png'

# Plot the first 10 bars in red (Underproduction)
plot datafile using 3:xtic(1) every ::0::10 title 'Underproduction' linecolor rgb red

# Setup second graph (graph_lv_max.png)

set title "Ten stations with the maximum loadds"
set output 'graphs/graph_lv_max.png'

plot datafile using 3:xtic(1) every ::11::20 title 'Overproduction' linecolor rgb green