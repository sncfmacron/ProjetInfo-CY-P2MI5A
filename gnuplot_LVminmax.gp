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

# Configuration des xtics avec les nombres de 1 à 20
set xtics nomirror
set xtics 1

set yrange [0:*]
set title "Stations with Minimum and Maximum Loads"

# Définir les couleurs
red = "#ff0000"
green = "#669900"

# Graphe avec des couleurs séparées selon la deuxième colonne
plot \
    datafile using ($2==1 ? $1 : NaN):xticlabels(sprintf("%d",int($0+1))) title 'Underproduction' linecolor rgb red, \
    datafile using ($2==2 ? $1 : NaN):xticlabels(sprintf("%d",int($0+1))) title 'Overproduction' linecolor rgb green
