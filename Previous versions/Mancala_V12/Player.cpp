#include "Player.h"

Player::Player(string n) {
    data.username = n;
    data.win = 0;
    data.loss = 0;
}

void Player::setName(string n) {
    data.username = n;
}

void Player::setWin(int w) {
    data.win = w;
}

void Player::addWin() {
    data.win++;
}

void Player::setLoss(int l) {
    data.loss = l;
}

void Player::addLoss() {
    data.loss++;
}

void Player::setPoints(int p) {
    data.points = p;
}

string Player::getName() {
    return data.username;
}

int Player::getWin() {
    return data.win;
}

int Player::getLoss() {
    return data.loss;
}

int Player::getPoints() {
    return data.points;
}

void Player::print() {
    cout << "Name: " << data.username << endl;
    cout << "Wins: " << data.win << endl;
    cout << "Losses: " << data.loss << endl;
    cout << "Points: " << data.points << endl;
}
