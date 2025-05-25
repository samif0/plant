#include "plant.hpp"
#include <cmath>
#include <ecs/entity.hpp>
#include <ecs/render_component.hpp>
#include <ecs/transform_component.hpp>
#include <geometry/mesh.hpp>
#include <geometry/point.hpp>
#include <math/vector.hpp>
#include <sim.hpp>

using namespace SFSim;
using namespace SFSim::Math;
using namespace SFSim::ECS;

int main(int argc, char const *argv[]) {

  SFSim::sim_config cfg{sf::String("plant"), 1200, 800};
  SFSim::sim s{cfg};

  s.addCamera(Vector3f(0, 5, 15), Vector3f(0, 0, 0));

  auto createGrid = MeshGeometry::createGrid();
  Entity gridEntity(1);
  gridEntity.addComponent<TransformComponent>(Vector3f());
  gridEntity.addComponent<RenderComponent>(std::move(createGrid));
  s.addEntity(std::move(gridEntity));

  const float spread = 5.0f;
  const int num_particles = 1000;

  static EntityID nextId = 100;

  for (int i = 0; i < num_particles; ++i) {
    float theta = static_cast<float>(rand()) / RAND_MAX * 2.0f * M_PI;
    float phi = static_cast<float>(rand()) / RAND_MAX * M_PI;
    float r = static_cast<float>(rand()) / RAND_MAX * spread;

    Vector3f pos(r * sin(phi) * cos(theta),
                 r * sin(phi) * sin(theta) + 2.0f, // Offset upward
                 r * cos(phi));

    auto particleMesh = MeshGeometry::createCube(0.2f);
    particleMesh->setColor(sf::Color::Red);

    Entity particleEntity(nextId++);
    particleEntity.addComponent<TransformComponent>(pos);
    particleEntity.addComponent<RenderComponent>(std::move(particleMesh));

    s.addEntity(std::move(particleEntity));
  }

  s.start();
}
