#include <iostream>

#include "math/vector.hpp"
#include "plant.hpp"

using namespace SFSim::Math;

int main(int argc, char const* argv[]) {
    // Create a plant using sfsim's math library
    plant myPlant(5.0f, 3.0f);

    Vector3f position = myPlant.getPosition();
    std::cout << "Plant position: (" << position.x << ", " << position.y << ", " << position.z
              << ")" << std::endl;

    // Demonstrate vector operations from sfsim
    Vector3f direction = Vector3f(1, 0, 0);
    Vector3f newPosition = position + direction * 2.0f;
    myPlant.setPosition(newPosition);

    Vector3f updatedPosition = myPlant.getPosition();
    std::cout << "Updated position: (" << updatedPosition.x << ", " << updatedPosition.y << ", "
              << updatedPosition.z << ")" << std::endl;

    return 0;
}
