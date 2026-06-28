#pragma once
#include <raylib.h>
#include <disparo.hpp>
#include <vector>
class enemigo{
    public:
        Texture2D imagenA;
        int tipo;
        Vector2 posicion;
        float vida;
        float vidaInicial;
        enemigo(int tipo, Vector2 posicion, float vida = 1);
        void dibujar();
        void disparar(std::vector<disparo>& balas_enemigos);
        Rectangle hitbox();
        void mover(int direccion);
        private:

};
