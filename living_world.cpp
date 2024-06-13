#include "fern.hpp"
#include "grass.hpp"
#include "historian.hpp"
#include "macros.hpp"
#include "position.hpp"
#include "sheep.hpp"
#include "wolf.hpp"
#include "world.hpp"
#include <memory>

int main()
{
    TODO("make code work 🤓");

    World world{10, 10};
    Historian historian{};

    std::unique_ptr<Organism> organisms[24] = {
        // grasses
        std::make_unique<Grass>(Position{1, 1}),
        std::make_unique<Grass>(Position{1, 2}),
        std::make_unique<Grass>(Position{2, 1}),
        std::make_unique<Grass>(Position{2, 2}),

        // Ferns
        std::make_unique<Fern>(Position{5, 1}),
        std::make_unique<Fern>(Position{5, 2}),
        std::make_unique<Fern>(Position{6, 1}),
        std::make_unique<Fern>(Position{6, 2}),

        // Wolves
        std::make_unique<Wolf>(3, Position{1, 5}),
        std::make_unique<Wolf>(3, Position{2, 5}),
        std::make_unique<Wolf>(3, Position{1, 6}),
        std::make_unique<Wolf>(3, Position{2, 6}),
        std::make_unique<Wolf>(3, Position{3, 7}),
        std::make_unique<Wolf>(3, Position{4, 7}),
        std::make_unique<Wolf>(3, Position{3, 8}),
        std::make_unique<Wolf>(3, Position{4, 8}),

        // Sheep
        std::make_unique<Sheep>(Position{5, 5}),
        std::make_unique<Sheep>(Position{5, 6}),
        std::make_unique<Sheep>(Position{6, 5}),
        std::make_unique<Sheep>(Position{6, 6}),
        std::make_unique<Sheep>(Position{7, 7}),
        std::make_unique<Sheep>(Position{7, 8}),
        std::make_unique<Sheep>(Position{8, 8}),
        std::make_unique<Sheep>(Position{8, 9}),
    };

    for (auto &x : organisms)
        if (x) {
            x->index(historian += std::make_shared<Record>(0));
            world += x;
        }

    world += [&historian, &world](size_t x) {
        (*historian[x])->death(world.turn());
    };

    world.newRegisterFunc([&historian, &world](Organism& o){
        o.index(historian += std::make_shared<Record>(world.turn()));
    });

    for (int x = 0; x < 50; ++x)
        world();

    for (auto x : historian.records())
        std::cout << *x << std::endl;
}
