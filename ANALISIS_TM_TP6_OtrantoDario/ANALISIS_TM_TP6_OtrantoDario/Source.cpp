#include <iostream>
#include <Windows.h>
#include <time.h>
#include <conio.h>

using namespace std;


//------------------------------------------- Declaracion de Funciones ------------------------------

HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE); // funcion para los colores
COORD consolecursorposition = { 20,10 }; // posicion del cursor en pantalla
enum class MenuScenes { MainMenu, Gameplay, Options, Credits, Exit }; // escenas del menu


int showMenu(int mainMenu);					// Muestra el Menu Principal
int gameplay();								// Muestra el Gameplay
int showCredits();							// Muestra los Creditos
int showOptions();							// Muestra el Menu de Opciones
int showRules();							// Muestra las Reglas
int pointer(int maxOption, int minOption);	// puntero para la seleccion
bool exitProgram();							// Muestra el  salir del juego
bool easyMode();							// Modo facil
bool mediumMode();							// Modo Normal
bool hardMode();							// Modo Dificil
bool boardPointer(int maxBoardSize);		// Puntero para el gameplay
void boardReset();							// Reseteo del tablero
void mixCards(int cant);					// Randomisa las cartas

//------------------------------------------ Declaracion de Variables ---------------------------------

int pointerCursor = 0;								// Cursor para la seleccion de opciones
int pointerCursorX = 0;								// Cursor en X para el gameplay
int pointerCursorY = 0;								// Cursor en Y para el gameplay
int playerTrys = 0;									// Intentos del Jugador
int playerPoints = 0;								// Puntos del Jugador
int amountOfNumbers = 40;							// numero total de pares
const int easyModeRows = 4;							// Filas para el modo facil
const int easyModeColumns = 4;						// Columnas para el modo facil
const int mediumModeRows = 6;						// Filas para el modo normal
const int mediumModeColumns = 6;					// Columnas para el modo normal
const int hardModeRows = 9;							// Filas para el modo dificil
const int hardModeColumns = 9;						// Columnas para el modo dificil

bool showCards = false;								// Variable para revelar las cartas
bool win = true;									// Chequeo de si el player gano

bool checkBoard[hardModeRows][hardModeColumns];		// Chequeo para el array de las cartas
int cardsBoard[easyModeRows][easyModeColumns];		// tablero para las cartas

struct Selection
{
	int posX;
	int posY;
};

//------------------------------------------ Inicia el Programa ----------------------------------------
void main()
{
	ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
	//setlocale(LC_ALL, "spanish");
	SetConsoleTitle((L"Memo Test"));

	int menuAnsw = 0;
	bool programOn = true;

	do
	{
		switch (menuAnsw)
		{
		case (int)MenuScenes::MainMenu:
			menuAnsw = showMenu(menuAnsw);
			break;
		case (int)MenuScenes::Gameplay:
			menuAnsw = gameplay();
			break;
		case (int)MenuScenes::Options:
			menuAnsw = showOptions();
			break;
		case (int)MenuScenes::Credits:
			menuAnsw = showCredits();
			break;
		case (int)MenuScenes::Exit:
			programOn = exitProgram();
			break;
		default:
			break;
		}
	} while (programOn);
}
void boardReset()
{
	int defaultValue = 0;
	memset(cardsBoard, defaultValue, hardModeRows);
	memset(checkBoard, defaultValue, hardModeColumns);
	playerPoints = defaultValue;
	playerTrys = defaultValue;
}
void mixCards(int cant)
{
	int auxRows;
	int auxColums;

	do
	{
		auxRows = rand() % easyModeRows;
		auxColums = rand() % easyModeColumns;

		if (cardsBoard[auxRows][auxColums] == 0)
		{
			if (cant <= amountOfNumbers)
			{
				cardsBoard[auxRows][auxColums] = cant;
			}
			break;
		}

	} while (cardsBoard[auxRows][auxColums] != 0);

}
void showBoard(int maxRows, int maxColumns)
{
	char cardBack = 177;	// dorso de las cartas
	char cros = 88;		// valor "X" en el tablero
	char circle = 79;	// valor "O" en el tablero

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

	SetConsoleTextAttribute(h, 11);
	cout << "\t""\t""\t""\t""\t""\t""\t""\t" << uperLeftCorner;
	for (int i = 0; i < maxRows; i++)
	{
		cout << horizontalRow << horizontalRow << horizontalRow << uperConection;
	}
	cout << "\b" << uperRightCorner;
	cout << endl;
	for (int rows = 0; rows < maxRows; rows++)
	{
		cout << "\t""\t""\t""\t""\t""\t""\t""\t";
		for (int columns = 0; columns < maxColumns; columns++)
		{
			if (checkBoard[rows][columns] == false)
			{
				cout << verticalColumn;
				SetConsoleTextAttribute(h, 10);
				if (pointerCursorX == columns && pointerCursorY == rows)
				{
					SetConsoleTextAttribute(h, 13);
				}
				cout << " " << cardBack << " ";
				SetConsoleTextAttribute(h, 11);
			}
			else if (checkBoard[rows][columns] == true)
			{
				cout << verticalColumn;
				SetConsoleTextAttribute(h, 3);
				if (pointerCursorX == columns && pointerCursorY == rows)
				{
					SetConsoleTextAttribute(h, 13);
				}
				cout << " " << cardsBoard[rows][columns] << " ";
				SetConsoleTextAttribute(h, 11);
			}
		}
		cout << verticalColumn;
		cout << endl;

		if (rows != maxRows - 1)
		{
			cout << "\t""\t""\t""\t""\t""\t""\t""\t" << verticalConection;
			for (int i = 0; i < maxRows; i++)
			{
				cout << horizontalRow << horizontalRow << horizontalRow << crosConection;
			}
			cout << "\b" << horizontalConection;
			cout << endl;
		}
	}
	cout << "\t""\t""\t""\t""\t""\t""\t""\t" << lowerLeftCorner;
	for (int i = 0; i < maxRows; i++)
	{
		cout << horizontalRow << horizontalRow << horizontalRow << lowerConection;
	}
	cout << "\b" << lowerRightCorner;
	cout << endl;

}

int showMenu(int mainMenu)
{
	system("cls");
	int mainMenuAnsw = mainMenu;
	int play = 1;
	int Options = 2;
	int credits = 3;
	int exitMenu = 4;



	SetConsoleTextAttribute(h, 160);
	cout << R"(
					.___  ___.  _______ .___  ___.   ______      .___________. _______      _______..___________.
					|   \/   | |   ____||   \/   |  /  __  \     |           ||   ____|    /       ||           |
					|  \  /  | |  |__   |  \  /  | |  |  |  |    `---|  |----`|  |__      |   (----``---|  |----`
					|  |\/|  | |   __|  |  |\/|  | |  |  |  |        |  |     |   __|      \   \        |  |     
					|  |  |  | |  |____ |  |  |  | |  `--'  |        |  |     |  |____ .----)   |       |  |     
					|__|  |__| |_______||__|  |__|  \______/         |__|     |_______||_______/        |__|     )" << endl;
	cout << endl;
	SetConsoleTextAttribute(h, 9);
	SetConsoleTextAttribute(h, 11);
	if (pointerCursor == play)
	{
		SetConsoleTextAttribute(h, 144);
	}
	consolecursorposition = { 80,13 };
	SetConsoleCursorPosition(h, consolecursorposition);
	cout << ".-------." << endl;
	consolecursorposition = { 80,14 };
	SetConsoleCursorPosition(h, consolecursorposition);
	cout << "| Jugar |" << endl;
	consolecursorposition = { 80,15 };
	SetConsoleCursorPosition(h, consolecursorposition);
	cout << "'-------'" << endl;
	cout << endl;
	SetConsoleTextAttribute(h, 11);
	if (pointerCursor == Options)
	{
		SetConsoleTextAttribute(h, 144);
	}
	consolecursorposition = { 80,17 };
	SetConsoleCursorPosition(h, consolecursorposition);
	cout << ".----------." << endl;
	consolecursorposition = { 80,18 };
	SetConsoleCursorPosition(h, consolecursorposition);
	cout << "| Opciones |" << endl;
	consolecursorposition = { 80,19 };
	SetConsoleCursorPosition(h, consolecursorposition);
	cout << "'----------'" << endl;
	cout << endl;
	SetConsoleTextAttribute(h, 11);
	if (pointerCursor == credits)
	{
		SetConsoleTextAttribute(h, 144);
	}
	consolecursorposition = { 80,21 };
	SetConsoleCursorPosition(h, consolecursorposition);
	cout << ".----------." << endl;
	consolecursorposition = { 80,22 };
	SetConsoleCursorPosition(h, consolecursorposition);
	cout << "| Creditos |" << endl;
	consolecursorposition = { 80,23 };
	SetConsoleCursorPosition(h, consolecursorposition);
	cout << "'----------'" << endl;
	cout << endl;
	SetConsoleTextAttribute(h, 11);
	if (pointerCursor == exitMenu)
	{
		SetConsoleTextAttribute(h, 144);
	}
	consolecursorposition = { 80,25 };
	SetConsoleCursorPosition(h, consolecursorposition);
	cout << ".-------." << endl;
	consolecursorposition = { 80,26 };
	SetConsoleCursorPosition(h, consolecursorposition);
	cout << "| Salir |" << endl;
	consolecursorposition = { 80,27 };
	SetConsoleCursorPosition(h, consolecursorposition);
	cout << "'-------'" << endl;
	cout << endl;
	SetConsoleTextAttribute(h, 11);
	SetConsoleTextAttribute(h, 9);
	cout << "\t""Usar W para subir" << endl;
	cout << "\t""Usar S para bajar" << endl;
	cout << "\t""Usar E para selecionar" << endl;

	mainMenuAnsw = pointer(exitMenu, play);
	return mainMenuAnsw;
}
int gameplay()
{
	int userAnsw;
	int defaultValue = 0;
	int easyDificulty = 1;
	int mediumDificulty = 2;
	int hardDificulty = 3;
	int backToMainMenu = 4;
	int turn = 0;
	bool continuePlaying = true;

	boardReset();  // resetea el tablero

	do
	{
		system("cls");
		SetConsoleTextAttribute(h, 11);
		cout << R"(					 ____  ____  ____  ____  _________  ____  ____  _________  ____  ____  ____  ____  ____ 
					||M ||||o ||||d ||||o ||||       ||||d ||||e ||||       ||||J ||||u ||||e ||||g ||||o ||
					||__||||__||||__||||__||||_______||||__||||__||||_______||||__||||__||||__||||__||||__||
					|/__\||/__\||/__\||/__\||/_______\||/__\||/__\||/_______\||/__\||/__\||/__\||/__\||/__\|)" << endl;
		SetConsoleTextAttribute(h, 9);
		cout << endl;
		if (pointerCursor == easyDificulty)
		{
			SetConsoleTextAttribute(h, 144);
		}
		cout << "\t""\t""\t""\t""\t""\t""\t""\t""\t""\t""\b""\b""\b"".-------." << endl;
		cout << "\t""\t""\t""\t""\t""\t""\t""\t""\t""\t""\b""\b""\b""| Facil |" << endl;
		cout << "\t""\t""\t""\t""\t""\t""\t""\t""\t""\t""\b""\b""\b""'-------'" << endl;
		cout << endl;
		SetConsoleTextAttribute(h, 9);
		if (pointerCursor == mediumDificulty)
		{
			SetConsoleTextAttribute(h, 144);
		}
		cout << "\t""\t""\t""\t""\t""\t""\t""\t""\t""\t""\b""\b""\b"".--------." << endl;
		cout << "\t""\t""\t""\t""\t""\t""\t""\t""\t""\t""\b""\b""\b""| Normal |" << endl;
		cout << "\t""\t""\t""\t""\t""\t""\t""\t""\t""\t""\b""\b""\b""'--------'" << endl;
		cout << endl;
		SetConsoleTextAttribute(h, 9);
		if (pointerCursor == hardDificulty)
		{
			SetConsoleTextAttribute(h, 144);
		}
		cout << "\t""\t""\t""\t""\t""\t""\t""\t""\t""\t""\b""\b""\b"".---------." << endl;
		cout << "\t""\t""\t""\t""\t""\t""\t""\t""\t""\t""\b""\b""\b""| Dificil |" << endl;
		cout << "\t""\t""\t""\t""\t""\t""\t""\t""\t""\t""\b""\b""\b""'---------'" << endl;
		cout << endl;
		SetConsoleTextAttribute(h, 9);
		if (pointerCursor == backToMainMenu)
		{
			SetConsoleTextAttribute(h, 144);
		}
		cout << "\t""\t""\t""\t""\t""\t""\t""\t""\t""\t""\b""\b""\b"".-------------------." << endl;
		cout << "\t""\t""\t""\t""\t""\t""\t""\t""\t""\t""\b""\b""\b""| Back to Main Menu |" << endl;
		cout << "\t""\t""\t""\t""\t""\t""\t""\t""\t""\t""\b""\b""\b""'-------------------'" << endl;
		cout << endl;
		SetConsoleTextAttribute(h, 9);
		consolecursorposition = { 20,6 };
		SetConsoleCursorPosition(h, consolecursorposition);
		cout << "\t""Usar W para subir" << endl;
		consolecursorposition = { 20,7 };
		SetConsoleCursorPosition(h, consolecursorposition);
		cout << "\t""Usar S para bajar" << endl;
		consolecursorposition = { 20,8 };
		SetConsoleCursorPosition(h, consolecursorposition);
		cout << "\t""Usar E para selecionar" << endl;
		userAnsw = pointer(backToMainMenu, easyDificulty);
		if (userAnsw == easyDificulty)
		{
			continuePlaying = easyMode();
		}
		else if (userAnsw == mediumDificulty)
		{
			continuePlaying = mediumMode();
		}
		else if (userAnsw == hardDificulty)
		{
			continuePlaying = hardMode();
		}
		else  if (userAnsw == backToMainMenu)
		{
			continuePlaying = false;
		}
	} while (continuePlaying);
	pointerCursor = defaultValue;
	return defaultValue;
}
int showOptions()
{
	system("cls");
	SetConsoleTextAttribute(h, 14);
	int backToMainMenu = 0;
	system("pause");
	return backToMainMenu;
}
int showRules()
{
	SetConsoleTextAttribute(h, 13);
	int backToMainMenu = 0;
	system("cls");
	cout << R"( 
												 _______  _______  _______  _        _______  _______ 
												(  ____ )(  ____ \(  ____ \( \      (  ___  )(  ____ \
												| (    )|| (    \/| (    \/| (      | (   ) || (    \/
												| (____)|| (__    | |      | |      | (___) || (_____ 
												|     __)|  __)   | | ____ | |      |  ___  |(_____  )
												| (\ (   | (      | | \_  )| |      | (   ) |      ) |
												| ) \ \__| (____/\| (___) || (____/\| )   ( |/\____) |
												|/   \__/(_______/(_______)(_______/|/     \|\_______)
								                                                      )" << endl;
	SetConsoleTextAttribute(h, 9);
	cout << R"(
	Este juego consiste en 3 o 4 jugadores que deben recorrer un tablero conformado por casillas con el objetivo de conseguir la mayor cantidad de monedas al pasar 5 vueltas al tablero.

	Todos los jugadores empezarán el juego con 0 monedas y éste será también el valor mínimo de monedas posibles

	Para moverse los jugadores tienen que tirar un dado de seis caras que determina cuántas casillas van a avanzar.

	A lo largo del juego los jugadores pueden caer en X tipos de casillas que tendrán una consecuencia distinta.
	
	----------------casillas-------------------
	
	 ° casilla vacía = no hay consecuencias
	
	 ° casilla Cazado = El cazador pensara un número del 1 a 3, si el jugador acierta el numero se le dará la cantidad de monedas que pensó 

		el cazador pero si no acierta el cazador lo hara retroceder la cantidad de números que pensó.
	
	 ° casilla Cazador = el jugador que cae en la casilla tiene la posibilidad de elegir a qué jugador quiere disparar, 

		al tirar un dado este determina cuántas casillas tendrá que retroceder el jugador seleccionado
	
	 ° casilla minijuego = En esta casilla se tendrá que jugar a un minijuego. Este minijuego consiste en adivinar en donde se esconde la tortuga,

		 ésta se esconderá en uno de los 6 lugares que se podrán elegir si el jugador acierta se le sumará 3 monedas y si pierde se le restara 3.
	
	 ° casilla Lanza otra vez = En esta casilla el jugador puede volver a lanzar un dado.
	
	 ° Casillas puntos = al jugador se le dará una cantidad aleatoria entre 1 y 5 de monedas.
	
)" << endl;
	system("pause");
	return backToMainMenu;
}
int showCredits()
{
	int backToMainMenu = 0;
	system("cls");
	SetConsoleTextAttribute(h, 14);
	cout << R"(
									  ____                                        _   _               _                             
									 |  _ \    ___   ___    __ _   _ __    ___   | | | |   __ _    __| |   ___    _ __    ___   ___ 
									 | | | |  / _ \ / __|  / _` | | '__|  / _ \  | | | |  / _` |  / _` |  / _ \  | '__|  / _ \ / __|
									 | |_| | |  __/ \__ \ | (_| | | |    | (_) | | | | | | (_| | | (_| | | (_) | | |    |  __/ \__ \
									 |____/   \___| |___/  \__,_| |_|     \___/  |_| |_|  \__,_|  \__,_|  \___/  |_|     \___| |___/
																																		)" << endl;
	SetConsoleTextAttribute(h, 3);
	cout << endl;
	cout << "\t""\t""\t""\t""\t""\t"".------------------." << endl;
	cout << "\t""\t""\t""\t""\t""\t""| Ignacio Arrastua |" << endl;
	cout << "\t""\t""\t""\t""\t""\t""'------------------'" << endl;
	cout << endl;
	cout << "\t""\t""\t""\t""\t""\t"".----------------." << endl;
	cout << "\t""\t""\t""\t""\t""\t""| Santiago Barra |" << endl;
	cout << "\t""\t""\t""\t""\t""\t""'----------------'" << endl;
	cout << endl;
	cout << "\t""\t""\t""\t""\t""\t"".---------------." << endl;
	cout << "\t""\t""\t""\t""\t""\t""| Dario Otranto |" << endl;
	cout << "\t""\t""\t""\t""\t""\t""'---------------'" << endl;
	cout << endl;
	cout << "\t""\t""\t""\t""\t""\t"".-------------." << endl;
	cout << "\t""\t""\t""\t""\t""\t""| Enzo Coleta |" << endl;
	cout << "\t""\t""\t""\t""\t""\t""'-------------'" << endl;
	cout << endl;
	cout << "\t""\t""\t""\t""\t""\t"".----------------." << endl;
	cout << "\t""\t""\t""\t""\t""\t""| Facundo Santos |" << endl;
	cout << "\t""\t""\t""\t""\t""\t""'----------------'" << endl;
	cout << endl;
	cout << "\t""\t""\t""\t""\t""\t"".-------------------." << endl;
	cout << "\t""\t""\t""\t""\t""\t""| Emiliano Cortinez |" << endl;
	cout << "\t""\t""\t""\t""\t""\t""'-------------------'" << endl;
	cout << endl;
	system("pause");
	return backToMainMenu;
}
int pointer(int maxOption, int minOption) // cursor para el menu
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
}

bool exitProgram()
{
	SetConsoleTextAttribute(h, 12);
	int backToMainMenu = 0;
	system("cls");
	cout << R"( 
					 .----------------.  .----------------.  .----------------.  .----------------.  .----------------.  .-----------------. .----------------.  .----------------. 
					| .--------------. || .--------------. || .--------------. || .--------------. || .--------------. || .--------------. || .--------------. || .--------------. |
					| |    _______   | || |      __      | || |   _____      | || |     _____    | || |  _________   | || | ____  _____  | || |  ________    | || |     ____     | |
					| |   /  ___  |  | || |     /  \     | || |  |_   _|     | || |    |_   _|   | || | |_   ___  |  | || ||_   \|_   _| | || | |_   ___ `.  | || |   .'    `.   | |
					| |  |  (__ \_|  | || |    / /\ \    | || |    | |       | || |      | |     | || |   | |_  \_|  | || |  |   \ | |   | || |   | |   `. \ | || |  /  .--.  \  | |
					| |   '.___`-.   | || |   / ____ \   | || |    | |   _   | || |      | |     | || |   |  _|  _   | || |  | |\ \| |   | || |   | |    | | | || |  | |    | |  | |
					| |  |`\____) |  | || | _/ /    \ \_ | || |   _| |__/ |  | || |     _| |_    | || |  _| |___/ |  | || | _| |_\   |_  | || |  _| |___.' / | || |  \  `--'  /  | |
					| |  |_______.'  | || ||____|  |____|| || |  |________|  | || |    |_____|   | || | |_________|  | || ||_____|\____| | || | |________.'  | || |   `.____.'   | |
					| |              | || |              | || |              | || |              | || |              | || |              | || |              | || |              | |
					| '--------------' || '--------------' || '--------------' || '--------------' || '--------------' || '--------------' || '--------------' || '--------------' |
					 '----------------'  '----------------'  '----------------'  '----------------'  '----------------'  '----------------'  '----------------'  '----------------' )" << endl;
	system("Pause");
	return backToMainMenu;
}
bool easyMode()
{
	int easyModeTrys = 30;
	int easyModeSelection = 1;
	int diferentCards = 8;
	bool easyModeOn = true;
	bool winCondition = false;
	bool firstCardSelected = false;
	bool secondCardSelected = false;
	Selection firstCard;
	Selection SecondCard;

	for (int i = 1; i <= diferentCards; i++)
	{
		mixCards(i);
		mixCards(i);
	}
	system("cls");
	do
	{
		system("cls");
		showBoard(easyModeRows, easyModeColumns);
		cout << endl;
		if (!firstCardSelected)
		{
			cout << "\t""\t""\t""\t""Elija la Primera Carta" << endl;
			firstCardSelected = boardPointer(easyModeColumns);
			if (firstCardSelected)
			{
				firstCard.posX = pointerCursorX;
				firstCard.posY = pointerCursorY;
				if (checkBoard[firstCard.posY][firstCard.posX] == true)
				{
					cout << "\t""\t""\t""\t""Esa carta ya esta Seleccionada" << endl;
					firstCardSelected = false;
					system("pause");
				}
				else
				{
					checkBoard[firstCard.posY][firstCard.posX] = true;
				}
			}
		}
		else if (firstCardSelected && !secondCardSelected)
		{
			cout << "\t""\t""\t""\t""Elija la Segunda Carta" << endl;
			secondCardSelected = boardPointer(easyModeColumns);
			if (secondCardSelected)
			{
				SecondCard.posX = pointerCursorX;
				SecondCard.posY = pointerCursorY;
				if (checkBoard[SecondCard.posY][SecondCard.posX] == true)
				{
					cout << "\t""\t""\t""\t""Esa carta ya esta Seleccionada" << endl;
					secondCardSelected = false;
					system("pause");
				}
				else
				{
					checkBoard[SecondCard.posY][SecondCard.posX] = true;
				}
			}
		}
		else
		{

		}
	} while (!winCondition);
	return true;
}
bool mediumMode()
{
	return true;
}
bool hardMode()
{
	return true;
}
bool boardPointer(int maxBoardSize)
{
	int max = maxBoardSize - 1;
	int min = 0;
	char cursor;
	cursor = _getch();
	switch (cursor)
	{
	case 'W':
	case 'w':
		pointerCursorY--;
		if (pointerCursorY < min)
		{
			pointerCursorY = max;
		}
		return false;
		break;
	case 'S':
	case 's':
		pointerCursorY++;
		if (pointerCursorY > max)
		{
			pointerCursorY = min;
		}
		return false;
		break;
	case 'A':
	case 'a':
		pointerCursorX--;
		if (pointerCursorX < min)
		{
			pointerCursorX = max;
		}
		return false;
		break;
	case 'D':
	case 'd':
		pointerCursorX++;
		if (pointerCursorX > max)
		{
			pointerCursorX = min;
		}
		return false;
		break;
	case 'E':
	case 'e':
		return true;
		break;
	default:
		break;
	}

}