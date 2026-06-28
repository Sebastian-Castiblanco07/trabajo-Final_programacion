#pragma once
#include <raylib.h>

class disparo{
    public:
        disparo(Vector2 _posicion, int _velocidad, Color _color_disparo);
        void dibujar();
        void mover();
        Rectangle hitbox(); 
        bool vivo;
        float danio = 1;
        Color color_disparo = YELLOW;
    private:
        Vector2 posicion;
        int velocidad;
};