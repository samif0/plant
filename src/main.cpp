#include "plant.hpp"
#include "sim.hpp"

int main(int argc, char const* argv[]) {
    sim_config cfg{sf::String("plant"), 800, 600};
    sim s{&cfg};

    mesh g{};
    g.to_grid(5, 5, 1, 1, true);
    std::vector<mesh> meshes{g};

    std::vector<point3d> points;
    s.init(meshes, points);
    s.start();
    s.add_object(new plant(0, 0));
    // for each object run through it's update function

    return 0;
}
