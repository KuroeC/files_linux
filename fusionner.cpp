#include "primitivepng.h"//on part du principe que toutes les primitives fonctionnent

#include "png_io.h" //pour faire bonne mesure
//-------------------------------------------------------------------
// Procédure qui permet de fusionner deux images de même taille
// Entrées : img2 une Image_PNG, pourcent un flottant
// Procédure qui applique une image sur une autre avec un pourcentage de transparence donné
// Entrées : img2 une Image_PNG, pourcent un réel ; 
// Sortie : img1 une Image_PNG
// Préconditions : Les deux images entrées en paramètres doivent être de mêmes dimensions
//                 0 ≤ pourcent ≤ 1
void fusionner(Image_PNG & img1 , Image_PNG img2 , float pourcent){
//Variables 
	// préconditions
	assert(0 <= pourcent && pourcent <= 1 && img1.largeur == img2.largeur && img1.hauteur == img2.hauteur);
	// variables
	RVB P, Q ; // valeurs temporaires de deux pixels
	// Debut
	for(int i = 0 ; i <= img1.largeur ; i++){
		for(int j = 0 ; j <= img1.hauteur ; j++){
			P = img1.pixels[i][j] ;
			Q = img2.pixels[i][j];
			produit_pixel(Q , pourcent , pourcent , pourcent); // on applique le pourcentage d'opacité à l'img2
			produit_pixel(P , 1 - pourcent , 1 - pourcent , 1 - pourcent); // on applique le pourcentage d'opacité inverse à img1
			assigne_pixel(img1.pixels[i][j] , P.rouge + Q.rouge , P.vert + Q.vert , P.bleu + Q.bleu); // on combine les deux images
		}
	}
}

int main(int argc, char** argv) {
	if (argc != 5) {
		return -1;
	}
	Image_PNG img1 = charger_PNG(argv[1]);
	Image_PNG img2 = charger_PNG(argv[2]);
	fusionner(img1, img2, atof(argv[3]));
	sauver_PNG(img1, argv[4]);
}
