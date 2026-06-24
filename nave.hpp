#pragma once
#include "disparo.hpp"
#include <raylib.h>
#include <vector>
#define VELOCIDAD 7
class nave{
        public:
        nave();
        void proyectar();
        void actualizar();
        void moverD();
        void moverI();
        void disparar();
        Rectangle hitbox();
        std::vector<disparo> balas;
        private:
        Texture2D imagen;
        Vector2 posicion;
    };
    
