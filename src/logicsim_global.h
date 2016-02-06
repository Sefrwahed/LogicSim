#ifndef LOGICSIM_GLOBAL
#define LOGICSIM_GLOBAL

// Qt includes

#include <QHash>

// Local includes

#include "gates.h"

namespace Logicsim
{

/* Drawing constants */
const int GATE_X_MARGIN = 20;
const int GATE_Y_MARGIN = 5;
const int CANVAS_WIDTH = 1800;
const int CANVAS_HEIGHT = 1800;
const int GRID_STEP = 90;
const int NUMBER_OF_SQUARES_IN_ROW = CANVAS_WIDTH / GRID_STEP;
const int NUMBER_OF_SQUARES_IN_COLUMN = CANVAS_HEIGHT / GRID_STEP;

} // namespace Logicsim

#endif // LOGICSIM_GLOBAL

