#pragma once

class Player {
private:
	int PlayerScore;
	int PlayerBestScore;
	char *PlayerName;
public:
	Player();
	~Player();

	void setPlayerName(char *PlayerName) { this->PlayerName = PlayerName; }
	char *getPlayerName() { return PlayerName; }

	void setPlayerScore(int PlayerScore) { this->PlayerScore = PlayerScore; }
	int getPlayerScore() { return PlayerScore; }

	void setPlayerBestScore(int PlayerBestScore) { this->PlayerBestScore = PlayerBestScore; }
	int getPlayerBestScore() { return PlayerBestScore; }
};
