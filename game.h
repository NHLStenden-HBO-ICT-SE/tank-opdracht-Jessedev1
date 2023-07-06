#pragma once
#include "Grid.h"
#include <memory>
#include <BS_thread_pool.hpp>

namespace Tmpl8
{
//forward declarations
class Tank;
class Rocket;
class Smoke;
class Particle_beam;

class Game
{
public:
    void set_target(Surface* surface) { screen = surface; }
    void init();
    void shutdown();
    void update(float deltaTime);
    void draw();
    void tick(float deltaTime);
    void insertion_sort_tanks_health(const std::vector<Tank>& original, std::vector<const Tank*>& sorted_tanks, int begin, int end);
    void draw_health_bars(const std::vector<Tank*>& sorted_tanks, const int team);
    void measure_performance();

    Tank& find_closest_enemy(Tank& current_tank);

    void mouse_up(int button)
    { /* implement if you want to detect mouse button presses */
    }

    void mouse_down(int button)
    { /* implement if you want to detect mouse button presses */
    }

    void mouse_move(int x, int y)
    { /* implement if you want to detect mouse movement */
    }

    void key_up(int key)
    { /* implement if you want to handle keys */
    }

    void key_down(int key)
    { /* implement if you want to handle keys */
    }

private:
    int numThreads = std::thread::hardware_concurrency() * 2;

    std::unique_ptr<Grid> grid;

    Surface* screen;

    vector<Tank> tanks;
    vector<Tank*> Bluetanks;
    vector<Tank*> Redtanks;

    vector<Rocket> rockets;
    vector<Smoke> smokes;
    vector<Explosion> explosions;
    vector<Particle_beam> particle_beams;

    Terrain background_terrain;
    std::vector<vec2> forcefield_hull;

    Font* frame_count_font;
    long long frame_count = 0;


    bool lock_update = false;

    std::unique_ptr<BS::thread_pool> bsThreadPool;

    //Checks if a point lies on the left of an arbitrary angled line
    bool left_of_line(vec2 line_start, vec2 line_end, vec2 point);


    void processRocketUpdate(std::vector<Rocket>& pRockets);
    void processRocketConvex();
    void processGameTankNudging(std::vector<Tank>& pTanks);
    void processGameTankUpdate(std::vector<Tank*> to_update);
    void processLaserUpdate();
    void calcForcefield();

};

}; // namespace Tmpl8