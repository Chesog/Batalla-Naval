#include <iostream>
#include <Windows.h>
#include <time.h>
#include <conio.h>

using namespace std;

/*
Condiciones mínimas:
1. Hacer que el tablero/set de cartas tenga como mínimo 4 pares
de cartas.
2. Las cartas deben ser números o caracteres reconocibles/
fácilmente distinguibles.
3. Cada vez que se empieza una partida nueva, el tablero es
randomizado.
4. El juego se juega en solitario.

Condiciones avanzadas:
1. Hacer que el juego tenga, por lo menos, tres dificultades: Fácil,
Normal y Difícil. A medida que aumenta la dificultad el número
de pares de cartas también aumenta.
2. El jugador puede optar por terminar el juego en mitad de la
partida.

"Ultimate Conditions" :
1. Hacer que haya un sistema que cuente la cantidad de jugadas
que fueron necesarias para completar el juego.
2. Hacer que en tableros de cantidad de cartas impares exista una
carta que no posea un par y sólo genere que el jugador haya
utilizado su turno en vano.
3. Hacer que el juego tenga una condición de derrota luego de que
el jugador supere una cierta cantidad de jugadas.
*/

// ANALISIS_TM_TP6_OtrantoDario - Memotest

//------------------------------------------- Declaracion de Funciones ------------------------------

HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);                           // funcion para los colores
COORD consolecursorposition = { 20,10 };                             // posicion del cursor en pantalla
enum class MenuScenes { MainMenu, Gameplay, Rules, Credits, Exit }; // escenas del menu
struct Selection												   // struc con las posicions de las cartas seleccionadas
{
	int posX;
	int posY;
};											


int showMenu(int mainMenu);												// Muestra el Menu Principal
int gameplay();															// Muestra el Gameplay
int showCredits();														// Muestra los Creditos
int showRules();														// Muestra el Menu de Opciones
int showRules();														// Muestra las Reglas
int pointer(int maxOption, int minOption);								// puntero para la seleccion

bool exitProgram();														// Muestra el  salir del juego
bool easyMode();														// Modo facil
bool mediumMode();														// Modo Normal
bool hardMode();														// Modo Dificil
bool boardPointer(int maxBoardSize);									// Puntero para el gameplay


void boardReset();														// Reseteo del tablero
void mixCards(int cant, int modeRows, int modeColumns);					// Randomisa las cartas
void checkEquality(Selection firstCard, Selection secondCard);

//------------------------------------------ Declaracion de Variables ---------------------------------

int pointerCursor = 0;								// Cursor para la seleccion de opciones
int pointerCursorX = 0;								// Cursor en X para el gameplay
int pointerCursorY = 0;								// Cursor en Y para el gameplay
int playerTrys = 0;									// Intentos del Jugador
int playerPoints = 0;								// Puntos del Jugador
int easyModeTrys = 25;								// Total maximo de intentos para el modo facil
int mediumModeTrys = 70;							// Total maximo de intentos para el modo normal
int hardModeTrys = 85;								// Total maximo de intentos para el modo dificil
int easyModePars = 8;								// Total de pares para el modo facil
int medimModePars = 18;								// Total de pares para el modo normal
int hardModePars = 40;								// Total de pares para el modo dificil
int amountOfNumbers = 40;							// numero total 
const int easyModeRows = 4;							// Filas para el modo facil
const int easyModeColumns = 4;						// Columnas para el modo facil
const int mediumModeRows = 6;						// Filas para el modo normal
const int mediumModeColumns = 6;					// Columnas para el modo normal
const int hardModeRows = 9;							// Filas para el modo dificil
const int hardModeColumns = 9;						// Columnas para el modo dificil

bool showCards = false;								// Variable para revelar las cartas
bool win = true;									// Chequeo de si el player gano
bool exitToMenu = false;							// Chequeo para volver a la selecion de dificultad

bool checkBoard[hardModeRows][hardModeColumns];		// Chequeo para el array de las cartas
int cardsBoard[hardModeRows][hardModeColumns];		// tablero para las cartas



//------------------------------------------ Inicia el Programa ----------------------------------------
void main()
{
	ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
	srand(time(NULL));
	//setlocale(LC_ALL, "spanish");
	SetConsoleTitle((L"Memo Test"));

	int menuAnsw = 0;
	bool programOn = true;

	do											// Game Loop
	{
		switch (menuAnsw)
		{
		case (int)MenuScenes::MainMenu:
			menuAnsw = showMenu(menuAnsw);
			break;
		case (int)MenuScenes::Gameplay:
			menuAnsw = gameplay();
			break;
		case (int)MenuScenes::Rules:
			menuAnsw = showRules();
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
void boardReset()		// Reseteo del tablero
{
	int defaultValue = 0;
	for (int rows = 0; rows < hardModeRows; rows++)
	{
		for (int columns = 0; columns < hardModeColumns; columns++)
		{
			cardsBoard[rows][columns] = defaultValue;
		}
	}
	for (int rows = 0; rows < hardModeRows; rows++)
	{
		for (int columns = 0; columns < hardModeColumns; columns++)
		{
			checkBoard[rows][columns] = false;;
		}
	}
	playerPoints = defaultValue;
	playerTrys = defaultValue;
}
void mixCards(int cant, int modeRows, int modeColumns)	// funcion para la seleccion random de los pares en el tablero
{
	
	int auxRows;
	int auxColums;

	do
	{
		auxRows = rand() % modeRows;
		auxColums = rand() % modeColumns;

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
void showBoard(int maxRows, int maxColumns)	// funcion para mostrar el tablero
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

	SetConsoleTextAttribute(h, 9);
	consolecursorposition = { 3,2 };
	SetConsoleCursorPosition(h, consolecursorposition);
	cout << "Usar W,A,S,D para moverse" << endl;
	consolecursorposition = { 3,3 };
	SetConsoleCursorPosition(h, consolecursorposition);
	cout << "Usar E para selecionar" << endl;
	consolecursorposition = { 3,4 };
	SetConsoleCursorPosition(h, consolecursorposition);
	cout << "Usar P para salir al menu" << endl;

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
				if (cardsBoard[rows][columns] >= 10)
				{
					cout << verticalColumn;
					SetConsoleTextAttribute(h, 3);
					if (pointerCursorX == columns && pointerCursorY == rows)
					{
						SetConsoleTextAttribute(h, 13);
					}
					cout  << cardsBoard[rows][columns] << " ";
					SetConsoleTextAttribute(h, 11);
				}
				else
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

int showMenu(int mainMenu)	// funcion para mostrar el menu principal
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
	SetConsoleTextAttribute(h, 14);
	cout << R"(
			.------.											.------.
			|M.--. |											|T.--. |
			| (\/) |											| :/\: |
			| :\/: |											| (__) |
			| '--'M|											| '--'T|
			`------'											`------')" << endl;
	cout << R"(
					.------.											.------.
					|E.--. |											|E.--. |
					| (\/) |											| (\/) |
					| :\/: |											| :\/: |
					| '--'E|											| '--'E|
					`------'											`------')" << endl;
	cout << R"(
			.------.											.------.
			|M.--. |											|S.--. |
			| (\/) |											| :/\: |
			| :\/: |											| :\/: |
			| '--'M|											| '--'S|
			`------'											`------')" << endl;
	cout << R"(
					.------.											.------.
					|O.--. |											|T.--. |
					| :/\: |											| :/\: |
					| :\/: |											| (__) |
					| '--'O|											| '--'T|
					`------'											`------')" << endl;
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
	cout << ".--------." << endl;
	consolecursorposition = { 80,18 };
	SetConsoleCursorPosition(h, consolecursorposition);
	cout << "| Reglas |" << endl;
	consolecursorposition = { 80,19 };
	SetConsoleCursorPosition(h, consolecursorposition);
	cout << "'--------'" << endl;
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
int gameplay()	// funcion para la selecion de dificultad
{
	int userAnsw;
	int defaultValue = 0;
	int easyDificulty = 1;
	int mediumDificulty = 2;
	int hardDificulty = 3;
	int backToMainMenu = 4;
	bool continuePlaying = true;


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
			pointerCursor = defaultValue;
		}
		else if (userAnsw == mediumDificulty)
		{
			continuePlaying = mediumMode();
			pointerCursor = defaultValue;
		}
		else if (userAnsw == hardDificulty)
		{
			continuePlaying = hardMode();
			pointerCursor = defaultValue;
		}
		else  if (userAnsw == backToMainMenu)
		{
			continuePlaying = false;
		}
	} while (continuePlaying);
	pointerCursor = defaultValue;
	return defaultValue;
}
int showRules()	// funcion para mostrar las reglas
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
	SetConsoleTextAttribute(h, 14);
	cout << R"(	 El Memotest es un juego maravilloso que no solo permite al ninio desarrollar su memoria,
	 orientarse en el espacio, el reconocimiento visual,
	 entre otros, sino que ademas facilita la incorporacion de conocimientos y saberes de la cultura general de manera ludica.
	
	 # Las reglas son sencillas: consiste en una grilla o cuadricula de tamanio variable,
		# Facil:   4x4
		# Normal:  6x6
		# Dificil: 9x9
	
	 en la cual se esconden pares de objetos: pueden ser animales, capitales y paises,numeros y sus dobles, etc.
	 Los jugadores deben ir descubriendo las celdas de a una e ir recordando donde esta cada pieza del par,
	 para asi reunirlos y sumar puntos.

	 # En nuestro caso vamos a usar numeros.

	 El objetivo es lograr reunir la mayor cantidad de pares.
	 El jugador gana cuando encuentra todos los pares.
	 Si el jugador se pasa de la cantidad maxima de intentos pierde automaticamente.)" << endl;
	cout << endl;
	system("pause");
	return backToMainMenu;
}
int showCredits()	// funcion para mostrar los creditos
{
	int backToMenu = 0;
	system("cls");
	SetConsoleTextAttribute(h, 9);
	cout << R"( 
								/ \--------------------------------------, 
								\_,|                                     | 
								   |    Juego echo por : Dario Otranto   |
								   |	 Alias :                         |
								   |  ,------------------------------------
								   \_/___________________________________/ )" << endl;
	cout << endl;
	SetConsoleTextAttribute(h, 10);
	cout << R"(
								_________  /\                          
								\_   ___ \|  |__   ____   ______ ____  
								/    \  \/|  |  \_/ __ \ /  ___// __ \ 
								\     \____      \  ___/_\___ \(  \_\ )
								 \______  /___|  /\___  /____  \\____/ 
								        \/     \/     \/     \/        )" << endl;
	system("pause");
	return backToMenu;
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

bool exitProgram()	// funcion para salir del programa
{
	SetConsoleTextAttribute(h, 14);
	int backToMainMenu = 0;
	system("cls");
	cout << R"(
					.------..------..------..------..------..------..------..------.        .------..------..------.
					|S.--. ||A.--. ||L.--. ||I.--. ||E.--. ||N.--. ||D.--. ||O.--. | .-.    |..--. ||..--. ||..--. |
					| :/\: || (\/) || :/\: || (\/) || (\/) || :(): || :/\: || :/\: |((5))   | :(): || :(): || :(): |
					| :\/: || :\/: || (__) || :\/: || :\/: || ()() || (__) || :\/: | '-.-.  | ()() || ()() || ()() |
					| '--'S|| '--'A|| '--'L|| '--'I|| '--'E|| '--'N|| '--'D|| '--'O|  ((1)) | '--'.|| '--'.|| '--'.|
					`------'`------'`------'`------'`------'`------'`------'`------'   '-'  `------'`------'`------')" << endl;
	cout << endl;
	SetConsoleTextAttribute(h, 9);
	system("Pause");
	return backToMainMenu;
}
bool easyMode()	// modo de juego facil
{
	bool endCondition = false;
	bool firstCardSelected = false;
	bool secondCardSelected = false;
	exitToMenu = false;
	Selection firstCard;
	Selection secondCard;

	boardReset();
	for (int i = 1; i <= easyModePars; i++)
	{
		mixCards(i, easyModeRows, easyModeColumns);
		mixCards(i, easyModeRows, easyModeColumns);
	}
	system("cls");
	do
	{
		system("cls");
		showBoard(easyModeRows, easyModeColumns);
		consolecursorposition = { 3,12 };
		SetConsoleCursorPosition(h, consolecursorposition);
		cout << "Puntos: " << playerPoints << " / " << easyModePars << endl;
		consolecursorposition = { 3,13 };
		SetConsoleCursorPosition(h, consolecursorposition);
		cout << "Intentos: " << playerTrys << " / " << easyModeTrys << endl;
		cout << endl;
		if (!firstCardSelected)
		{
			cout << "\t""\t""\t""\t""Elija la Primera Carta" << endl;
			firstCardSelected = boardPointer(easyModeColumns);
			if (exitToMenu)
			{
				return true;
			}
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
			if (exitToMenu)
			{
				return true;
			}
			if (secondCardSelected)
			{
				secondCard.posX = pointerCursorX;
				secondCard.posY = pointerCursorY;
				if (checkBoard[secondCard.posY][secondCard.posX] == true)
				{
					cout << "\t""\t""\t""\t""Esa carta ya esta Seleccionada" << endl;
					secondCardSelected = false;
					system("pause");
				}
				else
				{
					checkBoard[secondCard.posY][secondCard.posX] = true;
				}
			}
		}
		else
		{
			checkEquality(firstCard, secondCard);
			firstCardSelected = false;
			secondCardSelected = false;
			system("pause");

		}

		if (playerTrys >= easyModeTrys)
		{
			SetConsoleTextAttribute(h, 12);
			system("cls");
			consolecursorposition = { 80,25 };
			SetConsoleCursorPosition(h, consolecursorposition);
			cout << ".----------." << endl;
			consolecursorposition = { 80,26 };
			SetConsoleCursorPosition(h, consolecursorposition);
			cout << "| PERDISTE |" << endl;
			consolecursorposition = { 80,27 };
			SetConsoleCursorPosition(h, consolecursorposition);
			cout << "'----------'" << endl;
			cout << endl;
			system("pause");
			return true;
		}

	} while (playerPoints != easyModePars);

	SetConsoleTextAttribute(h, 10);
	system("cls");
	consolecursorposition = { 80,25 };
	SetConsoleCursorPosition(h, consolecursorposition);
	cout << ".---------." << endl;
	consolecursorposition = { 80,26 };
	SetConsoleCursorPosition(h, consolecursorposition);
	cout << "| GANASTE |" << endl;
	consolecursorposition = { 80,27 };
	SetConsoleCursorPosition(h, consolecursorposition);
	cout << "'---------'" << endl;
	consolecursorposition = { 80,29 };
	SetConsoleCursorPosition(h, consolecursorposition);
	cout << ".---------------------." << endl;
	consolecursorposition = { 80,30 };
	SetConsoleCursorPosition(h, consolecursorposition);
	cout << "| Usaste: "<< playerTrys <<" intentos |" << endl;
	consolecursorposition = { 80,31 };
	SetConsoleCursorPosition(h, consolecursorposition);
	cout << "'---------------------'" << endl;
	cout << endl;
	system("pause");
	return true;
}
bool mediumMode()		// Modo de juego normal
{
	bool endCondition = false;
	bool firstCardSelected = false;
	bool secondCardSelected = false;
	exitToMenu = false;
	Selection firstCard;
	Selection secondCard;

	boardReset();
	for (int i = 1; i <= medimModePars; i++)
	{
		mixCards(i, mediumModeRows, mediumModeColumns);
		mixCards(i, mediumModeRows, mediumModeColumns);
	}
	system("cls");
	do
	{
		system("cls");
		showBoard(mediumModeRows, mediumModeColumns);
		consolecursorposition = { 3,12 };
		SetConsoleCursorPosition(h, consolecursorposition);
		cout << "Puntos: " << playerPoints << " / " << medimModePars << endl;
		consolecursorposition = { 3,13 };
		SetConsoleCursorPosition(h, consolecursorposition);
		cout << "Intentos: " << playerTrys << " / " << mediumModeTrys << endl;
		cout << endl;
		if (!firstCardSelected)
		{
			cout << "\t""\t""\t""\t""Elija la Primera Carta" << endl;
			firstCardSelected = boardPointer(mediumModeColumns);
			if (exitToMenu)
			{
				return true;
			}
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
			secondCardSelected = boardPointer(mediumModeColumns);
			if (exitToMenu)
			{
				return true;
			}
			if (secondCardSelected)
			{
				secondCard.posX = pointerCursorX;
				secondCard.posY = pointerCursorY;
				if (checkBoard[secondCard.posY][secondCard.posX] == true)
				{
					cout << "\t""\t""\t""\t""Esa carta ya esta Seleccionada" << endl;
					secondCardSelected = false;
					system("pause");
				}
				else
				{
					checkBoard[secondCard.posY][secondCard.posX] = true;
				}
			}
		}
		else
		{
			checkEquality(firstCard, secondCard);
			firstCardSelected = false;
			secondCardSelected = false;
			system("pause");

		}

		if (playerTrys >= mediumModeTrys)
		{
			SetConsoleTextAttribute(h, 12);
			system("cls");
			consolecursorposition = { 80,25 };
			SetConsoleCursorPosition(h, consolecursorposition);
			cout << ".----------." << endl;
			consolecursorposition = { 80,26 };
			SetConsoleCursorPosition(h, consolecursorposition);
			cout << "| PERDISTE |" << endl;
			consolecursorposition = { 80,27 };
			SetConsoleCursorPosition(h, consolecursorposition);
			cout << "'----------'" << endl;
			cout << endl;
			system("pause");
			return true;
		}

	} while (playerPoints != medimModePars);

	SetConsoleTextAttribute(h, 10);
	system("cls");
	consolecursorposition = { 80,25 };
	SetConsoleCursorPosition(h, consolecursorposition);
	cout << ".---------." << endl;
	consolecursorposition = { 80,26 };
	SetConsoleCursorPosition(h, consolecursorposition);
	cout << "| GANASTE |" << endl;
	consolecursorposition = { 80,27 };
	SetConsoleCursorPosition(h, consolecursorposition);
	cout << "'---------'" << endl;
	consolecursorposition = { 80,29 };
	SetConsoleCursorPosition(h, consolecursorposition);
	cout << ".---------------------." << endl;
	consolecursorposition = { 80,30 };
	SetConsoleCursorPosition(h, consolecursorposition);
	cout << "| Usaste: " << playerTrys << " intentos |" << endl;
	consolecursorposition = { 80,31 };
	SetConsoleCursorPosition(h, consolecursorposition);
	cout << "'---------------------'" << endl;
	cout << endl;
	system("pause");
	return true;
}
bool hardMode()	// modo de juego Dificil
{
	bool endCondition = false;
	bool firstCardSelected = false;
	bool secondCardSelected = false;
	exitToMenu = false;
	Selection firstCard;
	Selection secondCard;

	boardReset();
	for (int i = 1; i <= hardModePars; i++)
	{
		mixCards(i, hardModeRows, hardModeColumns);
		mixCards(i, hardModeRows, hardModeColumns);
	}
	system("cls");
	do
	{
		system("cls");
		showBoard(hardModeRows, hardModeColumns);
		consolecursorposition = { 3,12 };
		SetConsoleCursorPosition(h, consolecursorposition);
		cout << "Puntos: " << playerPoints << " / " << hardModePars << endl;
		consolecursorposition = { 3,13 };
		SetConsoleCursorPosition(h, consolecursorposition);
		cout << "Intentos: " << playerTrys << " / " << hardModeTrys << endl;
		cout << endl;
		if (!firstCardSelected)
		{
			cout << "\t""\t""\t""\t""Elija la Primera Carta" << endl;
			firstCardSelected = boardPointer(hardModeColumns);
			if (exitToMenu)
			{
				return true;
			}
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
			secondCardSelected = boardPointer(hardModeColumns);
			if (exitToMenu)
			{
				return true;
			}
			if (secondCardSelected)
			{
				secondCard.posX = pointerCursorX;
				secondCard.posY = pointerCursorY;
				if (checkBoard[secondCard.posY][secondCard.posX] == true)
				{
					cout << "\t""\t""\t""\t""Esa carta ya esta Seleccionada" << endl;
					secondCardSelected = false;
					system("pause");
				}
				else
				{
					checkBoard[secondCard.posY][secondCard.posX] = true;
				}
			}
		}
		else
		{
			checkEquality(firstCard, secondCard);
			firstCardSelected = false;
			secondCardSelected = false;
			system("pause");

		}

		if (playerTrys >= hardModeTrys)
		{
			SetConsoleTextAttribute(h, 12);
			system("cls");
			consolecursorposition = { 80,25 };
			SetConsoleCursorPosition(h, consolecursorposition);
			cout << ".----------." << endl;
			consolecursorposition = { 80,26 };
			SetConsoleCursorPosition(h, consolecursorposition);
			cout << "| PERDISTE |" << endl;
			consolecursorposition = { 80,27 };
			SetConsoleCursorPosition(h, consolecursorposition);
			cout << "'----------'" << endl;
			consolecursorposition = { 80,29 };
			SetConsoleCursorPosition(h, consolecursorposition);
			cout << ".---------------------." << endl;
			consolecursorposition = { 80,30 };
			SetConsoleCursorPosition(h, consolecursorposition);
			cout << "| Usaste: " << playerTrys << " intentos |" << endl;
			consolecursorposition = { 80,31 };
			SetConsoleCursorPosition(h, consolecursorposition);
			cout << "'---------------------'" << endl;
			cout << endl;
			system("pause");
			return true;
		}

	} while (playerPoints != hardModePars);

	SetConsoleTextAttribute(h, 10);
	system("cls");
	consolecursorposition = { 80,25 };
	SetConsoleCursorPosition(h, consolecursorposition);
	cout << ".---------." << endl;
	consolecursorposition = { 80,26 };
	SetConsoleCursorPosition(h, consolecursorposition);
	cout << "| GANASTE |" << endl;
	consolecursorposition = { 80,27 };
	SetConsoleCursorPosition(h, consolecursorposition);
	cout << "'---------'" << endl;
	cout << endl;
	system("pause");
	return true;
}
bool boardPointer(int maxBoardSize)	// cursor para el tablero del juego
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
	case 'P':
	case 'p':
		exitToMenu = true;
		break;
	default:
		break;
	}

}
void checkEquality(Selection firstCard, Selection secondCard) // funcion para verificar la igualdad de las cartas seleccionadas
{
	if (cardsBoard[firstCard.posY][firstCard.posX] == cardsBoard[secondCard.posY][secondCard.posX])
	{
		playerTrys++;
		playerPoints += 1;
		cout << "\t""\t""Encontraste el par" << endl;
		cout << endl;
	}
	else
	{
		playerTrys++;
		cout << "\t""\t""Mala Suerte :(" << endl;
		checkBoard[firstCard.posY][firstCard.posX] = false;
		checkBoard[secondCard.posY][secondCard.posX] = false;
	}
}
// --------------------------------------------------------- Fin del Programa ------------------------------