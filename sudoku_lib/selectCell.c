//
// Created by asus on 09/05/2019.
//

#include "sdl_sudoku.h"


void selectCell(sudokuGrid* data, cell* position){
    if(position==NULL){
        if(data->lastHovered!=NULL){
            data->lastHovered->isClicked = 0;
            updateHover(data,position);
        }
    }
    else{
        if (position!=data->lastHovered){
            data->lastHovered->isClicked = 0;
            updateHover(data,position);
            position->isClicked = 1;
        }
        else{
            if(!position->isClicked){
                position->isClicked = 1;
            }
        }
    }
}