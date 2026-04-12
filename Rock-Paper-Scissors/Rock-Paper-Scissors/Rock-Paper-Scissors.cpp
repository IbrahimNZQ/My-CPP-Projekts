#include<iostream>
#include<cstdlib>
#include <chrono>
#include <thread> 
using namespace std;
using namespace this_thread;
using namespace chrono;

enum enWinnerNumber {
	Player1 = 1, Computer = 2, NoWinner = 3
};
enum enGameChoice {
	Stone = 1, Paper = 2, Scissors = 3
};
struct stGameInfo {
	short hawManyRounds = 0;
	short player1WonTimes = 0;
	short PcWonTimes = 0;
	short drawTimes = 0;
	enWinnerNumber gameWinnerNumber;
	string winnerName;
};
struct stRoundInfo {
	enGameChoice playerChoice;
	enGameChoice computerChoice;
	short roundNumber=0;
	enWinnerNumber winnerNumber;
	string winnerName;
};

short readPositiveNum() {
	int number = 0;
	cout << "For how many raouds will be the game?" << endl;
	cout << "Answer: ";
	cin >> number;
	return number;
}
string taps(int tapsNumber) {
	string tabs = "";
	for (int i = 0; i < tapsNumber; i++) {
		tabs += "\t";
	}
	return tabs;
}
string lines(int linesNumber) {
	string lines = "";
	for (int i = 0; i < linesNumber; i++) {
		lines += "\n";
	}
	return lines;
}

void screenLigth(int winner) {
	if (winner == enWinnerNumber::Player1) system("color 2F");
	else if (winner == enWinnerNumber::Computer) system("color 4F");
	else system("color 6F");
}
void resetScreen() {
	system("cls");
	system("color 0F");
}

string returnWinnerName(int numberWinner) {
	string names[] = { "Player1","Computer","No Winner" };
	return names[numberWinner - 1];
}
string returnChoiceName(int numberChoice) {
	string choices[] = { "Stone","Paper","Scissors" };
	return choices[numberChoice - 1];
}

enGameChoice readPlayerChoice() {
	short choice = 0;

	do {
		cout << "\nYour Choice: [1]:Stone, [2]:Paper, [3]:Scissors ?";
		cout << "\nAnswer: ";
		cin >> choice;
	} while (choice<1 || choice>4);

	return enGameChoice(choice);
}
enGameChoice getCoputerChoice() {
	return enGameChoice((rand() % 3) + 1);
}

enWinnerNumber whoWonTheRound(stRoundInfo roundInfo) {
	if (roundInfo.playerChoice == roundInfo.computerChoice) return enWinnerNumber::NoWinner;
	switch(roundInfo.playerChoice) {
	case enGameChoice::Stone :
		return (roundInfo.computerChoice == enGameChoice::Paper) ? enWinnerNumber::Computer : enWinnerNumber::Player1;
	case enGameChoice::Paper:
		return (roundInfo.computerChoice == enGameChoice::Scissors) ? enWinnerNumber::Computer : enWinnerNumber::Player1;
	case enGameChoice::Scissors:
		return (roundInfo.computerChoice == enGameChoice::Stone) ? enWinnerNumber::Computer : enWinnerNumber::Player1;
	}
}
enWinnerNumber whoWonTheGame(stGameInfo gameInfo) {
	if (gameInfo.player1WonTimes > gameInfo.PcWonTimes) return enWinnerNumber::Player1;
	else if (gameInfo.player1WonTimes < gameInfo.PcWonTimes) return enWinnerNumber::Computer;
	else return enWinnerNumber::NoWinner;
}

void printRoundResult(stRoundInfo roundInfo) {
	screenLigth(roundInfo.winnerNumber);
	cout << lines(2) << "__________________________Round [" << roundInfo.roundNumber << "]__________________________\n";
	cout << "Player1 Choice: " << returnChoiceName(roundInfo.playerChoice)<< endl;
	cout << "Computer Choice: " << returnChoiceName(roundInfo.computerChoice)<< endl;
	cout << "Round Winner: " << returnWinnerName(roundInfo.winnerNumber) << endl;
	cout << "_____________________________________________________________\n";
}
void showGameOverScreen() {
	cout << lines(4);
	cout << taps(4) << "___________________________________________________________\n";
	cout << taps(4) << "                    +++Game Over+++                        \n";
	cout << taps(4) << "___________________________________________________________\n";
}
void showFinalGameResults(stGameInfo gameInfo) {
	screenLigth(gameInfo.gameWinnerNumber);
	cout << lines(2) << taps(4) << "_____________________[Game Results]_________________________\n";
	cout << taps(4) << "Game Rounds        : " << gameInfo.hawManyRounds << endl;
	cout << taps(4) << "Player1 won times  : " << gameInfo.player1WonTimes << endl;
	cout << taps(4) << "Computer won times : " << gameInfo.PcWonTimes << endl;
	cout << taps(4) << "Draw times         : " << gameInfo.drawTimes << endl;;
	cout << taps(4) << "Final Winner       : " << returnWinnerName(gameInfo.gameWinnerNumber) << endl;
	cout << taps(4) << "___________________________________________________________\n";
}

void playRound(stRoundInfo& roundInfo, stGameInfo& gameInfo) {

	cout << lines(2) << "Round [" << roundInfo.roundNumber << "] begins:" << endl;

	roundInfo.playerChoice = readPlayerChoice();
	roundInfo.computerChoice = getCoputerChoice();
	roundInfo.winnerNumber = whoWonTheRound(roundInfo);
	roundInfo.winnerName = returnWinnerName(roundInfo.winnerNumber);
	printRoundResult(roundInfo);

	if (roundInfo.winnerNumber == enWinnerNumber::Player1) gameInfo.player1WonTimes++;
	else if (roundInfo.winnerNumber == enWinnerNumber::Computer) gameInfo.PcWonTimes++;
	else gameInfo.drawTimes++;
}
stGameInfo playGame() {

	stGameInfo gameInfo;
	gameInfo.hawManyRounds= readPositiveNum();

	stRoundInfo roundInfo;
	roundInfo.roundNumber = 1;

	while (roundInfo.roundNumber <= gameInfo.hawManyRounds) {
		playRound(roundInfo, gameInfo);
		roundInfo.roundNumber++;
	}
	gameInfo.gameWinnerNumber = whoWonTheGame(gameInfo);
	gameInfo.winnerName = returnWinnerName(gameInfo.gameWinnerNumber);
	sleep_for(seconds(1));
	return gameInfo;
}
void startGame() {
	int playAgain = 0;
	do {
		resetScreen();
		stGameInfo gameResult = playGame();
		showGameOverScreen();
		showFinalGameResults(gameResult);
		cout << lines(4) << taps(4) << "Do you want to Play agin? [1]:Yes [0]:No ?";
		cout << lines(1) << taps(4) << "Answer: ";
		cin >> playAgain;

	} while (playAgain == 1);
}

int main() {
	srand((unsigned)time(NULL));
	startGame();
	return 0;
}