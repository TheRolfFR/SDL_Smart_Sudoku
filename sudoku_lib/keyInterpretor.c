//
// Created by asus on 09/05/2019.
//

#include "keyInterpretor.h"
#include "sdl_sudoku.h"

extern sudokuGrid *data;
void keyInterpretor(SDL_Keycode key){
    if (data->lastKeyWasCtrl && key==SDLK_z)
    {
        undo();
    }
    else{
        data->lastKeyWasCtrl = 0;
        switch (key){
            case SDLK_LCTRL:
            case SDLK_RCTRL:
                data->lastKeyWasCtrl = 1;
                break;
            case SDLK_CAPSLOCK: // Basculement du mode pencil mark
                changeMode();
                ChangeTitleMode(); //Changement du titre de la fenetre (pour indiquer le mode)
                break;
            default:
                if(data->lastClicked != NULL){ //Event agissant sur une case séléctionnée
                    switch (key){
                        case SDLK_1: //nombre
                        case SDLK_KP_1:
                            data->typedNumber = 1;
                            updateCellValue(); //mise à jour de la valeur de la case
                            break;
                        case SDLK_2:
                        case SDLK_KP_2:
                            data->typedNumber = 2;
                            updateCellValue();
                            break;
                        case SDLK_3:
                        case SDLK_KP_3:
                            data->typedNumber = 3;
                            updateCellValue();
                            break;
                        case SDLK_4:
                        case SDLK_KP_4:
                            data->typedNumber = 4;
                            updateCellValue();
                            break;
                        case SDLK_5:
                        case SDLK_KP_5:
                            data->typedNumber = 5;
                            updateCellValue();
                            break;
                        case SDLK_6:
                        case SDLK_KP_6:
                            data->typedNumber = 6;
                            updateCellValue();
                            break;
                        case SDLK_7:
                        case SDLK_KP_7:
                            data->typedNumber = 7;
                            updateCellValue();
                            break;
                        case SDLK_8:
                        case SDLK_KP_8:
                            data->typedNumber = 8;
                            updateCellValue();
                            break;
                        case SDLK_9:
                        case SDLK_KP_9:
                            data->typedNumber = 9;
                            updateCellValue();
                            break;
                            //Fléches directionnelles
                        case SDLK_DOWN:
                            moveSelected(1, 0); //Changement de cellule sélectionnée
                            break;
                        case SDLK_UP:
                            moveSelected(-1, 0);
                            break;
                        case SDLK_LEFT:
                            moveSelected(0, -1);
                            break;
                        case SDLK_RIGHT:
                            moveSelected(0, 1);
                            break;
                            //Echap
                        case SDLK_ESCAPE:
                            unselect(); //Désélection de la cellule sélectionnée
                            break;
                            //Suppr
                        case SDLK_DELETE:
                        case SDLK_BACKSPACE:
                            clearCell(); //Nettoyage de la cellule sélectionnée
                        default:
                            break;
                    }

                }
        }
    }
}

void changeMode(){
    data->pencilMarkMode = (!data->pencilMarkMode);
}