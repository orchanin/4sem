//
//  MaterialPoint.hpp
//  bounces
//
//  Created by Евгений Дьячков on 17.03.17.
//  Copyright © 2017 Dyachkov. All rights reserved.
//

#ifndef MaterialPoint_hpp
#define MaterialPoint_hpp

#include <stdio.h>
#include "Vector2.hpp"
#endif /* MaterialPoint_hpp */

class MaterialPoint
{
public:
    
    Vector2 position;
    Vector2 velocity;
    
    float mass;
    
    
    void updatePosition(float dt);
    
};
