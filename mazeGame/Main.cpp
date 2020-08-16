// iD Tech Game Plan - SFML Template
#include "essentials.h"
#include <fstream>
#include "maze.h"
#include "Player.h"

/* DEFINE GAMESTATES HERE */
string levelsPath = "defaultMazes.txt";

string defaultOrUserMaps();

string defaultOrUserMaps() {
	cout << "Would you like to use your own mazes?(y/n)" << endl;
	char input;
	cin >> input;
	if (input == 'y' || input == 'Y') {
		cout << "Enter the path to your maze text file: ";
		string path;
		cin >> path;
		cout << path;
		return path;
	}
	else {
		return levelsPath;
	}
}

int main()
{
	levelsPath = defaultOrUserMaps();

	vector<maze> levels;

	float currentLevel = 0;

	ifstream file(levelsPath);
	int mazeCount = file.get() - 47;
	file.get();

	for (int k = 0; k < mazeCount; k++) {
		int dimension = file.get() - 47;
		vector<vector<char>> mazeData;

		file.get();
		for (int i = 0; i < dimension; i++) {
			vector<char> temp;
			for (int j = 0; j < dimension; j++) {
				temp.push_back(file.get());
			}
			mazeData.push_back(temp);
			file.get();
		}

		levels.push_back(maze(mazeData));
	}

	sf::RenderWindow window(sf::VideoMode(500, 500), "Maze Game");

	Player player(levels[currentLevel].squareSize/2);
	player.setPos(levels[currentLevel].getPlayerStart());

	bool menuOpen = true;

	Music backGrndMusic;
	backGrndMusic.openFromFile("backGroundMusic.wav");
	backGrndMusic.setLoop(true);
	backGrndMusic.setVolume(20);

	backGrndMusic.play();

	Font font;
	font.loadFromFile("default.ttf");
	Text label;
	Text info;
	label.setFont(font);
	info.setFont(font);
	label.setCharacterSize(24);
	info.setCharacterSize(18);
	label.setString("Welcome to Maze Game!!");
	info.setString("Press Enter to begin.");
	label.setFillColor(Color::Magenta);
	info.setFillColor(Color::Magenta);
	label.setPosition(Vector2f(100, 100));
	info.setPosition(Vector2f(150, 150));

	// Run the Program while the Window is Open
	while (window.isOpen())
	{
		if (menuOpen) {
			if (Keyboard::isKeyPressed(Keyboard::Enter)) {
				menuOpen = false;
			}

			window.clear(Color::White);
			window.draw(label);
			window.draw(info);
			window.display();
			continue;
		}
		
		sf::Event event;
		while (window.pollEvent(event))
		{
			// When X Button Clicked, Close Window
			if (event.type == sf::Event::Closed)
				window.close();
			if (Keyboard::isKeyPressed(Keyboard::P)) {
				currentLevel++;
				player.setPos(levels[currentLevel].getPlayerStart());
				float pSize = levels[currentLevel].squareSize / 2;
				player.changeSize(pSize);
				levels[currentLevel].resetKey();
			}
		}
		player.checkInput();

		if (!levels[currentLevel].isKeyCollected()) {
			levels[currentLevel].checkKey(player.getShape());
		}

		if (levels[currentLevel].checkCollisions(player.getShape())) {
			player.setPos(levels[currentLevel].getPlayerStart());
			levels[currentLevel].resetKey();
		}

		if (levels[currentLevel].checkExit(player.getShape())) {
			currentLevel++;
			player.setPos(levels[currentLevel].getPlayerStart());
			float pSize = levels[currentLevel].squareSize / 2;
			player.changeSize(pSize);
			levels[currentLevel].resetKey();
		}

		/* DEFINE ACTIONS (i.e. MOVEMENT) HERE */

		window.clear(Color::White);
		/* DRAW OBJECTS HERE */
		for (RectangleShape rs : levels[currentLevel].getShapes()) {
			window.draw(rs);
		}
		window.draw(player.getShape());
		window.display();
	}
}