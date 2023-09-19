#include <SFML/Graphics.hpp>

using namespace sf;

const int WIDTH = 93;
const int HEIGHT = 27;
int count = 226;

String TileMap[HEIGHT] = {
	"                                                                                             ",
	"                                                                                             ",
	"  0  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0   ",
	"                                                                                             ",
	"  0     0               0                        0              0     0         0         0  ",
	"                                                                                             ",
	"  0 1   0               0 0 0 0 0 0 0 0 0 0 0 0  0 0 0 0 0 0 0  0     0 0 0 0  0 0 0 0 03    ",
	"                                                                                             ",
	"        0      0 0 0 0  0            0           0              0     0            0         ",
	"                                                                                             ",
	"        0      0        0            0           0              0     0            0         ",
	"                                                                                             ",
	"        0               0            0           0              0     0            0         ",
	"- 0 0 0        0 0                                                                   0 0 0  +",
	"        0               0            0           0              0     0       0 0  0         ",
	"                                                                                             ",
	"        0               0            0           0 0 0 0 0 0 0  0     0            0         ",
	"                                                                                             ",
	"        0               0            0                                0            0         ",
	"  2                                                                                     4    ",
	"      0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0  0              0 0 0 0 0 0 0 0 0 0 0 0      ",
	"                                                                                             ",
	"  0      0                 0    0                0    0    0 0  0               0            ",
	"                                                                                             ",
	"  0 0 0 0 0 0 0 0 0 0 0 0  0    0 0 0 0 0 0 0 0  0    0 0  0    0 0 0 0 0 0 0 0 0 0 0 0  0   ",
	"                                                                                             ",
	"                                                                                             ",
};

class Blocks {
public:
	Blocks(int x, int y, int weight, int height) {
		this->x = x;
		this->y = y;
		this->weight = weight;
		this->height = height;
	}
	int GetX() {
		return x;
	}
	int GetY() {
		return y;
	}
	int GetW() {
		return weight;
	}
	int GetH() {
		return height;
	}
private:
	int x;
	int y;
	int weight;
	int height;
};

const int LENGTH = 41;

Blocks part[41] = {
	Blocks(3, 0, 462, 4),
	Blocks(3, 3, 2, 46),
	Blocks(462, 5, 4, 45),
	Blocks(21, 20, 15, 8),
	Blocks(133, 20, 112, 8),
	Blocks(261, 20, 57, 8),
	Blocks(365, 20, 32, 8),
	Blocks(413, 20, 32, 8),
	Blocks(53, 20, 63, 16),
	Blocks(53, 36, 15, 57),
	Blocks(69, 77, 47, 16),
	Blocks(100, 52, 16, 26),
	Blocks(86, 52, 15, 8),
	Blocks(133, 44, 47, 49),
	Blocks(198, 44, 47, 49),
	Blocks(261, 44, 18, 4),
	Blocks(261, 49, 3, 27),
	Blocks(265, 73, 53, 3),
	Blocks(300, 44, 18, 4),
	Blocks(314, 49, 4, 24),
	Blocks(334, 20, 15, 73),
	Blocks(365, 45, 48, 23),
	Blocks(365, 68, 17, 25),
	Blocks(382, 84, 31, 9),
	Blocks(2, 44, 34, 16),
	Blocks(429, 45, 37, 16),
	Blocks(2, 77, 34, 16),
	Blocks(429, 77, 37, 16),
	Blocks(22, 109, 23, 8),
	Blocks(61, 109, 71, 8),
	Blocks(150, 109, 7, 24),
	Blocks(174, 109, 71, 8),
	Blocks(261, 117, 7, 16),
	Blocks(261, 93, 57, 7),
	Blocks(286, 100, 7, 16),
	Blocks(310, 117, 8, 16),
	Blocks(334, 109, 63, 8),
	Blocks(414, 109, 29, 8),
	Blocks(2, 92, 3, 44),
	Blocks(461, 92, 4, 44),
	Blocks(5, 133, 460, 2)
};