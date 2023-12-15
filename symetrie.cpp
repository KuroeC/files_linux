#include "primitivepng.h"//on part du principe que toutes les primitives fonctionnent

#include "png_io.h" //pour faire bonne mesure
//---------------------------------------------------------------------
// Fonction qui applique une symétrie sur une image
// Entrées: img une Image_PNG, axe un entier ; axe détermine le type de symétrie appliqué
//Sortie : img2 une Image_PNG
Image_PNG symetrie(Image_PNG img, int axe){
	// variable
	Image_PNG img2 = creer_PNG(img.largeur, img.hauteur); // image en sortie 
	if (axe == 0){ // symétrie verticale
		for(int i = 0 ; i < img.hauteur ; i = i + 1){
			for(int j = 0 ; j < img.largeur ; j = j + 1){
				img2.pixels[i][j] = img.pixels[i][img.largeur - j - 1];
			}
		}
	}
	else if (axe == 1){ // symétrie horizontale
		for(int i = 0 ; i < img.hauteur ; i = i + 1){
			for(int j = 0 ; j < img.largeur ; j = j + 1){
				img2.pixels[i][j] = img.pixels[img.hauteur - i - 1][j];
			}
		}
	}
	return img2;

}
int main(int argc, char** argv) {
	if (argc != 4) {
		return -1;
	}
	Image_PNG img = charger_PNG(argv[1]);
	Image_PNG img2 = symetrie(img, atoi(argv[2]));
	sauver_PNG(img2, argv[3]);
}
