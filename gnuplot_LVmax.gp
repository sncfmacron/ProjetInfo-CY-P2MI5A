
#permet de définir le séparateur(:)
set datafile separator ":"

# taille en pixel du graphique + nom du fichier graphique
set terminal pngcairo size 1000,600
set output 'graphs/graphiqueLV_max.png'

#baton
set style data histogram

#largeur baton
set style histogram cluster gap 1

#contour baton
set style fill solid

#remplissage du baton par rapport a sa place
set boxwidth 0.9

# permet d'avoir une grille pour mieux se reperer  
set grid ytics

set xtics 1
set yrange [0:40]
set xrange [0:11]
set format y "%g"

# nom x/y/graphique
set xlabel "LV max/min"
set ylabel "capacity(kwh)"
set title "10 LV max"


plot 'data_LV.txt' using 2:xtic(column(0)+1) title 'LV max' linecolor rgb "#e34234",
