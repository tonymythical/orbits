#include "orbiter.h"

Orbiter::Orbiter(bn::fixed_point starting_location, bn::fixed_point starting_velocity, Center &center) :
        _sprite(bn::sprite_items::dot.create_sprite(starting_location)),
        _velocity(starting_velocity),
        _center(center) {
}