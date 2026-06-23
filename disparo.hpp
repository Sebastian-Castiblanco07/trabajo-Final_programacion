#pragma once
#include <raylib.h>

class disparo{
    public:
        disparo(Vector2 posicion, int velocidad);
        void dibujar();
        void mover();
        bool vivo;
    private:
        Vector2 posicion;
        int velocidad;
};