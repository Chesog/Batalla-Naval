#include <iostream>
#include <Windows.h>
#include <conio.h>

using namespace std;
// ------------------------------------------ Declaracion de Funciones ---------------------------------------
int pointer();
int showMenu(int mainMenu);

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

int pointerCursor = 0;

void main()
{
	enum class MenuScenes { MainMenu, Gameplay, Options, Credits, Exit };
	int menuAnsw = 0;
	bool ProgramOn = true;
	system("cls");
	do
	{
		switch (menuAnsw)
		{
		case (int)MenuScenes::MainMenu:
			menuAnsw = showMenu(menuAnsw);
			break;
		case (int)MenuScenes::Gameplay:
			system("cls");
			cout << "Gameplay" << endl;
			system("pause");
			menuAnsw = (int)MenuScenes::MainMenu;
			break;
		case (int)MenuScenes::Options:
			system("cls");
			cout << "Opciones" << endl;
			system("pause");
			menuAnsw = (int)MenuScenes::MainMenu;
			break;
		case (int)MenuScenes::Credits:
			system("cls");
			cout << "Creditos" << endl;
			system("pause");
			menuAnsw = (int)MenuScenes::MainMenu;
			break;
		case (int)MenuScenes::Exit:
			system("cls");
			cout << "Salir" << endl;
			system("pause");
			menuAnsw = (int)MenuScenes::MainMenu;
			break;
		default:
			break;
		}
	} while (ProgramOn);


}
int showMenu(int mainMenu)
{
	system("cls");
	int mainMenuAnsw = mainMenu;
	int play = 1;
	int options = 2;
	int credits = 3;
	int exitMenu = 4;
	SetConsoleTextAttribute(hConsole, 9);
	cout << R"(                         @@@@@@@    @@@@@@   @@@@@@@   @@@@@@   @@@       @@@        @@@@@@      @@@  @@@   @@@@@@   @@@  @@@   @@@@@@   @@@       
                         @@@@@@@@  @@@@@@@@  @@@@@@@  @@@@@@@@  @@@       @@@       @@@@@@@@     @@@@ @@@  @@@@@@@@  @@@  @@@  @@@@@@@@  @@@       
                         @@!  @@@  @@!  @@@    @@!    @@!  @@@  @@!       @@!       @@!  @@@     @@!@!@@@  @@!  @@@  @@!  @@@  @@!  @@@  @@!       
                         !@   @!@  !@!  @!@    !@!    !@!  @!@  !@!       !@!       !@!  @!@     !@!!@!@!  !@!  @!@  !@!  @!@  !@!  @!@  !@!       
                         @!@!@!@   @!@!@!@!    @!!    @!@!@!@!  @!!       @!!       @!@!@!@!     @!@ !!@!  @!@!@!@!  @!@  !@!  @!@!@!@!  @!!       
                         !!!@!!!!  !!!@!!!!    !!!    !!!@!!!!  !!!       !!!       !!!@!!!!     !@!  !!!  !!!@!!!!  !@!  !!!  !!!@!!!!  !!!       
                         !!:  !!!  !!:  !!!    !!:    !!:  !!!  !!:       !!:       !!:  !!!     !!:  !!!  !!:  !!!  :!:  !!:  !!:  !!!  !!:       
                         :!:  !:!  :!:  !:!    :!:    :!:  !:!   :!:       :!:      :!:  !:!     :!:  !:!  :!:  !:!   ::!!:!   :!:  !:!   :!:      
                          :: ::::  ::   :::     ::    ::   :::   :: ::::   :: ::::  ::   :::      ::   ::  ::   :::    ::::    ::   :::   :: ::::  
                         :: : ::    :   : :     :      :   : :  : :: : :  : :: : :   :   : :     ::    :    :   : :     :       :   : :  : :: : :  
                                                                                                                         )" << endl;
	cout << endl;
	SetConsoleTextAttribute(hConsole, 11);
	if (pointerCursor == play)
	{
		SetConsoleTextAttribute(hConsole, 144);
	}
	cout << "\t""\t""\t""\t""\t""\t""\t""\t""\t""\t"".-------." << endl;
	cout << "\t""\t""\t""\t""\t""\t""\t""\t""\t""\t""| Jugar |" << endl;
	cout << "\t""\t""\t""\t""\t""\t""\t""\t""\t""\t""'-------'" << endl;
	cout << endl;
	SetConsoleTextAttribute(hConsole, 11);
	if (pointerCursor == options)
	{
		SetConsoleTextAttribute(hConsole, 144);
	}
	cout << "\t""\t""\t""\t""\t""\t""\t""\t""\t""\t""\b"".----------." << endl;
	cout << "\t""\t""\t""\t""\t""\t""\t""\t""\t""\t""\b""| Opciones |" << endl;
	cout << "\t""\t""\t""\t""\t""\t""\t""\t""\t""\t""\b""'----------'" << endl;
	cout << endl;
	SetConsoleTextAttribute(hConsole, 11);
	if (pointerCursor == credits)
	{
		SetConsoleTextAttribute(hConsole, 144);
	}
	cout << "\t""\t""\t""\t""\t""\t""\t""\t""\t""\t""\b"".----------." << endl;
	cout << "\t""\t""\t""\t""\t""\t""\t""\t""\t""\t""\b""| Creditos |" << endl;
	cout << "\t""\t""\t""\t""\t""\t""\t""\t""\t""\t""\b""'----------'" << endl;
	cout << endl;
	SetConsoleTextAttribute(hConsole, 11);
	if (pointerCursor == exitMenu)
	{
		SetConsoleTextAttribute(hConsole, 144);
	}
	cout << "\t""\t""\t""\t""\t""\t""\t""\t""\t""\t"".-------." << endl;
	cout << "\t""\t""\t""\t""\t""\t""\t""\t""\t""\t""| Salir |" << endl;
	cout << "\t""\t""\t""\t""\t""\t""\t""\t""\t""\t""'-------'" << endl;
	cout << endl;
	SetConsoleTextAttribute(hConsole, 11);
	mainMenuAnsw = pointer();
	return mainMenuAnsw;
}
int pointer()
{
	int defaultOption = 0;
	char cursor;
	int play = 1;
	int exitMenu = 4;
	cursor = _getch();
	switch (cursor)
	{
	case 'W':
	case 'w':
		if (pointerCursor < play)
		{
			pointerCursor = exitMenu;
		}
		else
		{
			pointerCursor--;
		}
		return defaultOption;
		break;
	case 'S':
	case 's':
		if (pointerCursor > exitMenu)
		{
			pointerCursor = play;
		}
		else
		{
			pointerCursor++;
		}
		return defaultOption;
		break;
	case 'E':
	case 'e':
		return pointerCursor;
		break;
	default:
		return defaultOption;
		break;
	}
}