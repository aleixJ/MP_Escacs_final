//
//  main.cpp
//
//  Copyright � 2018 Compiled Creations Limited. All rights reserved.
//

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__) || defined  (_WIN64)

#include <iostream>
//Definicio necesaria per poder incloure la llibreria i que trobi el main
#define SDL_MAIN_HANDLED
#include <windows.h>
//Llibreria grafica
#include "../Graphic Lib/libreria.h"
#include "../Graphic Lib/NFont/NFont.h"
#include <conio.h>      /* getch */ 

#elif __APPLE__
//Llibreria grafica
#include "../Graphic Lib/libreria.h"
#include "../Graphic Lib/NFont/NFont.h"
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdocumentation"
#include <SDL2/SDL.h>
#pragma clang diagnostic pop

#endif

#include "./Chess/CurrentGame.hpp"
#include "./Chess/GameInfo.h"


int main(int argc, const char* argv[])
{
	//Instruccions necesaries per poder incloure la llibreria i que trobi el main
	SDL_SetMainReady();
	SDL_Init(SDL_INIT_VIDEO);

	//Inicialitza un objecte de la classe Screen que s'utilitza per gestionar la finestra grafica
	Screen pantalla(SCREEN_SIZE_X, SCREEN_SIZE_Y);
	//Mostrem la finestra grafica
	pantalla.show();

	CurrentGame game;
    bool inicialitzat = false;
    string fileMoviments = "data/Games/movements.txt";
    bool end = false;

    do
    {
        // Captura tots els events de ratolí i teclat de l'ultim cicle
        pantalla.processEvents();

        bool mouseStatus = Mouse_getBtnLeft();
        int mousePosX = Mouse_getX();
        int mousePosY = Mouse_getY();
        end = game.updateAndRender(mousePosX, mousePosY, mouseStatus);
        if ((game.getMode() != GM_NONE) && (!inicialitzat))
        {
            game.init(game.getMode(), "data/Games/board.txt", fileMoviments);
            inicialitzat = true;
        }
        // Actualitza la pantalla
        pantalla.update();

    } while ((!Keyboard_GetKeyTrg(KEYBOARD_ESCAPE)) && (end == 0));
    // Sortim del bucle si pressionem ESC

    game.end(fileMoviments);

	//Instruccio necesaria per alliberar els recursos de la llibreria 
	SDL_Quit();
	return 0;
}

