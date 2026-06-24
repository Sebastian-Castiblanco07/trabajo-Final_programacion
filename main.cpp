#include <raylib.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "nave.hpp"
#include "nave.cpp"
#include "enemigo.hpp"
#include "enemigo.cpp"

const std::string ARCHIVO_CSV = "historial.csv";

void guardarTiempo(int minutos, int segundos) {
    std::ofstream archivo(ARCHIVO_CSV, std::ios::app);
    if (archivo.is_open()) {
        archivo << minutos << ":" << segundos << "\n";
        archivo.close();
    }
}

std::vector<float> leerHistorial() {
    std::vector<float> tiempos;
    std::ifstream archivo(ARCHIVO_CSV);
    if (!archivo.is_open()) return tiempos;
    std::string linea;
    while (std::getline(archivo, linea)) {
        if (linea.empty()) continue;
        int m = 0, s = 0;
        if (sscanf(linea.c_str(), "%d:%d", &m, &s) == 2)
            tiempos.push_back(m * 60.0f + s);
    }
    archivo.close();
    return tiempos;
}
 /*         FUNCION RECURSIVA           */
float tiempoMinimo(const std::vector<float>& tiempos, int idx) {
    if (idx == (int)tiempos.size() - 1) return tiempos[idx];
    float minResto = tiempoMinimo(tiempos, idx + 1);
    return tiempos[idx] < minResto ? tiempos[idx] : minResto;
}

std::vector<enemigo> crearMallaEnemigos() {
    std::vector<enemigo> temp_enemigos;
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 11; j++) {
            int _tipo = 1;
            switch (i) {
                case 0: case 1: _tipo = 3; break;
                case 2: case 3: _tipo = 2; break;
                default:        _tipo = 1; break;
            }
            float x = 60 + j * 60;
            float y = 10 + i * 50;
            temp_enemigos.push_back(enemigo(_tipo, {x, y}));
        }
    }
    return temp_enemigos;
}

void dibujarTextoCentrado(const char* texto, int y, int fontSize, Color color) {
    int ancho = MeasureText(texto, fontSize);
    DrawText(texto, (GetScreenWidth() - ancho) / 2, y, fontSize, color);
}

bool menuInicio() {
    float timer = 0.0f;
    while (!WindowShouldClose()) {
        timer += GetFrameTime();
        if (IsKeyPressed(KEY_ENTER))  return true;
        if (IsKeyPressed(KEY_ESCAPE)) return false;
        BeginDrawing();
        ClearBackground(BLACK);
        dibujarTextoCentrado("SPACE INVADERS", 160, 60, {12, 183, 242, 255});
        dibujarTextoCentrado("- - - - - - - - - - - - - -", 235, 20, {80, 80, 80, 255});
        if ((int)(timer * 2) % 2 == 0)
            dibujarTextoCentrado("PRESIONA  ENTER  PARA JUGAR", 310, 22, WHITE);
        dibujarTextoCentrado("ESC para salir", 360, 16, {120, 120, 120, 255});
        dibujarTextoCentrado("Z = disparar     FLECHAS = mover", 620, 16, {70, 70, 70, 255});
        EndDrawing();
    }
    return false;
}

void menuFinal(bool victoria, float tiempoPartida) {
    int minutos = (int)tiempoPartida / 60;
    int segundos = (int)tiempoPartida % 60;

    bool esRecord = false;
    float record = 0.0f;

    if (victoria) {
        std::vector<float> historial = leerHistorial();
        guardarTiempo(minutos, segundos);
        if (historial.empty()) {
            esRecord = true;
        } else {
            record = tiempoMinimo(historial, 0);
            esRecord = (tiempoPartida < record);
        }
    }

    float timer = 0.0f;
    while (!WindowShouldClose()) {
        timer += GetFrameTime();
        if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_ESCAPE)) break;
        BeginDrawing();
        ClearBackground(BLACK);

        if (victoria) {
            dibujarTextoCentrado("GANASTE!", 250, 60, {12, 183, 242, 255});
            dibujarTextoCentrado(TextFormat("Tiempo: %02d:%02d", minutos, segundos), 330, 28, WHITE);
            if (esRecord) {
                if ((int)(timer * 2) % 2 == 0)
                    dibujarTextoCentrado("Nuevo record!", 380, 24, YELLOW);
            } else {
                int rm = (int)record / 60;
                int rs = (int)record % 60;
                dibujarTextoCentrado(TextFormat("Record: %02d:%02d", rm, rs), 380, 22, {180, 180, 180, 255});
            }
        } else {
            dibujarTextoCentrado("GAME OVER", 280, 60, RED);
        }

        if ((int)(timer * 2) % 2 == 0)
            dibujarTextoCentrado("ENTER para salir", 580, 18, {120, 120, 120, 255});
        EndDrawing();
    }
}

int main() {
    int anchoPantalla = 750;
    int largoPantalla = 700;
    InitWindow(anchoPantalla, largoPantalla, "Space Invaders");
    SetTargetFPS(60);

    if (!menuInicio()) {
        CloseWindow();
        return 0;
    }

    nave jugador;
    std::vector<enemigo> enemigos = crearMallaEnemigos();
    int direccionEnemigos = 1;
    float ultimoDisparoJugador = 0;
    bool gameover = false;
    bool victoria = false;
    float tiempoPartida = 0.0f;

    while (!WindowShouldClose() && !gameover) {
        float dt = GetFrameTime();
        tiempoPartida += dt;
        ultimoDisparoJugador++;

        BeginDrawing();
        ClearBackground(BLACK);

        jugador.proyectar();
        jugador.actualizar();

        if (IsKeyDown(KEY_Z) && ultimoDisparoJugador > 10) {
            jugador.disparar();
            ultimoDisparoJugador = 0;
        }

        for (auto& disparo : jugador.balas) {
            disparo.dibujar();
            disparo.mover();
        }
        for (auto a = jugador.balas.begin(); a != jugador.balas.end();) {
            if (!a->vivo) a = jugador.balas.erase(a);
            else ++a;
        }

        for (auto& e : enemigos) e.dibujar();

        for (auto& e : enemigos) {
            if (e.posicion.x + e.imagenA.width > GetScreenWidth()) {
                for (auto& e2 : enemigos) e2.posicion.y += 6;
                direccionEnemigos = -2;
            } else if (e.posicion.x < 0) {
                for (auto& e2 : enemigos) e2.posicion.y += 6;
                direccionEnemigos = 2;
            }
            e.mover(direccionEnemigos);
        }

        for (auto& disparo : jugador.balas) {
            auto a = enemigos.begin();
            while (a != enemigos.end()) {
                if (CheckCollisionRecs(a->hitbox(), disparo.hitbox())) {
                    a = enemigos.erase(a);
                    disparo.vivo = false;
                    if (enemigos.empty()) {
                        gameover = true;
                        victoria = true;
                    }
                } else {
                    ++a;
                }
            }
        }

        for (auto& e : enemigos) {
            if (CheckCollisionRecs(e.hitbox(), jugador.hitbox())) {
                gameover = true;
                victoria = false;
            }
        }

        {
            int min = (int)tiempoPartida / 60;
            int seg = (int)tiempoPartida % 60;
            const char* textoTiempo = TextFormat("%02d:%02d", min, seg);
            int tw = MeasureText(textoTiempo, 20);
            DrawRectangle(anchoPantalla - tw - 18, 6, tw + 14, 28, {0, 0, 0, 160});
            DrawText(textoTiempo, anchoPantalla - tw - 11, 10, 20, {12, 183, 242, 255});
        }

        EndDrawing();
    }

    menuFinal(victoria, tiempoPartida);

    CloseWindow();
    return 0;
}