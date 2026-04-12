#include<iostream>
#include<cstdlib>
#include<thread>
#include<chrono>
using namespace std;
using namespace this_thread;
using namespace chrono;

enum enQuestionLevel { Easy=1, Med, Hard, Mixed };
enum enOperationType { Add=1, Sub, Mul, Div, Mix};

string getQuestionLevel(int levelNumber) {
	string levels[] = { "Easy","Med","Hard","Mix" };
	return levels[levelNumber - 1];
}
string getOperationType(int typeNumber) {
	string types[] = { "Add","Sub","Mul","Div","Mix" };
	return types[typeNumber - 1];
}
string getQuizResult(bool result) {
	if (result)
		return "PASS";
	else
		return "FAIL";
}
string getOperationSymbol(int typeNumber) {
	string types[] = { "+","-","*","/" };
	return types[typeNumber - 1];
}

struct stQuestion {
	int number1 = 0;
	int number2 = 0;
	enQuestionLevel questionsLevel;
	enOperationType operationType;
	int correctAnswer = 0;
	int playerAnswer = 0;
	bool answerResult = false;
};
struct stQuiz {
	stQuestion questionListe[100];
	short numberOfQuestion=0;
	enQuestionLevel questionsLevel;
	enOperationType operationType;
	short numberOfRightAnswers = 0;
	short numberOfWrongAnswers=0;
	bool isPass=false;
};

int randomNumber(int from, int to) {
	return (rand() % (to - from + 1)) + from;
}
short readHowManyQuestions() {
	short number = 0;
	do {
		cout << "How Many Questions do you want to answer? ";
		cin >> number;
	} while (number < 1 || number>10);
	return number;
}
enQuestionLevel readQuestionsLevel() {
	short level;
	do {
		cout << "Enter Questions Level [1] Easy, [2] Med, [3] Hard, [4] Mix ? ";
		cin >> level;
	} while (level < 1 || level>4);
	return (enQuestionLevel)level;
}
enOperationType readOperationType() {
	short type;
	do {
		cout << "Enter Questions Type [1] Add, [2] Sub, [3] Mul, [4] Div, [5] Mix ? ";
		cin >> type;
	} while (type < 1 || type>5);
	return (enOperationType)type;
}
int ReadQuestionAnswer() {
	int answer = 0;
	cin >> answer;
	return answer;
}



void setScreenColor(bool result) {
	if (result)
		system("color 2F");
	else
		system("color 4F");
}
void printQuizResult(stQuiz quiz) {

	sleep_for(seconds(1));

	setScreenColor(quiz.isPass);

	cout << "\n_____________________________________________________\n" << endl;
	cout << "\tFinal Results is " <<getQuizResult(quiz.isPass)<< endl;
	cout << "\n_____________________________________________________\n" << endl;

	sleep_for(seconds(1));

	cout << "Number of Questoins: " << quiz.numberOfQuestion;
	cout << "\nQuestoins Level    : " << getQuestionLevel(quiz.questionsLevel);
	cout << "\nOperation Typ      : " << getOperationType(quiz.operationType);
	cout << "\nNumber of Right Answers: " << quiz.numberOfRightAnswers;
	cout << "\nNumber of Wrong Answers: " << quiz.numberOfWrongAnswers;
	cout << "\n_____________________________________________________" << endl;
}
void resetScreen() {
	system("cls");
	system("color 0F");
}

int simpleCalculator(int nummber1, int number2, enOperationType type) {
	switch (type) {
	case enOperationType::Add:
		return nummber1 + number2;

	case enOperationType::Sub:
		return nummber1 - number2;

	case enOperationType::Mul:
		return nummber1 * number2;

	case enOperationType::Div:
		return (number2 == 0 ? 0 : nummber1 / number2);
	}
}
stQuestion generateQuestion(enQuestionLevel level, enOperationType type) {
	stQuestion question;

	if (level == enQuestionLevel::Mixed)
		level = (enQuestionLevel)randomNumber(1, 3);

	if (type == enOperationType::Mix)
		type = (enOperationType)randomNumber(1, 4);

	question.questionsLevel = level;
	question.operationType = type;

	switch (question.questionsLevel) {

	case enQuestionLevel::Easy:
		question.number1 = randomNumber(1, 10);
		question.number2 = randomNumber(1, 10);
		question.correctAnswer = simpleCalculator(question.number1, question.number2, question.operationType);
		return question;

	case enQuestionLevel::Med:
		question.number1 = randomNumber(10, 50);
		question.number2 = randomNumber(10, 50);
		question.correctAnswer = simpleCalculator(question.number1, question.number2, question.operationType);
		return question;

	case enQuestionLevel::Hard:
		question.number1 = randomNumber(50, 100);
		question.number2 = randomNumber(50, 100);
		question.correctAnswer = simpleCalculator(question.number1, question.number2, question.operationType);
		return question;
	}
}
void generateQuizzQuestions(stQuiz& quiz) {
	for (int question = 0; question < quiz.numberOfQuestion; question++) {
		quiz.questionListe[question] = generateQuestion(quiz.questionsLevel, quiz.operationType);
	}
}


void printTheQuestion(stQuiz& quiz, short questionNumber) {

	cout << "\nQuestion [" << questionNumber+1<< "/" << quiz.numberOfQuestion<< "]\n" << endl;
	cout << quiz.questionListe[questionNumber].number1 << endl;
	cout << quiz.questionListe[questionNumber].number2 << "  ";
	cout << getOperationSymbol(quiz.questionListe[questionNumber].operationType);
	cout << "\n________________" << endl;
}
void correctTheQuestionAnswer(stQuiz& quiz, short questionNumber) {
	if (quiz.questionListe[questionNumber].playerAnswer != quiz.questionListe[questionNumber].correctAnswer) {
		quiz.questionListe[questionNumber].answerResult = false;
		quiz.numberOfWrongAnswers++;

		cout << "Wrong Answer :-(\n";
		cout << "The Right answer is: " << quiz.questionListe[questionNumber].correctAnswer;
		cout << "\n";
	}
	else {
		quiz.questionListe[questionNumber].answerResult = true;
		quiz.numberOfRightAnswers++;

		cout << "Right Answer :-(\n";
	}
	cout << endl;

	setScreenColor(quiz.questionListe[questionNumber].answerResult);
	
}
void askAndCorrectQuestionsListAnswers(stQuiz& quiz) {
	
	for (short questionNumber = 0; questionNumber < quiz.numberOfQuestion; questionNumber++) {
		printTheQuestion(quiz, questionNumber);
		quiz.questionListe[questionNumber].playerAnswer = ReadQuestionAnswer();
		correctTheQuestionAnswer(quiz, questionNumber);
	}
	quiz.isPass = (quiz.numberOfRightAnswers >= quiz.numberOfWrongAnswers);
}

void playMathGame() {

	stQuiz quiz;
	quiz.numberOfQuestion= readHowManyQuestions();
	quiz.questionsLevel = readQuestionsLevel();
	quiz.operationType = readOperationType();

	generateQuizzQuestions(quiz);
	askAndCorrectQuestionsListAnswers(quiz);

	printQuizResult(quiz);
}
void startGame() {
	int quizAgain = 0;
	do {
		resetScreen();
		playMathGame();

		cout << "Do you want to play again? [1]Yes, [0]No ? ";
		cin >> quizAgain;

	} while (quizAgain == 1);
}

int main() {
	srand((unsigned)time(NULL));
	startGame();
	return 0;
}