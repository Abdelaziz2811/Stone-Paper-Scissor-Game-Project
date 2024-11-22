#include <iostream>
#include <cstdlib>
using namespace std;

enum enGameChoice { stone = 1, paper = 2, scissors = 3 };
enum enWinner { player = 1, computer = 2, draw = 3 };

struct stRoundInfo
{
	short RoundNumber=0;
	enGameChoice PlayerChoice;
	enGameChoice ComputerChoice;
	enWinner Winner;
	string WinnerName="";
};

struct stGameresults
{
	short GameRounds=0;
	short PlayerWinTimes=0;
	short ComputerWinTimes=0;
	short DrawTimes=0;
	enWinner GameWinner;
	string WinnerName="";
};

int Randnum(int from, int to)
{
	int num = rand() % (to - from + 1) + from;
	return num;
}

short Readhowmanyrounds()
{
	short rounds;
	do
	{
		cout << "How many rounds 1 to 10 ?\n";
		cin >> rounds;

	} while (rounds < 1 || rounds>10);
	return rounds;
}

enGameChoice ReadPlayerChoice()
{
	short choice;
	do
	{
		cout << "Your choice : [1]:Stone, [2]:Paper, [3]:Scissors ? ";
		cin >> choice;

	} while (choice < 1 || choice>3);
	return (enGameChoice)choice;
}

enGameChoice GetComputerChoice()
{
	return (enGameChoice)Randnum(1, 3);
}

enWinner WhoWonTheRound(stRoundInfo RoundInfo)
{
	if (RoundInfo.PlayerChoice == RoundInfo.ComputerChoice)
	{
		return enWinner::draw;
	}

	switch (RoundInfo.PlayerChoice)
	{
	case enGameChoice::stone:
		if (RoundInfo.ComputerChoice == paper)
			return enWinner::computer;
		break;
	case enGameChoice::paper:
		if (RoundInfo.ComputerChoice == scissors)
			return enWinner::computer;
		break;
	case enGameChoice::scissors:
		if (RoundInfo.ComputerChoice == stone)
			return enWinner::computer;
		break;
	}

	// reach here means player win.
	return enWinner::player;
		
}

string WinnerName(enWinner Winner)
{
	string arr[3] = { "[Player]","[Computer]","[No Winner]" };
	return arr[Winner - 1];
}

string ChoiceName(enGameChoice GameChoice)
{
	string arr[3] = { "stone","paper","scissors" };
	return arr[GameChoice - 1];
}

enWinner WhoWonTheGame(short PlayerWinTimes, short ComputerWinTimes, short DrawTimes)
{
	if (PlayerWinTimes > ComputerWinTimes)
		return enWinner::player;
	else if (ComputerWinTimes > PlayerWinTimes)
		return enWinner::computer;
	else
		return enWinner::draw;
}

string GameWinnerName(enWinner Winner)
{
	string arr[3] = { "Player","Computer","No Winner" };
	return arr[Winner - 1];
}

stGameresults FillGameResults(short Rounds, short PlayerWinTimes, short ComputerWinTimes, short DrawTimes)
{
	stGameresults GameResults;
	GameResults.GameRounds = Rounds;
	GameResults.PlayerWinTimes = PlayerWinTimes;
	GameResults.ComputerWinTimes = ComputerWinTimes;
	GameResults.DrawTimes = DrawTimes;
	GameResults.GameWinner = WhoWonTheGame(PlayerWinTimes, ComputerWinTimes, DrawTimes);
	GameResults.WinnerName = GameWinnerName(GameResults.GameWinner);

	return GameResults;
}

string Tabs(int NumberOfTabs)
{
	string Tabs="";
	for (int i = 1; i <= NumberOfTabs; i++)
	{
		Tabs += "\t";
	}
	return Tabs;
}

void SetScreenColor(enWinner Winner)
{
	switch (Winner)
	{
	case enWinner::player:
		system("color 2F");
		break;
	case enWinner::computer:
		system("color 4F");
		cout << "\a";
		break;
	case enWinner::draw:
		system("color 6F");
		break;
	}
}

void PrintRoundResults(stRoundInfo RoundInfo)
{
	cout << "\n\n__________________Round[" << RoundInfo.RoundNumber << "]__________________\n\n";
	cout << "Player Choice    :" << ChoiceName(RoundInfo.PlayerChoice) << endl;
	cout << "Computer Choice  :" << ChoiceName(RoundInfo.ComputerChoice) << endl;
	cout << "Round Winner     :" << RoundInfo.WinnerName << endl;
	cout << "\n___________________________________________\n\n";
	SetScreenColor(RoundInfo.Winner);
}

void PrintFinalResults(stGameresults GameResults)
{
	cout << Tabs(3) << "___________________________ [G a m e   R e a s u l t s] ___________________________\n\n";
	cout << Tabs(3) << "Game rounds              : " << GameResults.GameRounds << endl;
	cout << Tabs(3) << "Player Won Times         : " << GameResults.PlayerWinTimes << endl;
	cout << Tabs(3) << "Computer Won Times       : " << GameResults.ComputerWinTimes << endl;
	cout << Tabs(3) << "Draw Times               : " << GameResults.DrawTimes << endl;
	cout << Tabs(3) << "Final Winner             : " << GameResults.WinnerName << endl;
	cout << Tabs(3) << "__________________________________________________________________________________\n\n";
	SetScreenColor(GameResults.GameWinner);
}

void ShowScreenGameOver()
{
	cout << Tabs(3) << "__________________________________________________________________________________\n\n";
	cout << Tabs(3) << "                            +++ G a m e    O v e r +++                            \n";
	cout << Tabs(3) << "__________________________________________________________________________________\n\n";
}

void ResetScreen()
{
	system("color 0F");
	system("cls");
}

stGameresults PlayGame(short HowManyRounds)
{
	stRoundInfo RoundInfo;
	short PlayerWinTimes = 0, ComputerWinTimes = 0, DrawTimes = 0;

	for (int GameRound = 1; GameRound <= HowManyRounds; GameRound++)
	{
		cout << "Round [" << GameRound << "] begins : \n\n";
		
		RoundInfo.RoundNumber = GameRound;
		RoundInfo.PlayerChoice = ReadPlayerChoice();
		RoundInfo.ComputerChoice = GetComputerChoice();
		RoundInfo.Winner = WhoWonTheRound(RoundInfo);
		RoundInfo.WinnerName = WinnerName(RoundInfo.Winner);

		// incrase win/draw counters .
		if (RoundInfo.Winner == enWinner::player)
			PlayerWinTimes++;
		else if (RoundInfo.Winner == enWinner::computer)
			ComputerWinTimes++;
		else
			DrawTimes++;


		PrintRoundResults(RoundInfo);
	}

	return FillGameResults(HowManyRounds, PlayerWinTimes, ComputerWinTimes, DrawTimes);
}

void StartGame()
{
	char PlayAgain;
	do
	{
		ResetScreen();
		stGameresults GameResults = PlayGame(Readhowmanyrounds());
		ShowScreenGameOver();
		PrintFinalResults(GameResults);
		cout << "do you want to play again [Y]:yes [n]:No ? ";
		cin >> PlayAgain;

	} while (PlayAgain == 'Y' || PlayAgain == 'y');

}

int main() {
	srand((unsigned)time(NULL));
	
	StartGame();

	return 0;
}

