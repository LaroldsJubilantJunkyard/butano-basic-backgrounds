#include <bn_core.h>
#include <bn_keypad.h>
#include <bn_vector.h>
#include <bn_regular_bg_ptr.h>
#include <bn_camera_ptr.h>
#include <bn_sprite_ptr.h>
#include "bn_regular_bg_items_water.h"
#include "bn_regular_bg_items_clouds.h"
#include "bn_regular_bg_items_ground.h"

// Vector from #include <bn_vector.h>
bn::vector<bn::regular_bg_ptr,3> vectorOfRegularBackgrounds;

// Optional is part of #include <bn_core.h>
bn::optional<bn::regular_bg_ptr> optionalGround;


int main()
{
    bn::core::init();

    {
        // The clouds background will only last inside of the this scope (defined by the curly brackets)
        bn::regular_bg_ptr clouds = bn::regular_bg_items::clouds.create_bg();

        // The water background will last until it's removed from the tree
        vectorOfRegularBackgrounds.push_back(bn::regular_bg_items::water.create_bg());

        // The ground background is optional, with it's value set it will last until we change that value or reset the optional
        optionalGround = bn::regular_bg_items::ground.create_bg();

        // Wait for a to be pressed
        while(!bn::keypad::a_pressed())bn::core::update();
    }

    // When this part of the code is reached, the clouds background has gone out of scope and will be removed
    while(true)
    {
        bn::core::update();

        
        // Wait for a to be pressed
        if(bn::keypad::a_pressed()){

            // This will remove the water background, whose pointer was in this vector
            vectorOfRegularBackgrounds.clear();
        }   

        
        // Wait for a to be pressed
        if(bn::keypad::b_pressed()){


            // This will remove the ground background, which was optional
            // Make sure to always test for an actual value
            if(optionalGround.has_value())optionalGround.reset();
        }   

    }
}