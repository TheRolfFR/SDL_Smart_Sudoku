//
// Created by asus on 09/05/2019.
//

#include "keyInterpretor.h"
#include "sdl_sudoku.h"

void keyInterpretor(sudokuGrid* data,SDL_Keycode key){
    switch (key){
        case SDLK_LCTRL: // retour en arrière "Undo"
        case SDLK_RCTRL:
            //zWait();
            break;
        case SDLK_CAPSLOCK: // Basculage du mode pencil mark
            data->pencilMarkMode = (!data->pencilMarkMode);
            ChangeTitleMode(data); // et du titre de la fenetre
            break;
        default:
            if(data->lastClicked != NULL){ //if necessaire si on a précédement déselectionné une case avec suppr
                switch (key){ // d abord toutes les touches
                    case SDLK_1:
                    case SDLK_KP_1:
                        updateCellValue(data,1);
                        break;
                    case SDLK_2:
                    case SDLK_KP_2:
                        updateCellValue(data,2);
                        break;
                    case SDLK_3:
                    case SDLK_KP_3:
                        updateCellValue(data,3);
                        break;
                    case SDLK_4:
                    case SDLK_KP_4:
                        updateCellValue(data,4);
                        break;
                    case SDLK_5:
                    case SDLK_KP_5:
                        updateCellValue(data,5);
                        break;
                    case SDLK_6:
                    case SDLK_KP_6:
                        updateCellValue(data,6);
                        break;
                    case SDLK_7:
                    case SDLK_KP_7:
                        updateCellValue(data,7);
                        break;
                    case SDLK_8:
                    case SDLK_KP_8:
                        updateCellValue(data,8);
                        break;
                    case SDLK_9:
                    case SDLK_KP_9:
                        updateCellValue(data,9);
                        break;
                        // Puis les flèches directionelles pour se déplacer sur le plateau
                    case SDLK_DOWN:
                        moveSelected(data, 1, 0);
                        break;
                    case SDLK_UP:
                        moveSelected(data, -1, 0);
                        break;
                    case SDLK_LEFT:
                        moveSelected(data, 0, -1);
                        break;
                    case SDLK_RIGHT:
                        moveSelected(data, 0, 1);
                        break;
                        // puis échap pour pouvoir déselectionner
                    case SDLK_ESCAPE:
                        unselect(data);
                        break;
                        // Suppr ou "retour en arrière" pour nettoyer la cellule
                    case SDLK_DELETE:
                    case SDLK_BACKSPACE:
                        clearCell(data);
                    default:
                        break;
                }

            }
    }
}


void zWait(){

}