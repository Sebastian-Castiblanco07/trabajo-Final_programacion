#include "disparo.hpp"
#include <raylib.h>
#include <iostream>

disparo::disparo(Vector2 _posicion,int _velocidad , Color _color_disparo ){
this -> posicion = _posicion;
this -> velocidad = _velocidad;
this -> vivo = true;
this -> danio = 1; 
this -> color_disparo = _color_disparo;
}

void disparo::dibujar(){
    if(vivo){
        DrawRectangle((int)posicion.x, (int)posicion.y, 10, 30, color_disparo);
    }
}
void disparo::mover(){
    posicion.y += float(velocidad);
    if(vivo){
        if(posicion.y < 0 || posicion.y > float(GetScreenHeight()) ){
            vivo = false; 
        }
        
    }
    
}
Rectangle disparo::hitbox(){
    Rectangle rectangulo;
    rectangulo.x = posicion.x;
    rectangulo.y = posicion.y;
    rectangulo.width = 10;
    rectangulo.height = 30;
    return rectangulo;
}