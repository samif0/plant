#include "math/vector.hpp"

using namespace SFSim::Math;

class plant {
private:
    Vector3f position;

public:
    void update() {}
    plant(float x, float y) : position(x, y, 0) {}
    
    Vector3f getPosition() const { return position; }
    void setPosition(const Vector3f& pos) { position = pos; }
};
