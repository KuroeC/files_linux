#include "primitivepng.h"//on part du principe que toutes les primitives fonctionnent

#include "png_io.h" //pour faire bonne mesure
// Procédure qui calcule la différence entre les composantes RGB de chaque pixel de deux images 
// Entrées : img2 une Image_PNG
// Sortie : img1 une Image_PNG
// Précondition : img1 et img2 doivent être de mêmes dimensions
void differenceimages(Image_PNG & img1, Image_PNG img2){
	// précondition
	assert(img1.largeur == img2.largeur && img1.hauteur == img2.hauteur);
	// variables
	RVB P, Q; // variables temporaires de deux pixels de même indice de l'img1 et l'img2
	// Début
	for(int i = 0 ; i < img1.largeur ; i = i + 1){le
		for(int j = 0 ; j < img2.hauteur ; j = j + 1){
			P=img1.pixels[i][j];
			Q=img2.pixels[i][j];
			assigne_pixel(P,max(P.rouge, Q.rouge) - min(P.rouge, Q.rouge),max(P.vert, Q.vert) - min(P.vert, Q.vert),max(P.bleu, Q.bleu) - min(P.bleu, Q.bleu));  // On calcule la différence entre chaque composante de
//chaque couple de pixel (pixel d'img1, pixel d'img2).
//Fonctions max et min choisies pour éviter toutes erreurs d'overflow
		}
	}
}

int main(int argc, char** argv) {
    if (argc != 4) {
        return -1;
    }
    Image_PNG img1 = charger_PNG(argv[1]);
    Image_PNG img2 = charger_PNG(argv[2]);
    differenceimages(img1, img2);
    sauver_PNG(img1, argv[3]);
}
