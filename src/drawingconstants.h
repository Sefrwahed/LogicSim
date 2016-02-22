#ifndef DRAWINGCONSTANTS_H
#define DRAWINGCONSTANTS_H

namespace Logicsim
{

class DrawingConstants
{
public:
    DrawingConstants* Instance();
    int GATE_X_MARGIN();
    int GATE_Y_MARGIN();
    int CANVAS_WIDTH();
    int CANVAS_HEIGHT();
    int GRID_STEP();
    int NUMBER_OF_SQUARES_IN_ROW();
    int NUMBER_OF_SQUARES_IN_COLUMN();

private:
    static DrawingConstants* instance;
    DrawingConstants();
    int v_GATE_X_MARGIN;
    int v_GATE_Y_MARGIN;
    int v_CANVAS_WIDTH;
    int v_CANVAS_HEIGHT;
    int v_GRID_STEP;
    int v_NUMBER_OF_SQUARES_IN_ROW;
    int v_NUMBER_OF_SQUARES_IN_COLUMN;


};
} //namespace LogicSim
#endif // DRAWINGCONSTANTS_H
