![title](https://github.com/narasu/kmgdev1_01/assets/58448900/175d68fa-91a8-4082-a452-1ee75a6e104c)

A simple game about **dodging** monsters and surviving as long as you can, made in C++ using the SFML library. Enemies spawn at the top of the screen and move down while you, the player, are at the bottom and need to avoid them by moving left and right. You gain points for each successfully dodged enemy. Get hit too many times and you die. The game increases in difficulty the further you progress. 

Here's how it works under the hood.
## Managers
While main.cpp doesn't do much more than initialize the window and draw sprites, the [GameManager][1] class handles most of the root game logic. It is essentially a finite state machine and aside from tracking score and difficulty stage, delegates all tasks to other managers. For example, the update loop of PlayState looks like this:

**GameManager::stateUpdate()**
```
if (state == PlayState) {
    if (entityManager->getPlayer().isDestroyed()) {
        switchState(LoseState);
        return;
    }

    spawner->update(stage, deltaTime.asSeconds(), entityManager->getPlayer().getPosition().x);
    if (spawner->isEnemySpawned()) {
        audioManager->playSound(EnemySpawnSound);
        spawner->spawnCallback();
    }

    // temp store pre-update player health
    int playerHealth = entityManager->getPlayer().getHealth();
    entityManager->updateAll(deltaTime.asSeconds());

    //if health has changed last update, update health UI
    if (playerHealth != entityManager->getPlayer().getHealth()) {
        interfaceManager->updateHealth(entityManager->getPlayer().getHealth());
    }

    if (entityManager->isPlayerHit()) {
        audioManager->playSound(PlayerHitSound);
        entityManager->playerHitCallback();
    }

    //if any enemies are below the bottom of the screen, increment the score and send the new value to UI
    int count = entityManager->getEnemyOutOfBoundsCount();
    if (count > 0) {
        score += SCORE_PER_ENEMY[stage] * static_cast<float>(count);
        interfaceManager->updateScore(score);

        if (stage < std::size(SCORE_THRESHOLD) && score >= SCORE_THRESHOLD.at(stage)) {
            switchState(StageUpState);
        }
    }
}
```
  
The [EntityManager][2] is what keeps track of all in-game objects (Entities). Its update loop makes sure each individual entity gets updated and deletes them when needed. Because each entity is a unique pointer, erasing them from the vectors is enough to unload them from memory. It also runs a collision check between the player and enemies. (How the calculations are done is detailed in the _Math_ section.)
```
void EntityManager::updateAll(float _delta) {
	enemyOutOfBoundsCount = 0;
    if (player!=nullptr) {
        player->update(_delta);
    }
	
    for(auto it = grass.begin(); it != grass.end();) {
        (*it)->update(_delta);

        if ((*it)->isDestroyed()) {
            it = grass.erase(it);
        }
        else {
            it++;
        }
    }

    for(auto it = enemies.begin(); it != enemies.end();) {
        (*it)->update(_delta);
        if ((*it)->isDestroyed()) {
            if ((*it)->isOutOfBounds()) {
                enemyOutOfBoundsCount+=1;
            }
            it = enemies.erase(it);
        }
        else {
            it++;
        }
    }
    checkCollisions();
}

void EntityManager::checkCollisions() {
    if (enemies.empty() || player==nullptr) {
        return;
    }

    for (const auto& e : enemies) {
        if (Rect<float>::isOverlapping(e->getBoundsGlobal(), player->getBoundsGlobal())) {
            playerHit = true;
            e->onCollision();
            player->onCollision();
        }
    }
}
```
  
Then there's a [Spawner][6] class which handles creating entities. It runs timers and spawns entities at set intervals. Spawning enemies, for example, looks like this:
```
void Spawner::update(int _stage, float _delta, float _playerX) {
    if (timerActive[EnemySpawn] && _playerX >= -1.0f) {
        time[EnemySpawn] += _delta;
        if (intervalReached(EnemySpawn)) {
            spawnEnemy(_stage, 1, _playerX);
        }
    }
	[...]
}

void Spawner::spawnEnemy(int _stage, int _count, float _playerX) {
    while (_count > 0) {
        auto randomPosition = generateRandomPosition(lastSpawn[EnemySpawn], 15.0f);

        // chance that the enemy will spawn directly above the player, never twice in a row
        if (!biasTriggered) {
            int randomChance = rand() % 100;
            if (randomChance > 40) {
                randomPosition = _playerX;
                biasTriggered = true;
            }
        }
        else {
            biasTriggered = false;
        }

        // get random texture, never the same twice
        int random123 = rand() % 3 + 1;
        if (lastEnemy != 0) {
            while (random123 == lastEnemy) {
                random123 = rand() % 3 + 1;
            }
        }

        lastEnemy = random123;
        std::string randomEnemy = "enemy0" + std::to_string(random123);

        entityManager->addEnemy(
                std::make_unique<Enemy>(
                        *textureManager->getTexture(randomEnemy),
                        randomPosition,
                        static_cast<float>(HUD_HEIGHT),
                        BOUNDS.at(randomEnemy),
                        ENEMY_FORCE_Y[_stage])
        );
        _count--;
    }
    enemySpawned = true;
}
```
  
There's an [InterfaceManager][3] for UI and an [AudioManager][4] for sounds, and finally the [TextureManager][5] manages all textures.
## Entities
All non-UI objects in the game are derived from the [BaseEntity][7] class, which initializes a Sprite and specifies a pure virtual update method. Derived from that is a [PhysicsEntity][8] which initializes a rigidbody, implements the update method and specifies a pure virtual onCollision method. Its implementation of update looks like this:
```
void PhysicsEntity::update(float _delta) {
    rigidbody->applyFriction();
    position += rigidbody->getVelocity() * _delta;

    //reset velocity to 0 if its magnitude is below 0.01
    if (rigidbody->getVelocity().sqrMagnitude() < 0.0001f) {
        rigidbody->setVelocity(V2_ZERO<float>);
    }

    // round to whole numbers to prevent sub-pixel rendering
    sprite->setPosition(roundf(position.x), roundf(position.y));
}
```
  
It is then up to classes derived from PhysicsEntity to define when forces are applied, and how to behave on collision. The [Player][9] class, for example:
```
void Player::update(float _delta) {
    float direction = 0;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        direction-=1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        direction+=1;
    }

    //prevent player moving off screen
    if (rigidbody->getVelocity().x < 0 && position.x <= 0) {
        rigidbody->setVelocity(V2_ZERO<float>);
        position.x=0;
    }
    else if (rigidbody->getVelocity().x > 0 && position.x >= VIEWPORT_WIDTH - bounds.w) {
        rigidbody->setVelocity(V2_ZERO<float>);
        position.x= VIEWPORT_WIDTH - bounds.w;
    }
    rigidbody->addForce(moveSpeed * direction, .0f);
    PhysicsEntity::update(_delta);
}

void Player::onCollision() {
    health--;
    if (health <= 0) {
        destroyed = true;
    }
}
```
How forces are calculated in the rigidbody is detailed in the next section.  

## Math
For this game (as per the specification of the assignment) I wrote some custom math classes. Most essential is [Vector2][10]. It's a template class which stores any type of number as x and y. Any non-ambiguous operation is defined in an operator overload. 
```
Vector2<T>& operator=(const Vector2<T>& _rhVector2) {
	x = _rhVector2.x;
	y = _rhVector2.y;
	return *this;
}

bool operator==(const Vector2<T> &_rhVector2) { return x == _rhVector2.x && y == _rhVector2.y; }

bool operator!=(const Vector2<T> &_rhVector2) { return x != _rhVector2.x || y != _rhVector2.y; }

Vector2 operator+(const Vector2& _rhVector2) { return Vector2<T>(x+_rhVector2.x, y+_rhVector2.y); }

Vector2& operator+=(const Vector2& _rhVector2) {
	x += _rhVector2.x;
	y += _rhVector2.y;
	return *this;
}

Vector2<T> operator-() { return Vector2<T>(-x, -y); }

Vector2 operator-(const Vector2& _rhVector2) { return Vector2(x-_rhVector2.x, y-_rhVector2.y); }

Vector2& operator-=(const Vector2& _rhVector2) {
	x -= _rhVector2.x;
	y -= _rhVector2.y;
	return *this;
}

Vector2 operator*(const T& _rhScalar) { return Vector2(x*_rhScalar, y*_rhScalar); }

Vector2& operator*=(const T& _rhScalar) {
	x *= _rhScalar;
	y *= _rhScalar;
	return *this;
}

Vector2 operator/(const T& _rhScalar) { return Vector2(x/_rhScalar, y/_rhScalar); }

Vector2& operator/=(const T& _rhScalar) {
	x /= _rhScalar;
	y /= _rhScalar;
	return *this;
}
```
There are also some helpful methods for running various calculations. I've written more than I ended up using, but here are the important ones:
```
T sqrMagnitude() {
	return x*x + y*y;
}

T magnitude() {
	return sqrt(sqrMagnitude());
}

Vector2<T> normalized() {
	static_assert(std::is_floating_point_v<T>);
	return Vector2<T>(x / magnitude(), y / magnitude());
}
```
A [Rect][11] class whose most important task is checking for collisions:
```
static bool isOverlapping(const Rect<T> &_rectA, const Rect<T> &_rectB) {
	return
		_rectA.x < _rectB.x + _rectB.w &&
		_rectA.x + _rectA.w > _rectB.x &&
		_rectA.y < _rectB.y + _rectB.h &&
		_rectA.h + _rectA.y > _rectB.y;
}
```
And finally, a [Rigidbody][12] which is required by the PhysicsEntity class and handles velocity calculations.
```
void Rigidbody::addForce(Vector2<float> _force) {
	friction = _force.sqrMagnitude() > 0 ? _force.magnitude() : friction;
	velocity += _force / mass;
}
void Rigidbody::addForce(float _forceX, float _forceY) {
	addForce(Vector2<float>(_forceX, _forceY));
}

void Rigidbody::applyFriction() {
	if (friction == .0f) {
		return;
	}
	Vector2<float> oppositeDirection = -(velocity.normalized());
	Vector2<float> f;
	if (pow(friction, 2) <= velocity.sqrMagnitude()) {
		f = oppositeDirection * friction;
	}
	else {
		f = -velocity;
	}
	addForce(f * frictionMult);
}
```

## License
All art and audio in the game, as well as all code hosted on this repository, are custom-made and free to use under the MIT license.

## Sources & Credits
[SFML Documentation](https://www.sfml-dev.org/documentation/2.5.1/index.php)  
[FindSFML CMake file](https://github.com/CaffeinatedTech/nibbles/blob/main/nibbles-01/cmake_modules/FindSFML.cmake)  
[Generics in C++](https://www.geeksforgeeks.org/generics-in-c/)  
Ponderosa font by [Tepid Monkey](https://www.1001fonts.com/users/tepidmonkey/)  
EDG-8 color palette by [Endesga](https://twitter.com/ENDESGA)  
  
Tools used:  
CLion  
SFML 2.5.1  
Aseprite  
Beepbox  
SFXR  

[1]: https://github.com/narasu/kmgdev1_01/blob/master/src/managers/GameManager.h
[2]: https://github.com/narasu/kmgdev1_01/blob/master/src/managers/EntityManager.h
[3]: https://github.com/narasu/kmgdev1_01/blob/master/src/managers/InterfaceManager.h
[4]: https://github.com/narasu/kmgdev1_01/blob/master/src/managers/AudioManager.h
[5]: https://github.com/narasu/kmgdev1_01/blob/master/src/managers/TextureManager.h
[6]: https://github.com/narasu/kmgdev1_01/blob/master/src/spawner/Spawner.h
[7]: https://github.com/narasu/kmgdev1_01/blob/master/src/entity/BaseEntity.h
[8]: https://github.com/narasu/kmgdev1_01/blob/master/src/entity/PhysicsEntity.h
[9]: https://github.com/narasu/kmgdev1_01/blob/master/src/entity/Player.h
[10]: https://github.com/narasu/kmgdev1_01/blob/master/src/hiro/Vector2.h
[11]: https://github.com/narasu/kmgdev1_01/blob/master/src/hiro/Rect.h
[12]: https://github.com/narasu/kmgdev1_01/blob/master/src/hiro/Rigidbody.h
