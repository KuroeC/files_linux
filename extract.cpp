#include "primitivepng.h"//on part du principe que toutes les primitives fonctionnent

#include "png_io.h" //pour faire bonne mesure

//-------------------------------------------------------------------
// Fonction qui permet d'extraire un morceau d'image spécifié par ses coordonées
/* Entrées: img une Image_PNG et x1, x2, y1 et y2 quatre entiers naturels représentant
les coordonnées x et y des quatre coins du morceau d'image a extraire */
// Sortie : img2 une Image_PNG
// Préconditions : 0 ≤ x1 < x2≤image et 0 ≤ y1 ≤ y2 ; on s'assure que les coordonnées de début et de fin sont
//                                              dans les limites de l'image et forment une région valide.
Image_PNG extract(Image_PNG img , int x1 , int x2 , int y1 , int y2){
	// Préconditions
	assert(0 <= x1 && x1 < x2 && x2 <= img.largeur && 0 <= y1 && y1 < y2 && y2 <= img.hauteur);
	// Début
	Image_PNG img2 = creer_PNG(x2 - x1 , y1 -y2);
	for(int i = x1; x1 <= x2; i++){
		for(int j = y1 ; y1 <= y2 ;j++){
			img2.pixels[i - x1][j - y1] = img.pixels[i][j]; // remplace un pixel de l'img2 par un pixel de l'img
		}
	}
	return img2;
} 


int main(int argc, char** argv) {
	if (argc != 7) {
		return -1;
	}
	Image_PNG img = charger_PNG(argv[1]);
	Image_PNG img2 = extract(img, atoi(argv[2]), atoi(argv[3]), atoi(argv[4]), atoi(argv[5]));
	sauver_PNG(img2, argv[6]);
}
