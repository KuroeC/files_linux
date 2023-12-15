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
/////////////////////////////
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
//////////////////////////////////////////////////
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
///////////////////////////////////////////////
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

///////////////////////////////////////////////
#include "primitivepng.h"//on part du principe que toutes les primitives fonctionnent

#include "png_io.h" //pour faire bonne mesure

//-------------------------------------------------------------------
//-------------------------------------------------------------------
// Fonction qui permet de charger des fichiers texte
// Entrées : listeSortie un tableau de 9 réels, fichierText une chaine
// Sortie : liste de 9 flottants
int fileTxtToList(float (&listeSortie)[9], string fichierText){
    // variables
    fstream fluxFichier;
    float nb;
    // Début
    fluxFichier.open(fichierText, ios::in);
    if (fluxFichier.is_open()) {
        fluxFichier >> nb;  // première lecture avant le tant que
        size_t i = 0;
        while (fluxFichier.good() && i < 9) {
            listeSortie[i] = nb;
            fluxFichier >> nb;  // lecture élément suivant, déclenchant  possiblement une erreur rendant fluxFichier.good() faux 
            i++;
    }
    fluxFichier.close();
  }
    else {
        cout << "Erreur : impossible d'ouvrir " << fichierText << endl;
        return -1;
  }
return 0;
}
//-------------------------------------------------------------------
void filtre_matriciel(Image_PNG & img,float tab[9]){
	// Variables
    RVB P;
	// Début 
    for (int i; i < img.hauteur; i++){
        for (int j; j < img.largeur; j++){
            P=img.pixels[i][j];
            //produit matriciel entre le vecteur colonne RVB et la matrice tab
            //on obtient un vecteur colonne RVB qui est la nouvelle couleur du pixel
            assigne_pixel(img.pixels[i][j],P.rouge*tab[0]+P.vert*tab[1]+P.bleu*tab[2],P.rouge*tab[3]+P.vert*tab[4]+P.bleu*tab[5],P.rouge*tab[6]+P.vert*tab[7]+P.bleu*tab[8]);     
		}
	}
}


int main(int argc, char** argv) {
	if (argc != 4) {
		return -1;
	}
	Image_PNG img = charger_PNG(argv[1]);
	float tab[9];
	fileTxtToList(tab, argv[2]);
	filtre_matriciel(img, tab);
	sauver_PNG(img, argv[3]);
}
///////////////////////////////////////////////
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
///////////////////////////////////////////////

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

///////////////////////////////////////////////
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
