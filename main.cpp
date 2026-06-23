 #include "raylib.h"
 #define VELOCIDAD 7
    /*      CLASES      */
    class nave{
        public:
        nave();
        void proyectar();
        void actualizar();
        void moverD();
        void moverI();
        void disparar();
        private:
        Texture2D imagen;
        Vector2 posicion;
    };
    /*      definir funciones de objetos        */
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

    /*      FUNCION MAIN        */
int main(){
     /*   Valores iniciales de la pantalla     */
     Color celeste = {12,183,242,200};
    int anchoPantalla = 750;
    int largoPantalla =700;
    InitWindow(anchoPantalla,largoPantalla,"Nombre por definir");
    SetTargetFPS(60);
    nave jugador;
    while( !WindowShouldClose()){
        BeginDrawing();
        // GAME LOOP    
        ClearBackground(celeste);
        jugador.proyectar();
        jugador.actualizar();

        EndDrawing();
    }
    CloseWindow();
}