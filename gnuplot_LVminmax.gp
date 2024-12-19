
# gnuplot_LVminmax

# permet de définir le séparateur (:)
set datafile separator ":"

# taille en pixel du graphique + nom du fichier graphique
set terminal pngcairo size 1000,600
set output 'graphs/graphLV_minmax.png'

# baton
set style data histogram

# largeur baton
set style histogram cluster gap 1

# contour baton
set style fill solid

# remplissage du baton par rapport a sa place
set boxwidth 0.9

# permet d'avoir une grille pour mieux se reperer  
set grid ytics

# pour avoir une graduation de 1 en 1 POUR l'axe x
set xtics 1

# si tu veux chager la range de y c'est juste en dessous, tu peux meme l'enlever parce que elle sert pas trop 
set yrange [0:80]
set xrange [0:21]

# nom x/y/graphique
set xlabel "Station LV"
set ylabel "Capacity / Unused capacity (kWh)"
set title "20 Stations sorted by unused capacity"

# column(1) remplace la colonne du fichier de l'axe des x

plot 'lv_minmax_temp.csv' using 2:xtic(1) title 'Capacity' linecolor rgb "#669900", \
    '' using 3 title 'Unused capacity' linecolor rgb "#ff0000"