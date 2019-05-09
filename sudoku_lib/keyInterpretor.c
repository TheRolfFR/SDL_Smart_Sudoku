//
// Created by asus on 09/05/2019.
//

#include "sdl_sudoku.h"

void keyInterpretor(sudokuGrid* data,SDL_Keycode key){
    switch (key){
        case SDLK_LCTRL:
        case SDLK_RCTRL:
            zWait();
            break;
        case SDLK_CAPSLOCK:
            data->pencilMarkMode = (!data->pencilMarkMode);
            break;
        default:
            if(data->lastHovered->isClicked){
                switch (key){
                    case SDLK_1:
                        updateCellValue(data,1);
                        break;
                    case SDLK_2:
                        updateCellValue(data,2);
                        break;
                    case SDLK_3:
                        updateCellValue(data,3);
                        break;
                    case SDLK_4:
                        updateCellValue(data,4);
                        break;
                    case SDLK_5:
                        updateCellValue(data,5);
                        break;
                    case SDLK_6:
                        updateCellValue(data,6);
                        break;
                    case SDLK_7:
                        updateCellValue(data,7);
                        break;
                    case SDLK_8:
                        updateCellValue(data,8);
                        break;
                    case SDLK_9:
                        updateCellValue(data,2);
                        break;
                    case SDLK_DOWN:
                        moveSelected(data,3);
                        break;
                    case SDLK_UP:
                        moveSelected(data,1);
                        break;
                    case SDLK_LEFT:
                        moveSelected(data,4);
                        break;
                    case SDLK_DOWN:
                        moveSelected(data,5);
                        break;
                    case SDLK_ESCAPE:
                        data->lastHovered->isClicked = 0;
                        updateHover(data,getMousePosition(data));
                        break;
                }

            }
    }
}


void zWait(){

}