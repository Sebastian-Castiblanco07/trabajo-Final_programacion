#include "disparo.hpp"
#include <raylib.h>
#include <iostream>

disparo::disparo(Vector2 posicion,int velocidad){
this -> posicion = posicion;
this -> velocidad = velocidad;
this -> vivo = true;
}

void disparo::dibujar(){
    if(vivo){
        DrawRectangle(posicion.x,posicion.y,10,30,YELLOW);
    }
}
void disparo::mover(){
    posicion.y += velocidad;
    if(vivo){
        if(posicion.y < 0 || posicion.y>GetScreenHeight() ){
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