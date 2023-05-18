//
// Created by Yamada on 18-5-2023.
//

#include <iostream>
#include "Player.h"

Player::Player() : Entity() {

}

Player::~Player() {
    std::cout << "Player destructor" << std::endl;
}
