#include "primitivepng.h"//on part du principe que toutes les primitives fonctionnent 

#include "png_io.h"

// Procédure qui permet d'empiler une image sur une autre
// Entrées : img1 une Image_PNG, img2 une Image_PNG, x et y deux entiers naturels
// Sortie : img1 une Image_PNG

void stack(Image_PNG & img1, Image_PNG img2, int x, int y){
	for(int i = max(0, x) ; i < min(img1.hauteur, x + img2.hauteur) ; i = i + 1){ // boucle à partir du pixel où on veut placer img2 sur img1
		for (int j = max(0, y) ; j < min(img1.largeur, y + img2.largeur) ; j = j + 1){
			img1.pixels[i][j] = img2.pixels[i-x][j-y]; // remplace un pixel de l'img1 par un pixel de l'img2
		}
	}
}
int main(int argc, char** argv) {
    if (argc != 6) {
        return -1;
    }
    Image_PNG img1 = charger_PNG(argv[1]);
    Image_PNG img2 = charger_PNG(argv[2]);
    stack(img1, img2, atoi(argv[3]), atoi(argv[4]));
    sauver_PNG(img1, argv[5]);
}
