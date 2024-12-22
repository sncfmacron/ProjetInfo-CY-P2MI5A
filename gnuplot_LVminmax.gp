<<<<<<< HEAD
# Fichier temporaire généré
datafile = 'tmp/lv_all_minmax_prepared.dat'

set terminal pngcairo size 1920,1080
set output 'graphs/graph_lv_combined.png'

set style data histogram
set style histogram cluster gap 1
set style fill solid
set boxwidth 0.9
set grid ytics
set xlabel "Station Order"
set ylabel "Load (kWh)"
=======
# gnuplot_LVminmax.gp : A gnuplot script to make graphics from the c-wire output


# Data file used to generate the graph (the default separator character is “ ”)

datafile = 'tmp/lv_all_minmax_prepared.dat'

# Setup the bar graph

set title "LV Stations with Minimum and Maximum Loads"
set output 'graphs/graph_lv_combined.png'

set terminal pngcairo size 1920,1080    # Set the ouput as a '.png' file with a resolution of 1920*1080 pixels
set style data histogram                # Set the graph as a bar graph
set style histogram cluster gap 1       # Group the bars together with a gap of 1 between each group
set style fill solid                    # Fill bars with color
set boxwidth 0.9                        # Set the width of the bars to 90% of the box width
set grid ytics                          # Add grid lines on the y axis

set xtics 1                             # Set the tick marks on the x axis to appear every 1 unit

set xlabel "Station Order (ID)"         # Set the label for the x axis (Station IDs)
set ylabel "Load (kWh)"                 # Set the label for the y axis (Load)

set yrange [0:*]                        # Set the Y-axis range to start from 0, and auto scale upwards

# Variable declaration to define the bar color
>>>>>>> origin/Rom1

# Configuration des xtics avec les nombres de 1 à 20
set xtics nomirror
set xtics 1

set yrange [0:*]
set title "Stations with Minimum and Maximum Loads"

# Définir les couleurs
red = "#ff0000"
green = "#669900"

<<<<<<< HEAD
# Graphe avec des couleurs séparées selon la deuxième colonne
plot \
    datafile using ($2==1 ? $1 : NaN):xticlabels(sprintf("%d",int($0+1))) title 'Underproduction' linecolor rgb red, \
    datafile using ($2==2 ? $1 : NaN):xticlabels(sprintf("%d",int($0+1))) title 'Overproduction' linecolor rgb green
=======
# Generate the graph. We use a condition to check the value of the third column of the input file to define the color of the bar :
# 1 = red (underproduction)
# 2 = green (overproduction)

plot \
    datafile using ($3==1 ? $2 : NaN):xtic(1) title 'Underproduction' linecolor rgb red, \
    datafile using ($3==2 ? $2 : NaN):xtic(1) title 'Overproduction' linecolor rgb green
>>>>>>> origin/Rom1
