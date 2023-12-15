#include "png_io.h"

void clamp(int& value, int min, int max) {
	assert(min <= max);
    if (value < min) value = min;
    else if (value > max) value = max;
}


//-------------------------------------------------------------------

//procédure qui fait le produit de chaque composante d'un pixel par un réel
//entrées : p un pixel, alpha, beta et gamma des réels
//sortie : p un pixel
void produit_pixel(RVB &p,float alpha, float beta, float gamma){
	//on profite toujours que la fonction assigne_pixel force les valeurs à être entre 0 et 255 pour simplifier le code
	assigne_pixel(p, p.rouge*alpha, p.vert*beta, p.bleu*gamma);
}

//-------------------------------------------------------------------
//procédure qui assigne à un pixel les valeurs r, v et b
//entrées : p un pixel, r, v et b des entiers naturels
//sortie : p un pixel
void assigne_pixel(RVB & p, int r, int v, int b){
	//on force les valeurs à être entre 0 et 255 pour éviter les erreurs d'overflow
    clamp(r,0,255);
    clamp(v,0,255);
    clamp(b,0,255);
	//on assigne les valeurs
    p.rouge = r;
    p.vert = v;
    p.bleu = b;
}
//-------------------------------------------------------------------
//procédure qui fait la somme de chaque composante d'un pixel et de trois entiers 
//entrées : P un pixel, alpha, beta et gamma des entiers naturels
//sortie : P un pixel
void somme_pixel(RVB &P , int alpha , int beta , int gamma){
	//on profite que la fonction assigne_pixel force les valeurs à être entre 0 et 255 pour simplifier le code
	assigne_pixel(P, P.rouge + alpha, P.vert + beta, P.bleu + gamma);



bool sont_egalles(images_PNG img1, images_PNG img2){
	if(img1.largeur != img2.largeur || img1.hauteur != img2.hauteur){
		return false;
	}
	for ( int i = 0 ; i < img1.largeur ; i = i + 1 ){
		for ( int j = 0 ; j < img2.hauteur ; j = j + 1 ){
			if ( img1.pixels[i][j] != img2.pixels[i][j] ){
				return false;
			}
		}
	}
	return true;
}
