 #include <raylib.h>
 #include <iostream>
 #include "nave.hpp"
 #include "nave.cpp"
 
 #include "enemigo.hpp"
 #include "enemigo.cpp"


        
    

    /*      FUNCION MAIN        */
int main(){
     /*   Valores iniciales de la pantalla     */
     Color celeste = {12,183,242,200};
    int anchoPantalla = 750;
    int largoPantalla =700;
    InitWindow(anchoPantalla,largoPantalla,"Asteroids");
    SetTargetFPS(60);
    nave jugador;
    enemigo alien(1, {100,100});
    while( !WindowShouldClose()){
        BeginDrawing();
        // GAME LOOP    
        ClearBackground(celeste);
        jugador.proyectar();
        jugador.actualizar();
        alien.dibujar();
        if(IsKeyDown(KEY_Z)){
            jugador.disparar();
            
        }
        //dibujar y mover balas del jugador
        for(auto& disparo: jugador.balas){
            disparo.dibujar();
            disparo.mover();
        }
        //borrar balas viejas del jugador
        for(auto a = jugador.balas.begin(); a != jugador.balas.end();){
            if(!a -> vivo){
                a = jugador.balas.erase(a);
            } else{
                ++ a;
            }
        }

        EndDrawing();
    }
    CloseWindow();
}