#include "nave.hpp"
 #include "disparo.hpp"
 #include "disparo.cpp"
#include <raylib.h>
#include <vector>

nave::nave(){
        imagen = LoadTexture("Imagenes/nave64px.png");
        posicion.x = GetScreenWidth()/2- imagen.width/2;
        posicion.y = GetScreenHeight()- imagen.height;
    }

void nave::proyectar(){
        DrawTextureV(imagen,posicion, WHITE);
}
void nave::actualizar(){
        if(IsKeyDown(KEY_RIGHT) && (posicion.x+7)< GetScreenWidth()-imagen.width){
            moverD();
        }else if (IsKeyDown(KEY_LEFT) && (posicion.x-7)> 0 ){
            moverI();
        }
    
    };
void nave::moverD(){
        posicion.x += VELOCIDAD;
    };
void nave::moverI(){
        posicion.x -= VELOCIDAD;
    }
void nave::disparar(){
            balas.push_back(disparo({posicion.x + imagen.width/2, posicion.y},-7));
            
        

}
    