
#permet de définir le séparateur(:)
set datafile separator ":"

# taille en pixel du graphique + nom du fichier graphique
set terminal pngcairo size 1000,600
set output 'graphs/graphique_LVmin.png'

#baton
set style data histogram

#largeur baton
set style histogram cluster gap 1

#contour baton
set style fill solid

#remplissage du baton par rapport a sa place
set boxwidth 0.9

#jsp 
set grid ytics

# nom x/y/graphique
set xlabel "LV max/min"
set ylabel "V"
set title "10 max and 10 min"



plot 'data_LV.txt' using 3:xtic(1) title 'LV min' linecolor rgb "#228b22",
