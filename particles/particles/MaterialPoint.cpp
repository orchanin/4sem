//
//  MaterialPoint.cpp
//  bounces
//
//  Created by Евгений Дьячков on 17.03.17.
//  Copyright © 2017 Dyachkov. All rights reserved.
//

#include "MaterialPoint.hpp"





void MaterialPoint::updatePosition(float dt){
    this->position += this->velocity * dt;
}

