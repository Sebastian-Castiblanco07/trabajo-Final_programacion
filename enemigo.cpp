#include "enemigo.hpp"
#include <raylib.h>

enemigo::enemigo(int tipo,Vector2 posicion){
    this -> tipo = tipo;
    this -> posicion = posicion;
    switch (tipo) {
        case 1:
            imagenA = LoadTexture("Imagenes/alien_1.png");
            break;
        case 2:
            imagenA = LoadTexture("Imagenes/alien_2.png");
            break;
        case 3:
            imagenA = LoadTexture("Imagenes/alien_3.png");
            break;
        default:
            imagenA = LoadTexture("Imagenes/alien_1.png");
            break;
    }
}
void enemigo::dibujar(){
    DrawTextureV(imagenA,posicion,WHITE);
}