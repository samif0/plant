#include "sim.hpp"

class plant : public sim_object {
private:
    int x, y;

public:
    void update() override {}
    plant(int x, int y) : x(x), y(y) {}
};
