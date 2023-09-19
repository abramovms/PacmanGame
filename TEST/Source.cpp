#include <SFML/Graphics.hpp>
#include "map.h"
#include <cmath>
#include <ctime>


using namespace sf;

bool game = true;
bool resize = true;

class Entity {
public:
    Entity(Image &image, float X, float Y, float W, float H) {
        x = X;
        y = Y;
        weight = W;
        height = H;
        dx = 0, dy = 0;
        speed = 0.02;
        CurrentFrame = 0;
        life = true;
        dir = 1, d = 1;
        texture.loadFromImage(image);
        sprite.setTexture(texture);
    }
    Sprite& GetSprite() {
        return sprite;
    }
    void CheckCollision(float time) {
        float X = x + weight - 1;
        float Y = y + height - 1;
        switch (dir) {
        case 0:
            for (int i = x; i < x + weight; i++) {
                for (int j = 0; j < LENGTH; j++) {
                    if ((i >= part[j].GetX() && i <= part[j].GetX() + part[j].GetW() - 1) && (y - 1 >= part[j].GetY() && y - 1 <= part[j].GetY() + part[j].GetH() - 1)) {
                        y -= dy * time;
                        return;
                    }
                }
            }
            break;
        case 1:
            for (int i = y; i < y + height; i++) {
                for (int j = 0; j < LENGTH; j++) {
                    if ((X + 1 >= part[j].GetX() && X + 1 <= part[j].GetX() + part[j].GetW() - 1) && (i >= part[j].GetY() && i <= part[j].GetY() + part[j].GetH() - 1)) {
                        x -= dx * time;
                        return;
                    }
                }
            }
            break;
        case 2:
            for (int i = x; i < x + weight; i++) {
                for (int j = 0; j < LENGTH; j++) {
                    if ((i >= part[j].GetX() && i <= part[j].GetX() + part[j].GetW() - 1) && (Y + 1 >= part[j].GetY() && Y + 1 <= part[j].GetY() + part[j].GetH() - 1)) {
                        y -= dy * time;
                        return;
                    }
                }
            }
            break;
        case 3:
            for (int i = y; i < y + height; i++) {
                for (int j = 0; j < LENGTH; j++) {
                    if ((x - 1 >= part[j].GetX() && x - 1 <= part[j].GetX() + part[j].GetW() - 1) && (i >= part[j].GetY() && i <= part[j].GetY() + part[j].GetH() - 1)) {
                        x -= dx * time;
                        return;
                    }
                }
            }
            break;
        }
    }
    bool checkside() {
        float X = x + weight - 1;
        float Y = y + height - 1;
        switch (d) {
        case 0:
            for (int i = x; i < x + weight; i++) {
                for (int j = 0; j < LENGTH; j++) {
                    for (int v = 1; v <= 4; v++) {
                        if ((i >= part[j].GetX() && i <= part[j].GetX() + part[j].GetW() - 1) && (y - v >= part[j].GetY() && y - v <= part[j].GetY() + part[j].GetH() - 1)) {
                            return false;
                        }
                    }
                }
            }
            break;
        case 1:
            for (int i = y; i < y + height; i++) {
                for (int j = 0; j < LENGTH; j++) {
                    for (int v = 1; v <= 4; v++) {
                        if ((X + v >= part[j].GetX() && X + v <= part[j].GetX() + part[j].GetW() - 1) && (i >= part[j].GetY() && i <= part[j].GetY() + part[j].GetH() - 1)) {
                            return false;
                        }
                    }
                }
            }
            break;
        case 2:
            for (int i = x; i < x + weight; i++) {
                for (int j = 0; j < LENGTH; j++) {
                    for (int v = 1; v <= 4; v++) {
                        if ((i >= part[j].GetX() && i <= part[j].GetX() + part[j].GetW() - 1) && (Y + v >= part[j].GetY() && Y + v <= part[j].GetY() + part[j].GetH() - 1)) {
                            return false;
                        }
                    }
                }
            }
            break;
        case 3:
            for (int i = y; i < y + height; i++) {
                for (int j = 0; j < LENGTH; j++) {
                    for (int v = 1; v <= 4; v++) {
                        if ((x - v >= part[j].GetX() && x - v <= part[j].GetX() + part[j].GetW() - 1) && (i >= part[j].GetY() && i <= part[j].GetY() + part[j].GetH() - 1)) {
                            return false;
                        }
                    }
                }
            }
        }
        return true;
    }
    void teleport() {
        for (int i = (y + 5) / 5; i < (y + height - 4) / 5; i++) {
            for (int j = (x + 5) / 5; j < (x + weight - 4) / 5; j++) {
                if (TileMap[i][j] == '-') {
                    x = 440;
                    y = 61;
                    d = 3;
                    dir = d;
                    break;
                }
                if (TileMap[i][j] == '+') {
                    x = 10;
                    y = 61;
                    d = 1;
                    dir = d;
                    break;
                }
            }
        }
    }
    bool& GetLife() {
        return life;
    }
    int GetDir() {
        return dir;
    }
protected:
    float x, y, weight, height, dx, dy, speed;
    float CurrentFrame;
    int dir, d;
    bool life;
    Texture texture;
    Sprite sprite;
};

class NPC : public Entity {
public:
    NPC(Image& image, float X, float Y, float W, float H, int name) : Entity(image, X, Y, W, H) {
        x1 = x, y1 = y;
        dir = 0, d = 0;
        timer = 0, timelife = 0;
        this->name = name;
        sprite.setTextureRect(IntRect(1, 82 + 20 * name, weight, height));
    }
    bool Collision(float X, float Y) {
        for (int i = y + 3; i < y + height - 2; i++) {
            if (i != y + 3 && i != y + height - 3) {
                if ((x + 3 > X && x + 3 < X + weight - 1) && (i > Y && i < Y + height - 1)) return true;
                if ((x + weight - 2 > X && x + weight - 2 < X + weight - 1) && (i > Y && i < Y + height - 1)) return true;
            }
            else {
                for (int j = x + 3; j < x + weight - 2; j++) {
                    if ((j > X && j < X + weight - 1) && (i > Y && i < Y + height - 1)) return true;
                }
            }
        }
        return false;
    }
    void Animation(float time) {
        CurrentFrame += 0.005 * time;
        if (CurrentFrame > 2) CurrentFrame -= 2;
        if (life) {
            switch (dir) {
            case 0: 
                sprite.setTextureRect(IntRect(1 + (weight + 6) * (int)(CurrentFrame), 82 + 20 * name, weight, height));
                break;
            case 1:
                sprite.setTextureRect(IntRect(121 + (weight + 6) * (int)(CurrentFrame), 82 + 20 * name, weight, height));
                break;
            case 2:
                sprite.setTextureRect(IntRect(41 + (weight + 6) * (int)(CurrentFrame), 82 + 20 * name, weight, height));
                break;
            case 3:
                sprite.setTextureRect(IntRect(81 + (weight + 6) * (int)(CurrentFrame), 82 + 20 * name, weight, height));
                break;
            }
        }
        else {
            sprite.setTextureRect(IntRect(2 + (weight + 6) * (int)(CurrentFrame), 162, weight, height));
        }
    }
    bool check() {
        if ((y + height - 1 + 5 >= 45 && y + height - 1 + 5 < 75) && (x >= 261 && x < 316)) return true;
        return false;
    }
    bool checkspawn() {
        if ((y + height - 1 >= 43 && y + height < 75) && (x > 261 && x < 316)) return true;
        return false;
    }
    void control(float X, float Y, float time, int dr) {
        timer += 0.005 * time;
        if (timer > 10) timer = 0;
        if (!life) {
            if (abs(X - x) <= 5 || abs(Y - y) <= 5) {
                if (abs(dir - dr) == 2) {
                    dir = d = dr;
                    timer = 0;
                    return;
                }
            }
        }
        if (checkspawn()) {
            timer = 0;
            d = 0;
            dir = d;
            return;
        }
        if (x1 == x && y1 == y) {
            timer = 0;
            while (!checkside()) d = rand() % 4;
            if (abs(dir - d) == 2) {
                int d1 = d, d2 = d;
                while (d == d1 || d == dir) d = rand() % 4;
                if (checkside()) {
                    dir = d;
                    return;
                }
                d2 = d;
                while ((d == d1) || (d == d2) || (d == dir)) d = rand() % 4;
                if (checkside()) {
                    dir = d;
                    return;
                }
                d = d1;
                dir = d;
                return;
            }
            dir = d;
            return;
        }
        if (d != dir && checkside() && timer <= 7) {
            if (d == 2) {
                if (!check()) dir = d;
                else {
                    if (dir == d + 1) {
                        d++;
                        dir = d;
                    }
                    else {
                        d--;
                        dir = d;
                    }
                }
            }
            else {
                dir = d;
            }
        }
        else if (timer > 7) {
            while (d == dir || abs(d - dir) == 2) d = rand() % 4;
            if (checkside()) {
                timer = 0;
                if (d == 2) {
                    if (!check()) dir = d;
                    else {
                        if (dir == d + 1) {
                            d++;
                            dir = d;
                        }
                        else {
                            d--;
                            dir = d;
                        }
                    }
                }
                else {
                    dir = d;
                }
            } 
        }
    }
    void update(float X, float Y, bool &Life, float time, int dr) {
        if (!life) {
            speed = 0.01;
            timelife += 0.005 * time;
            if (timelife > 20) {
                speed = 0.02;
                timelife = 0;
                life = true;
            }
        }
        teleport();
        Animation(time);
        control(X, Y, time, dr);
        x1 = x, y1 = y;
        switch (dir) {
        case 0: dx = 0; dy = -speed; break;
        case 1: dx = speed; dy = 0; break;
        case 2: dx = 0; dy = speed; break;
        case 3: dx = -speed; dy = 0; break;
        }
        x += dx * time;
        y += dy * time;
        CheckCollision(time);
        if (Collision(X, Y)) {
            if (!life) {
                x = 280;
                y = 55;
                life = true;
                speed = 0.02;
                timelife = 0;
            }
            else {
                Life = false;
            }
        }
        sprite.setPosition(x, y);
    }
private:
    float x1, y1;
    float timer;
    float timelife;
    int name;
};

class Player : public Entity {
public:
    Player(Image& image, float X, float Y, float W, float H) : Entity(image, X, Y, W, H) {
        LifeGhost = true;
        CurrentLframe = 0;
        d = 1;
        sprite.setTextureRect(IntRect(1, 22, weight, height));
    }

    void Animation(float time) {
        CurrentFrame += 0.005 * time;
        if (CurrentFrame > 2) CurrentFrame -= 2;
        switch (dir) {
        case 0: sprite.setTextureRect(IntRect(2 + (5 + weight) * (int)(CurrentFrame), 42, weight, height)); break;
        case 1: sprite.setTextureRect(IntRect(2 + (5 + weight) * (int)(CurrentFrame), 22, weight, height)); break;
        case 2: sprite.setTextureRect(IntRect(2 + (5 + weight) * (int)(CurrentFrame), 61, weight, height)); break;
        case 3: sprite.setTextureRect(IntRect(2 + (5 + weight) * (int)(CurrentFrame), 2, weight, height)); break;
        }
    }

    void control() {
        if (Keyboard::isKeyPressed(Keyboard::W) || Keyboard::isKeyPressed(Keyboard::Up)) {
            d = 0;
        }
        if (Keyboard::isKeyPressed(Keyboard::D) || Keyboard::isKeyPressed(Keyboard::Right)) {
            d = 1;
        }
        if (Keyboard::isKeyPressed(Keyboard::S) || Keyboard::isKeyPressed(Keyboard::Down)) {
            d = 2;
        }
        if (Keyboard::isKeyPressed(Keyboard::A) || Keyboard::isKeyPressed(Keyboard::Left)) {
            d = 3;
        }
        if (Entity::checkside()) dir = d;
    }

    void update(float time) {
        for (int i = (y + 3) / 5; i < (y + height - 2) / 5; i++) {
            for (int j = (x + 3) / 5; j < (x + weight - 2) / 5; j++) {
                if (TileMap[i][j] == '0') {
                    count--;
                    TileMap[i][j] = ' ';
                    break;
                }
            }
        }

        teleport();

        for (int i = y / 5; i < (y + height) / 5; i++) {
            for (int j = (x - 5) / 5; j < (x + weight) / 5; j++) {
                if (TileMap[i][j] == '1') {
                    LifeGhost = false;
                    TileMap[i][j] = ' ';
                    break;
                }
                if (TileMap[i][j] == '2') {
                    LifeGhost = false;
                    TileMap[i][j] = ' ';
                    break;
                }
                if (TileMap[i][j] == '3') {
                    LifeGhost = false;
                    TileMap[i][j] = ' ';
                    break;
                }
                if (TileMap[i][j] == '4') {
                    LifeGhost = false;
                    TileMap[i][j] = ' ';
                    break;
                }
            }
        }

        control();
        switch (dir) {
        case 0: dx = 0; dy = -speed; break;
        case 1: dx = speed; dy = 0; break;
        case 2: dx = 0; dy = speed; break;
        case 3: dx = -speed; dy = 0; break;
        }
        Animation(time);
        x += dx * time;
        y += dy * time;
        CheckCollision(time);

        sprite.setPosition(x, y);
    }
    void game_over(float time) {
        CurrentLframe += 0.005 * time;
        if (CurrentLframe > 11) {
            game = false;
            return;
        }
        sprite.setTextureRect(IntRect(1 + (5 + 15) * (int)(CurrentLframe), 245, 15, 8));
    }
    int GetX() {
        return x;
    }
    int GetY() {
        return y;
    }
    bool& GetLifeGhost() {
        return LifeGhost;
    }
private:
    bool LifeGhost;
    float CurrentLframe;
};

int main() {

    RenderWindow window(VideoMode(465, 135), "Test");

    Image image;
    image.loadFromFile("Image/pacman.png");


    Image map;
    map.loadFromFile("Image/pacman.png");
    Texture t_map;
    t_map.loadFromImage(map);
    Sprite s_map;
    s_map.setTexture(t_map);
    s_map.setTextureRect(IntRect(321, 1, 465, 135));

    Sprite fruits;
    fruits.setTexture(t_map);

    Sprite gameover;
    gameover.setTexture(t_map);
    gameover.setTextureRect(IntRect(10, 190, 82, 10));
    gameover.setPosition(180, 35);

    NPC ghost[4] = {
        NPC(image, 280, 55, 15, 15, 0),
        NPC(image, 285, 55, 15, 15, 1),
        NPC(image, 280, 55, 15, 15, 2),
        NPC(image, 285, 55, 15, 15, 3),
    };

    Player pacman(image, 74, 94, 15, 15);

    srand(time(NULL));

    Clock clock;

    while (window.isOpen()) {

        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time /= 800;


        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) window.close();
        }

        window.clear();

        window.draw(s_map);


        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++) {
                if (TileMap[i][j] == '0') {
                    CircleShape yellow(2.f);
                    yellow.setFillColor(Color(255, 255, 0));
                    yellow.move(j * 5, i * 5);
                    window.draw(yellow);
                }
                if (TileMap[i][j] == '1') {
                    fruits.setTextureRect(IntRect(170, 163, 14, 12));
                    fruits.setPosition(j * 5, i * 5);
                    window.draw(fruits);
                }
                if (TileMap[i][j] == '2') {
                    fruits.setTextureRect(IntRect(170, 184, 14, 12));
                    fruits.setPosition(j * 5, i * 5);
                    window.draw(fruits);
                }
                if (TileMap[i][j] == '3') {
                    fruits.setTextureRect(IntRect(170, 203, 14, 12));
                    fruits.setPosition(j * 5, i * 5);
                    window.draw(fruits);
                }
                if (TileMap[i][j] == '4') {
                    fruits.setTextureRect(IntRect(170, 223, 14, 12));
                    fruits.setPosition(j * 5, i * 5);
                    window.draw(fruits);
                }
            }
        }

        if (count == 0) {
            for (int i = 0; i < 4; i++) {
                window.draw(ghost[i].GetSprite());
            }
            window.draw(pacman.GetSprite());

        }
        else {
            if (pacman.GetLife()) {
                for (int i = 0; i < 4; i++) {
                    ghost[i].update(pacman.GetX(), pacman.GetY(), pacman.GetLife(), time, pacman.GetDir());
                    window.draw(ghost[i].GetSprite());
                }

                pacman.update(time);

                if (!pacman.GetLifeGhost()) {
                    for (int i = 0; i < 4; i++) {
                        ghost[i].GetLife() = false;
                    }
                    pacman.GetLifeGhost() = true;
                }

                window.draw(pacman.GetSprite());

            }
            else {
                for (int i = 0; i < 4; i++) {
                    window.draw(ghost[i].GetSprite());
                }
                if (game) {
                    pacman.game_over(time);
                    window.draw(pacman.GetSprite());
                }
                else {
                    window.draw(gameover);
                }
            }
        }

        window.display();
    }

    return 0;
}