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
