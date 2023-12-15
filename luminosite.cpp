#include "primitivepng.h"//on part du principe que toutes les primitives fonctionnent

#include "png_io.h" //pour faire bonne mesure
//-------------------------------------------------------------------
// Procédure qui assombrit ou éclaircit une image
// Entrée : indice un entier naturel ; l'indice est le pourcentage d'assombrissement (si indice < 0) ou d'éclaircissement (si indice > 0)
// Sortie : img une Image_PNG
// Précondition : -100 ≤ indice ≤ 100
void luminosite(Image_PNG & img, int indice){
	// précondition
	assert(-100 <= indice && indice <= 100);
	// variable 
	RVB P; // valeur temporaire d'un pixel
	// Début
	indice = static_cast<int>(indice*2.55); // conversion en entier nécessaire
	for(int i = 0 ; i < img.largeur ; i = i + 1){
		for(int j = 0 ; j < img.hauteur; j = j + 1){
			P = img.pixels[i][j];
			assigne_pixel(P, indice + P.rouge, indice + P.vert, indice + P.bleu);
		}
	}
}

int main(int argc, char** argv) {
	if (argc != 4) {
		return -1;
	}
	Image_PNG img = charger_PNG(argv[1]);
	luminosite(img, atoi(argv[2]));
	sauver_PNG(img, argv[3]);
}
