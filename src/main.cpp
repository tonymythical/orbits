#include <bn_core.h>
#include <bn_keypad.h>
#include <bn_vector.h>

#include "Center.h"
#include "orbiter.h"

// Maximum number of orbiters allowed on the screen
static constexpr int MAX_ORBITERS = 30;

// Default starting position and velocity for Orbiter || Changed to variables instead of constexpr
bn::fixed_point ORBITER_START_POSIITON = {0, 0};
bn::fixed_point ORBITER_START_VELOCITY = {0, 1};

int main() {
    bn::core::init();

    Center center = Center({30, 40}, .05, 2);
    bn::vector<Orbiter, MAX_ORBITERS> orbiters = {};
    
    while(true) {

        // The orbiters now spawn with the position of the player
        if(bn::keypad::left_held())  { ORBITER_START_POSIITON.set_x(ORBITER_START_POSIITON.x() - 1); }
        if(bn::keypad::right_held()) { ORBITER_START_POSIITON.set_x(ORBITER_START_POSIITON.x() + 1); }
        if(bn::keypad::up_held())    { ORBITER_START_POSIITON.set_y(ORBITER_START_POSIITON.y() - 1); }
        if(bn::keypad::down_held())  { ORBITER_START_POSIITON.set_y(ORBITER_START_POSIITON.y() + 1); }

        // Add an orbiter when A is pressed if there's room
        if(bn::keypad::a_pressed()) {
            if(orbiters.size() < MAX_ORBITERS) {
                orbiters.push_back(Orbiter(ORBITER_START_POSIITON, ORBITER_START_VELOCITY, center));
            }
        }

        // Remove an orbiter when B is pressed if there's at least one
        if (bn::keypad::b_pressed()) {
            if(orbiters.size() > 0) {
                orbiters.pop_back();
            }
        }

        center.update();
        for(Orbiter& orbiter : orbiters) {
            orbiter.update();
        }

        bn::core::update();
    }
}