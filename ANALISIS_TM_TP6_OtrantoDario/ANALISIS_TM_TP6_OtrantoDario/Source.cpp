#include <iostream>
#include <Windows.h>
#include <conio.h>

using namespace std;
// ------------------------------------------ Declaracion de Funciones ---------------------------------------
int pointer(int maxOption, int minOption);
int showMenu(int mainMenu);
void showPrincipalBoard(int turn);
void showShotBoard(int turn);
int gameplay(bool newGame);
bool resetBoards();
bool setBoardShips();

HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

COORD consolecursorposition = { 48,1 }; // posicion del cursor en pantalla
int pointerCursor = 0;
int totalShipsP1 = 10;
int totalShipsP2 = 10;
const int maxBoardSize = 10;

int player1PrincipalBoard[maxBoardSize][maxBoardSize];
int player2PrincipalBoard[maxBoardSize][maxBoardSize];
bool player1ShotBoard[maxBoardSize][maxBoardSize];
bool player2ShotBoard[maxBoardSize][maxBoardSize];

void main()
{
	ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
	enum class MenuScenes { MainMenu, Gameplay, Options, Credits, Exit };
	int menuAnsw = 0;
	bool ProgramOn = true;
	bool newGame = true;
	do
	{
		switch (menuAnsw)
		{
		case (int)MenuScenes::MainMenu:
			menuAnsw = showMenu(menuAnsw);
			break;
		case (int)MenuScenes::Gameplay:
			system("cls");
			newGame = true;
			menuAnsw = gameplay(newGame);
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
			SetConsoleTextAttribute(h, 12);
			system("cls");
			cout << R"(								 ____ ____ ____ _________ ____ ____ ____ ____ ____ 
								||N |||o |||s |||       |||V |||e |||m |||o |||s ||
								||__|||__|||__|||_______|||__|||__|||__|||__|||__||
								|/__\|/__\|/__\|/_______\|/__\|/__\|/__\|/__\|/__\|)" << endl;
			system("pause");
			ProgramOn = false;
			break;
		default:
			break;
		}
	} while (ProgramOn);


}
int gameplay(bool newGame) // funcion que contiene el juego
{
	int userAnsw;
	int backToMainMenu = 0;
	int plyVsCpu = 1;
	int plyVsPly = 2;
	int turn = 0;
	bool newGameGamplay = newGame;
	bool fase1Player1 = true;
	bool fase1Player2 = true;
	bool continuePlaying = true;
	do
	{
		if (newGame)
		{
			newGameGamplay = resetBoards();
		}
		system("cls");
		SetConsoleTextAttribute(h, 11);
		cout << R"(					 ____  ____  ____  ____  _________  ____  ____  _________  ____  ____  ____  ____  ____ 
					||M ||||o ||||d ||||o ||||       ||||d ||||e ||||       ||||J ||||u ||||e ||||g ||||o ||
					||__||||__||||__||||__||||_______||||__||||__||||_______||||__||||__||||__||||__||||__||
					|/__\||/__\||/__\||/__\||/_______\||/__\||/__\||/_______\||/__\||/__\||/__\||/__\||/__\|)" << endl;
		SetConsoleTextAttribute(h, 9);
		cout << endl;
		if (pointerCursor == plyVsCpu)
		{
			SetConsoleTextAttribute(h, 144);
		}
		cout << "\t""\t""\t""\t""\t""\t""\t""\t""\t""\t"".---------------." << endl;
		cout << "\t""\t""\t""\t""\t""\t""\t""\t""\t""\t""| Player vs CPU |" << endl;
		cout << "\t""\t""\t""\t""\t""\t""\t""\t""\t""\t""'---------------'" << endl;
		cout << endl;
		SetConsoleTextAttribute(h, 9);
		if (pointerCursor == plyVsPly)
		{
			SetConsoleTextAttribute(h, 144);
		}
		cout << "\t""\t""\t""\t""\t""\t""\t""\t""\t""\t""\b"".------------------." << endl;
		cout << "\t""\t""\t""\t""\t""\t""\t""\t""\t""\t""\b""| Player vs Player |" << endl;
		cout << "\t""\t""\t""\t""\t""\t""\t""\t""\t""\t""\b""'------------------'" << endl;
		cout << endl;
		SetConsoleTextAttribute(h, 9);
		userAnsw = pointer(plyVsPly, plyVsCpu);
		if (userAnsw == plyVsCpu)
		{
			system("cls");
			cout << "Player vs CPU" << endl;
			continuePlaying = false;
			system("pause");
		}
		else if (userAnsw == plyVsPly)
		{
			system("cls");
			do
			{
				//cout << "Player vs Player" << endl;
				showPrincipalBoard(turn);
				fase1Player1 =  setBoardShips();
				system("cls");
			} while (fase1Player1);
			
			system("pause");
		}
	} while (continuePlaying);
	pointerCursor = backToMainMenu;
	return backToMainMenu;
}
int showMenu(int mainMenu) // funcion para mostrar el menu principal
{
	system("cls");
	int mainMenuAnsw = mainMenu;
	int play = 1;
	int options = 2;
	int credits = 3;
	int exitMenu = 4;
	SetConsoleTextAttribute(h, 9);
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
	SetConsoleTextAttribute(h, 11);
	if (pointerCursor == play)
	{
		SetConsoleTextAttribute(h, 144);
	}
	cout << "\t""\t""\t""\t""\t""\t""\t""\t""\t""\t"".-------." << endl;
	cout << "\t""\t""\t""\t""\t""\t""\t""\t""\t""\t""| Jugar |" << endl;
	cout << "\t""\t""\t""\t""\t""\t""\t""\t""\t""\t""'-------'" << endl;
	cout << endl;
	SetConsoleTextAttribute(h, 11);
	if (pointerCursor == options)
	{
		SetConsoleTextAttribute(h, 144);
	}
	cout << "\t""\t""\t""\t""\t""\t""\t""\t""\t""\t""\b"".----------." << endl;
	cout << "\t""\t""\t""\t""\t""\t""\t""\t""\t""\t""\b""| Opciones |" << endl;
	cout << "\t""\t""\t""\t""\t""\t""\t""\t""\t""\t""\b""'----------'" << endl;
	cout << endl;
	SetConsoleTextAttribute(h, 11);
	if (pointerCursor == credits)
	{
		SetConsoleTextAttribute(h, 144);
	}
	cout << "\t""\t""\t""\t""\t""\t""\t""\t""\t""\t""\b"".----------." << endl;
	cout << "\t""\t""\t""\t""\t""\t""\t""\t""\t""\t""\b""| Creditos |" << endl;
	cout << "\t""\t""\t""\t""\t""\t""\t""\t""\t""\t""\b""'----------'" << endl;
	cout << endl;
	SetConsoleTextAttribute(h, 11);
	if (pointerCursor == exitMenu)
	{
		SetConsoleTextAttribute(h, 144);
	}
	cout << "\t""\t""\t""\t""\t""\t""\t""\t""\t""\t"".-------." << endl;
	cout << "\t""\t""\t""\t""\t""\t""\t""\t""\t""\t""| Salir |" << endl;
	cout << "\t""\t""\t""\t""\t""\t""\t""\t""\t""\t""'-------'" << endl;
	cout << endl;
	SetConsoleTextAttribute(h, 11);
	mainMenuAnsw = pointer(exitMenu, play);
	return mainMenuAnsw;
}
int pointer(int maxOption, int minOption)
{
	int defaultOption = 0;
	int max = maxOption;
	int min = minOption;
	char cursor;
	cursor = _getch();
	switch (cursor)
	{
	case 'W':
	case 'w':
		pointerCursor--;
		if (pointerCursor < min)
		{
			pointerCursor = max;
		}
		return defaultOption;
		break;
	case 'S':
	case 's':
		pointerCursor++;
		if (pointerCursor > max)
		{
			pointerCursor = min;
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
} // cursor para el menu
bool resetBoards() // funcion para resetear los tableros
{
	int defaultValue = 0; // valor default para los tableros
	memset(player1PrincipalBoard, defaultValue, maxBoardSize); // resetea el tablero principal del jugador 1
	memset(player2PrincipalBoard, defaultValue, maxBoardSize); // resetea el tablero principal del jugador 2
	memset(player1ShotBoard, defaultValue, maxBoardSize); // resetea el tablero de tiro del jugador 1
	memset(player2ShotBoard, defaultValue, maxBoardSize); // resetea el tablero de tiro del jugador 2
	return false;
}
void showPrincipalBoard(int turn)
{
	char uperLeftCorner = 201; // esquina superior izquierda ╔
	char uperRightCorner = 187; // esquina superior derecha ╗
	char lowerLeftCorner = 200; // esquina inferior izquierda ╚
	char lowerRightCorner = 188; // esquina inferior Derecha ╝
	char horizontalRow = 205;	// linea horizontal ═
	char verticalColumn = 186; // linea vertical ║
	char uperConection = 203; // conector superior ╦
	char lowerConection = 202; // conector inferior ╩
	char horizontalConection = 185; // conector derecho ╣
	char verticalConection = 204; // conector izquierdo ╠
	char crosConection = 206; // interseccion ╬

	char empty = 32;	// valor vacio en el tablero
	char cros = 88;		// valor "X" en el tablero
	char circle = 79;	// valor "O" en el tablero

	SetConsoleTextAttribute(h, 9);
	cout << "\t" << uperLeftCorner;
	for (int i = 0; i < maxBoardSize; i++)
	{
		cout << horizontalRow << horizontalRow << horizontalRow << uperConection;
	}
	cout << "\b" << uperRightCorner;
	cout << endl;
	for (int rows = 0; rows < maxBoardSize; rows++)
	{
		cout << "\t";
		for (int columns = 0; columns < maxBoardSize; columns++)
		{
			if (player1PrincipalBoard[rows][columns] == 1)
			{
				cout << verticalColumn;
				SetConsoleTextAttribute(h, 8);
				cout << " " << cros << " ";
				SetConsoleTextAttribute(h, 13);
			}
			else if (player1PrincipalBoard[rows][columns] == 2)
			{
				cout << verticalColumn;
				SetConsoleTextAttribute(h, 3);
				cout << " " << circle << " ";
				SetConsoleTextAttribute(h, 13);
			}
			else
			{
				cout << verticalColumn << " " << empty << " ";
			}
		}
		cout << verticalColumn;
		cout << endl;

		if (rows != maxBoardSize - 1)
		{
			cout << "\t" << verticalConection;
			for (int i = 0; i < maxBoardSize; i++)
			{
				cout << horizontalRow << horizontalRow << horizontalRow << crosConection;
			}
			cout << "\b" << horizontalConection;
			cout << endl;
		}
	}
	cout << "\t" << lowerLeftCorner;
	for (int i = 0; i < maxBoardSize; i++)
	{
		cout << horizontalRow << horizontalRow << horizontalRow << lowerConection;
	}
	cout << "\b" << lowerRightCorner;
	cout << endl;
}
void showShotBoard(int turn)
{
	char uperLeftCorner = 201; // esquina superior izquierda ╔
	char uperRightCorner = 187; // esquina superior derecha ╗
	char lowerLeftCorner = 200; // esquina inferior izquierda ╚
	char lowerRightCorner = 188; // esquina inferior Derecha ╝
	char horizontalRow = 205;	// linea horizontal ═
	char verticalColumn = 186; // linea vertical ║
	char uperConection = 203; // conector superior ╦
	char lowerConection = 202; // conector inferior ╩
	char horizontalConection = 185; // conector derecho ╣
	char verticalConection = 204; // conector izquierdo ╠
	char crosConection = 206; // interseccion ╬
	char squareConection = 219; // conexion entre tableros █

	char empty = 32;	// valor vacio en el tablero
	char cros = 88;		// valor "X" en el tablero
	char circle = 79;	// valor "O" en el tablero
	int maxSpace = 43;

	SetConsoleTextAttribute(h, 3);
	cout << "\t";
	cout << "\b""\b" << squareConection << squareConection;
	for (int i = 0; i < maxSpace; i++)
	{
		cout << squareConection;
	}
	cout << endl;
	SetConsoleTextAttribute(h, 9);
	cout << "\t" << uperLeftCorner;
	for (int i = 0; i < maxBoardSize; i++)
	{
		cout << horizontalRow << horizontalRow << horizontalRow << uperConection;
	}
	cout << "\b" << uperRightCorner;
	cout << endl;
	for (int rows = 0; rows < maxBoardSize; rows++)
	{
		cout << "\t";
		for (int columns = 0; columns < maxBoardSize; columns++)
		{
			if (player1PrincipalBoard[rows][columns] == 1)
			{
				cout << verticalColumn;
				SetConsoleTextAttribute(h, 8);
				cout << " " << cros << " ";
				SetConsoleTextAttribute(h, 13);
			}
			else if (player1PrincipalBoard[rows][columns] == 2)
			{
				cout << verticalColumn;
				SetConsoleTextAttribute(h, 3);
				cout << " " << circle << " ";
				SetConsoleTextAttribute(h, 13);
			}
			else
			{
				cout << verticalColumn << " " << empty << " ";
			}
		}
		cout << verticalColumn;
		cout << endl;

		if (rows != maxBoardSize - 1)
		{
			cout << "\t" << verticalConection;
			for (int i = 0; i < maxBoardSize; i++)
			{
				cout << horizontalRow << horizontalRow << horizontalRow << crosConection;
			}
			cout << "\b" << horizontalConection;
			cout << endl;
		}
	}
	cout << "\t" << lowerLeftCorner;
	for (int i = 0; i < maxBoardSize; i++)
	{
		cout << horizontalRow << horizontalRow << horizontalRow << lowerConection;
	}
	cout << "\b" << lowerRightCorner;
	cout << endl;
}
bool setBoardShips() 
{
	enum class Ships {Acorazado = 1,Crucero,Destructor,Submarino};

	cout << "Selecione el barco que quiera usar" << endl;
	char water = 126;
	char acorazado = 219;
	char crucero = 175;
	char destructor = 223;
	char submarino = 220;
	char cros = 88;		// valor "X" en el tablero
	
	int shipSelected = 0;
	int allShipsPlaced = 0;

	//cout << "\t" << water << " = Agua" << endl;
	//cout << "\t" << cros << " = HIT!" << endl;
	SetConsoleTextAttribute(h, 11);
	if (pointerCursor == (int)Ships::Acorazado)
	{
		SetConsoleTextAttribute(h, 144);
	}
	cout << "\t" << " " << acorazado << " = Acorazado 4 casillas" << endl;
	SetConsoleTextAttribute(h, 11);
	if (pointerCursor == (int)Ships::Crucero)
	{
		SetConsoleTextAttribute(h, 144);
	}
	cout << "\t" << " " << crucero << " = Crucero 3 casillas" << endl;
	SetConsoleTextAttribute(h, 11);
	if (pointerCursor == (int)Ships::Destructor)
	{
		SetConsoleTextAttribute(h, 144);
	}
	cout << "\t" << " " << destructor << " = Destructor 2 casillas" << endl;
	SetConsoleTextAttribute(h, 11);
	if (pointerCursor == (int)Ships::Submarino)
	{
		SetConsoleTextAttribute(h, 144);
	}
	cout << "\t" << " " << submarino << " = Submarino 1 casilla" << endl;
	SetConsoleTextAttribute(h, 11);
	shipSelected = pointer((int)Ships::Submarino, (int)Ships::Acorazado);
	switch (shipSelected)
	{
	case (int)Ships::Acorazado:
		break;
	case (int)Ships::Crucero:
		break;
	case (int)Ships::Destructor:
		break;
	case (int)Ships::Submarino:
		break;
	default:
		cout << "Error" << endl;
		break;
	}
	if (totalShipsP1 == allShipsPlaced)
	{
		return false;
	}
	else
	{
		return true;
	}
}