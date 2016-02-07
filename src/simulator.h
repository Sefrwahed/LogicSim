#ifndef SIMULATOR_H
#define SIMULATOR_H

namespace Logicsim
{
class Simulator
{
public:
    static Simulator * getInstance();
private:
    static Simulator * instance;
    Simulator();

};
} // namespace Logicsim
#endif // SIMULATOR_H
