
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

#pour avoir une graduation de 1 en 1 POUR l'axe x
set xtics 1

#si tu veux chager la range de y c'est juste en dessoussi tu, tu peux meme l'enlever parce que elle sert pas trop 
set yrange [0:40]
set xrange [0:11]

# nom x/y/graphique
set xlabel "LV max/min"
set ylabel "capacity(kwh)"
set title "10 LV max"

#column(0)+1 remplace la colonne du fichier de l'axe des x

plot 'data_LV.txt' using 2:xtic(column(0)+1) title 'LV max' linecolor rgb "#e34234",
