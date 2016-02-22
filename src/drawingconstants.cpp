#include "drawingconstants.h"

namespace Logicsim
{
DrawingConstants::DrawingConstants()
{
    v_GATE_X_MARGIN = 20;
    v_GATE_Y_MARGIN = 5;
    v_CANVAS_WIDTH = 2250;
    v_CANVAS_HEIGHT = 2250;
    v_GRID_STEP = 150;
    v_NUMBER_OF_SQUARES_IN_ROW = v_CANVAS_WIDTH / v_GRID_STEP;
    v_NUMBER_OF_SQUARES_IN_COLUMN = v_CANVAS_HEIGHT / v_GRID_STEP;


}
DrawingConstants* DrawingConstants::instance = 0;
DrawingConstants* DrawingConstants::Instance()
{
    if(instance == 0) instance = new DrawingConstants();
    return instance;
}

int DrawingConstants::GATE_X_MARGIN()
{
    return v_GATE_X_MARGIN;
}

int DrawingConstants::GATE_Y_MARGIN()
{
    return v_GATE_Y_MARGIN;
}

int DrawingConstants::CANVAS_WIDTH()
{
    return v_CANVAS_WIDTH;
}

int DrawingConstants::CANVAS_HEIGHT()
{
    return v_CANVAS_HEIGHT;
}

int DrawingConstants::GRID_STEP()
{
    return v_GRID_STEP;
}

int DrawingConstants::NUMBER_OF_SQUARES_IN_ROW()
{
    return v_NUMBER_OF_SQUARES_IN_ROW;
}

int DrawingConstants::NUMBER_OF_SQUARES_IN_COLUMN()
{
    return v_NUMBER_OF_SQUARES_IN_COLUMN;
}


} //namespace LogicSim
