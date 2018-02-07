#define _USE_MATH_DEFINES

#include <map>
#include <string>
#include <vector>
#include "game.h"

using namespace std;

void game::addPlayer(int id, string _name) {
	player toAdd;
	toAdd.name = _name;
	toAdd.position = 0;
	toAdd.score = 0;
	players[id] = toAdd;
}

void game::removePlayer(int id) {
	this->players.erase(id);
}

void game::updateBall() {
	this->ballPos.x += cos(this->ballDirection * M_PI / 180);
	this->ballPos.y += sin(this->ballDirection * M_PI / 180);
	if (this->ballPos.y > 1 || this->ballPos.y < -1) {
		flipBallVertical();
	}
	if (this->ballPos.x > 1 || this->ballPos.x < -1) {
		flipBallHorizontal();
	}
}

void game::changeScore(int index, int toAdd) {
	this->players[index].score += toAdd;
	if (this->players[index].score >= this->maxScore) {
		this->stopGame();
	}
}

void game::stopGame() {
	for (map<int,player>::iterator it = this->players.begin(); it != this->players.end(); ++it) {
		it->second.score = 0;
		it->second.position = 0;
	}
	ballPos.x = 0;
	ballPos.y = 0;
}

void game::flipBallVertical() {
	ballDirection = (ballDirection * -1) % 360;
}

void game::flipBallHorizontal() {
	ballDirection = (180 - ballDirection) % 360;
}