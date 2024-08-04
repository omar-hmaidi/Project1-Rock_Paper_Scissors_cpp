#include <iostream>
#include <cstdlib>

using namespace std;

enum enGameChoice { Rock = 1, Paper = 2, Scissors = 3 };
enum enWinner { Player1 = 1, Computer = 2, Draw = 3 };

struct stRoundInfo
{
	short RoundNumber = 0;
	enGameChoice Player1Choice;
	enGameChoice ComputerChoice;
	enWinner Winner;
	string WinnerName;

};

struct stGameResults
{

	short GameRounds = 0;
	short Player1WinTimes = 0;
	short ComputerWinTimes = 0;
	short DrawTimes = 0;
	enWinner GameWinner;
	string WinnerName = "";

};

int RandomNumber(int From, int To)
{
	int RandNum = rand() % (To - From + 1) + From;
	return RandNum;
}

int delay(int milliseconds) // #include <ctime>
{
	clock_t goal = milliseconds + clock(); // Set the goal time
	while (goal > clock()); // Wait until the goal time is reached
	return 1;
}

string WinnerName(enWinner Winner)
{
	string arrWinnerName[3] = { "Player1","Computer","No Winner" };
	return arrWinnerName[Winner - 1];
}

enWinner WhoWonTheRound(stRoundInfo RoundInfo)
{
	if (RoundInfo.Player1Choice == RoundInfo.ComputerChoice)
	{
		return enWinner::Draw;
	}

	switch (RoundInfo.Player1Choice)
	{

	case enGameChoice::Rock:
		if (RoundInfo.ComputerChoice == enGameChoice::Paper)
		{
			return enWinner::Computer;
		}
		break;

	case enGameChoice::Paper:
		if (RoundInfo.ComputerChoice == enGameChoice::Scissors)
		{
			return enWinner::Computer;
		}
		break;

	case enGameChoice::Scissors:
		if (RoundInfo.ComputerChoice == enGameChoice::Rock)
		{
			return enWinner::Computer;
		}
		break;
	}

	//if you reach here then player1 is the winner.
	return enWinner::Player1;

}

string ChoiceName(enGameChoice Choice)
{
	string arrGameChoices[3] = { "Rock","Paper","Scissors" };

	return arrGameChoices[Choice - 1];
}

void SetWinnerScreenColor(enWinner Winner)
{
	switch (Winner)
	{
	case enWinner::Player1:
		system("color 2F"); //turn screen to Green
		break;

	case enWinner::Computer:
		system("color 4F"); //turn screen to Red
		cout << "\a";		//Beeb.
		break;

	default:
		system("color 6F"); //trun screen to Yellow
		break;
	}
}

void PrintRoundResults(stRoundInfo RoundInfo)
{
	cout << "\n____________Round [" << RoundInfo.RoundNumber << "] ____________\n\n";
	cout << "Player1  Choice: " << ChoiceName(RoundInfo.Player1Choice) << endl;
	cout << "Computer Choice: " << ChoiceName(RoundInfo.ComputerChoice) << endl;
	cout << "RoundWinner    : [" << RoundInfo.WinnerName << "] \n";
	cout << "__________________________________\n" << endl;

	SetWinnerScreenColor(RoundInfo.Winner);
}

enWinner WhoWonTheGame(short Player1WinTimes, short ComputerWinTimes)
{
	if (Player1WinTimes > ComputerWinTimes)
		return enWinner::Player1;
	else if (ComputerWinTimes > Player1WinTimes)
		return enWinner::Computer;
	else
		return enWinner::Draw;
}

stGameResults FillGameResults(int GameRounds, short Player1WinTimes, short ComputerWinTimes, short DrawTimes)
{

	stGameResults GameResults;

	GameResults.GameRounds = GameRounds;
	GameResults.Player1WinTimes = Player1WinTimes;
	GameResults.ComputerWinTimes = ComputerWinTimes;
	GameResults.DrawTimes = DrawTimes;
	GameResults.GameWinner = WhoWonTheGame(Player1WinTimes, ComputerWinTimes);
	GameResults.WinnerName = WinnerName(GameResults.GameWinner);

	return GameResults;

}

enGameChoice ReadPlayer1Choice()
{
	short Choice = 1;

	do
	{
		cout << "\nYour Choice: [1]:Rock, [2]:Paper, [3]:Scissors ? ";
		cin >> Choice;
	} while (Choice < 1 || Choice >3);

	return (enGameChoice)Choice;
}

enGameChoice GetComputerChoice()
{

	return (enGameChoice)RandomNumber(1, 3);
}

stGameResults PlayGame(short HowManyRounds)
{
	stRoundInfo RoundInfo;
	short Player1WinTimes = 0, ComputerWinTime = 0, DrawTimes = 0;

	for (short GameRound = 1; GameRound <= HowManyRounds; GameRound++)
	{
		cout << "\nRound [" << GameRound << "] begins:\n";
		RoundInfo.RoundNumber = GameRound;
		RoundInfo.Player1Choice = ReadPlayer1Choice();
		RoundInfo.ComputerChoice = GetComputerChoice();
		RoundInfo.Winner = WhoWonTheRound(RoundInfo);
		RoundInfo.WinnerName = WinnerName(RoundInfo.Winner);

		//Increase Win/Draw counters
		if (RoundInfo.Winner == enWinner::Player1)
			Player1WinTimes++;
		else if (RoundInfo.Winner == enWinner::Computer)
			ComputerWinTime++;
		else
			DrawTimes++;

		PrintRoundResults(RoundInfo);
	}

	return FillGameResults(HowManyRounds, Player1WinTimes, ComputerWinTime, DrawTimes);
}

string Tabs(short NumberOfTabs)
{
	string t = "";
	for (int i = 1; i <= NumberOfTabs; i++)
	{
		t = t + "\t";
		cout << t;
	}
	return t;
}

void ShowGameOverScreen()
{

	cout << Tabs(2) << "____________________________________________\n\n";
	cout << Tabs(2) << "	    +++ G A M E  O V E R +++\n";
	cout << Tabs(2) << "____________________________________________\n\n";

}

void ShowFinalGameResults(stGameResults GameResults)
{

	delay(1000);
	ShowGameOverScreen();
	SetWinnerScreenColor(GameResults.GameWinner);

	cout << Tabs(2) << "___________________ [Game Results ]_________\n\n";
	cout << Tabs(2) << "Game Rounds        :" << GameResults.GameRounds << endl;
	cout << Tabs(2) << "Player1 won times  :" << GameResults.Player1WinTimes << endl;
	cout << Tabs(2) << "Computer won times :" << GameResults.ComputerWinTimes << endl;
	cout << Tabs(2) << "Draw times         :" << GameResults.DrawTimes << endl;
	cout << Tabs(2) << "Final Winner	   :" << GameResults.WinnerName << endl;
	cout << Tabs(2) << "____________________________________________" << endl;


}

short ReadHowManyRounds()
{
	short GameRounds = 1;

	do
	{
		cout << "How Many Rounds 1 to 10 ?\n";
		cin >> GameRounds;

	} while (GameRounds < 0 || GameRounds > 10);

	return GameRounds;
}

void RestScreen()
{
	system("cls");
	system("color A");
}

void StartGame()
{

	char PlayAgain = 'Y';

	do
	{

		RestScreen();
		stGameResults GameResults = PlayGame(ReadHowManyRounds());

		ShowFinalGameResults(GameResults);

		cout << endl << Tabs(3) << "Do you want to play again? Y/N ";
		cin >> PlayAgain;
	} while (PlayAgain == 'Y' || PlayAgain == 'y');

	system("color A");
}


int main()
{
	//Seeds the random number generator in c++ , called only once
	srand((unsigned)time(NULL));

	StartGame();

	return 0;
}