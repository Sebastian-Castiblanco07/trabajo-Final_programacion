#include "enemigo.hpp"
#include "disparo.hpp"
#include <vector>
#include <raylib.h>

enemigo::enemigo(int _tipo,Vector2 _posicion,float _vida){
    this -> tipo = _tipo;
    this -> posicion = _posicion;
    this -> vida = _vida;
    this -> vidaInicial = _vida;
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
    DrawRectangle(posicion.x,posicion.y+imagenA.height,imagenA.width,imagenA.height/4,WHITE);
    float cantidad_vida = (((vidaInicial - vida)/vidaInicial)*imagenA.width);//cantidad que se le resta a la barra de vida
    DrawRectangle((posicion.x + imagenA.width + 2)-cantidad_vida,(posicion.y)+2+imagenA.height,cantidad_vida - 4,(imagenA.height/4)-4,BLACK);
}
void enemigo::mover(int _direccion){
    posicion.x += float(_direccion);
}
void enemigo::disparar(std::vector<disparo>& balas_enemigos){
    balas_enemigos.push_back(disparo(posicion,7,RED));
}
Rectangle enemigo::hitbox(){
    return{posicion.x,posicion.y,float(imagenA.width),float(imagenA.height)};
}