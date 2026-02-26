#ifndef ORBITER_H
#define ORBITER_H

#include <bn_fixed_point.h>
#include <bn_sprite_ptr.h>

#include "Center.h"
#include "movement.h"
#include "bn_sprite_items_dot.h"

// A scaling factor by which to reduce the force applied when orbiting
// Important for numerical stability
static constexpr bn::fixed FORCE_SCALE = 10;

/**
 * An object that orbits around a center. Orbits using Hooke's law, as if attached by a 2D spring.
 * The stiffness of the spring in each dimension is center.mass() / FORCE_SCALE. 
 */
class Orbiter {
    public:
        /**
         * Creates an orbiter.
         * 
         * @param starting_location the initial location of the Orbiter
         * @param starting_velocity the initial velocity of the Orbiter, {dx, dy}
         * @param center the center to orbit around
         */
        Orbiter(bn::fixed_point starting_location, bn::fixed_point starting_velocity, Center &center);

        /**
         * Take a step orbiting around the center.
         */
        void update() {
            // A vector from the Orbiter to the Center
            bn::fixed_point delta = _center.position() - _sprite.position();

            // Scale the vector by the mass and apply a FORCE_SCALE
            // This is done in two steps instead of having a pre-scaled mass to prevent loss of
            // fixed point precision
            bn::fixed_point force = delta * _center.mass();
            force /= FORCE_SCALE;

            // Update the current velocity with the force
            _velocity += force;

            // Update the position by taking a step by the velocity vector
            _sprite.set_position(_sprite.position() + _velocity);
        }

    private:
        bn::sprite_ptr _sprite;
        bn::fixed_point _velocity;
        Center& _center;
};

#endif