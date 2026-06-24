 #include <raylib.h>
 #include <iostream>
 #include "nave.hpp"
 #include "nave.cpp"
 
 #include "enemigo.hpp"
 #include "enemigo.cpp"
 void colisiones(){

 };

    std::vector<enemigo> crearMallaEnemigos(){
        std::vector<enemigo> temp_enemigos;
        for (int i = 0;i<6;i++){
            for(int j = 0;j<11;j++){
                int _tipo = 1;
                switch (i)
                {
                case 0:
                    _tipo = 3;
                    break;
                case 1:
                    _tipo = 3;
                    break;
                case 2:
                    _tipo = 2;
                    break;
                case 3:
                    _tipo = 2;
                    break;
                case 4:
                    _tipo = 1;
                    break;
                case 5:
                    _tipo = 1;
                    break;
                default:
                    _tipo = 1;
                    break;
                }
                float x =60+ j*60;
                float y = 10+i*50;
                temp_enemigos.push_back(enemigo(_tipo,{x,y}));
            }
        }
        return temp_enemigos;
    }

        
    

    /*      FUNCION MAIN        */
int main(){
     /*   Valores iniciales de la pantalla     */
     Color celeste = {12,183,242,200};
    int anchoPantalla = 750;
    int largoPantalla =700;
    InitWindow(anchoPantalla,largoPantalla,"Asteroids");
    SetTargetFPS(60);
    nave jugador;
    std::vector<enemigo> enemigos = crearMallaEnemigos();
    int direccioneenemigos = 1;
    float ultimodisparojugador = 0;
    bool gameover = false;
    bool victoria = true;
    while( !WindowShouldClose() && !gameover){
        ultimodisparojugador++;
        BeginDrawing();
        // GAME LOOP    
        ClearBackground(BLACK);
        jugador.proyectar();
        jugador.actualizar();
        if(IsKeyDown(KEY_Z) && ultimodisparojugador>10){
            jugador.disparar();
            ultimodisparojugador = 0;
            
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
        //dibujar todos loe enemigos
        for(auto& enemigo: enemigos){
            enemigo.dibujar();
        }
        //mover los enemigos
        for(auto& enemigo:enemigos ){
            if(enemigo.posicion.x + enemigo.imagenA.width > GetScreenWidth()){
                for(auto&enemigo:enemigos){
                    enemigo.posicion.y += 6;
                }
                direccioneenemigos = -2;
            }else if(enemigo.posicion.x < 0){
                for(auto&enemigo:enemigos){
                    enemigo.posicion.y += 6;
                }
                direccioneenemigos = 2;
            }
            enemigo.mover(direccioneenemigos);
        }
        // colisiones
        for(auto& disparo: jugador.balas){
            auto a = enemigos.begin();
            while(a != enemigos.end()){
                if(CheckCollisionRecs(a->hitbox(),disparo.hitbox())){
                    a = enemigos.erase(a);
                    disparo.vivo = false;
                }else{
                    a++;
                }
            }
        }
        for(auto&enemigo:enemigos){
            if(CheckCollisionRecs(enemigo.hitbox(),jugador.hitbox())){
                    gameover = true;
                    victoria = false;
            }
        }

        EndDrawing();
    }
    CloseWindow();
}