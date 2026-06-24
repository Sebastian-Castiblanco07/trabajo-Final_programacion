#pragma once
#include <raylib.h>

class enemigo{
    public:
        Texture2D imagenA;
        int tipo;
        Vector2 posicion;
        enemigo(int tipo, Vector2 posicion);
        void dibujar();
        Rectangle hitbox();
        void mover(int direccion);
        private:

};
