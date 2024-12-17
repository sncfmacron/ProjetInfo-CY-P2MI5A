
#permet de définir le séparateur(;)
set datafile separator ";"

# taille en pixel du graphique + nom du fichier graphique
set terminal pngcairo size 1000,600
set output 'graphs/graphique1LV_max.png'

#baton
set style data histogram

#largeur baton
set style histogram cluster gap 1

#contour baton
set style fill solid border -2

#remplissage du baton par rapport a sa place
set boxwidth 0.9

#jsp 
set grid ytics

# nom x/y/graphique
set xlabel "LV max/min"
set ylabel "capacity(kwh)"
set title "10 LV_max"



plot 'data_LVmax.txt' using 2:xtic(1) title 'LV max' linecolor rgb "#e34234",
