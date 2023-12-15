#include "primitivepng.h"//on part du principe que toutes les primitives fonctionnent

#include "png_io.h" //pour faire bonne mesure

//-------------------------------------------------------------------
// Procedure qui convertit une image en niveaux de gris.
// Entrée: img une Image_PNG
// Sortie: img une Image_PNG
void nivgris(Image_PNG  & img){
	// Variables
	int temp; // valeur temporaire des composantes identiques de chaque pixel gris
	RVB p; // valeur temporaire d'un pixel
	// Début
	for(int i = 0 ; i < img.largeur ; i = i + 1){
		for(int j = 0 ; j < img.hauteur; j = j + 1){
			p = img.pixels[i][j];
			produit_pixel(p, 0.299, 0.587, 0.187); // produit des valeurs d'après formule L = R∗0.299+G∗0.587+B∗0.114.
			temp = p.rouge + p.vert + p.bleu; // somme d'après formule L
			assigne_pixel(p, temp, temp, temp);
		}
	}
}

int main(int argc, char** argv) {
	if (argc != 3) {
		return -1;
	}
	Image_PNG img = charger_PNG(argv[1]);
	nivgris(img);
	sauver_PNG(img, argv[2]);
}
