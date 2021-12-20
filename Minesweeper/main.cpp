#include <SFML/Graphics.hpp>
#include<ctime>
#include<string>
//#define DEBUG

using namespace sf;



int main()
{
	
	RenderWindow window(VideoMode(320, 400), "Minesweeper");

	Image icon;
	icon.loadFromFile("icon.png");
	window.setIcon(32, 32, icon.getPixelsPtr());
	int w = 32;
	int fieldLogic[10][10];
	int fieldShow[10][10];
	Texture texture;
	Texture statusBar;
	Texture happyFace;
	texture.loadFromFile("texture.jpg");
	statusBar.loadFromFile("status_bar_new.png");
	happyFace.loadFromFile("status_bar_happy.png");
	Sprite spriteTexture(texture);
	Sprite spriteStatusBar(statusBar);
	Sprite spriteHappyFace(happyFace);
	Font font;
	font.loadFromFile("font.TTF");
	Text GameTime("", font, 22);
	Text Score("", font, 22);
	GameTime.setFillColor(Color::White);
	GameTime.setStyle(Text::Bold);
	Score.setFillColor(Color::White);
	Score.setStyle(Text::Bold);
	Clock clock;
	bool game = 1;
	int time=0;
	int count = 0;
#ifndef DEBUG
	for (int i = 0; i< 10; i++) {
		for (int j = 0; j < 10; j++) {
			fieldShow[i][j] = 10;
			if ((rand() % 5)== 0)
				fieldLogic[i][j] = 9;
			else
				fieldLogic[i][j] = 0;
		}
	}
#endif
#ifdef DEBUG 
	for (int i=0; i<10; i++)
		for (int j = 0; j < 10; j++) {
			fieldShow[i][j] = 10;
			if (i==4 && j==4)
				fieldLogic[i][j] = 9;
			else
				fieldLogic[i][j] = 0;
	} 
#endif
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			int n = 0;
			if (fieldLogic[i][j] == 9)
				continue;
			if (fieldLogic[i - 1][j - 1] == 9)
				n++;
			if (fieldLogic[i - 1][j] == 9)
				n++;
			if (fieldLogic[i - 1][j + 1] == 9)
				n++;
			if (fieldLogic[i][j - 1] == 9)
				n++;
			if (fieldLogic[i ][j + 1] == 9)
				n++;
			if (fieldLogic[i + 1][j - 1] == 9)
				n++;
			if (fieldLogic[i + 1][j] == 9)
				n++;
			if (fieldLogic[i + 1][j + 1] == 9)
				n++;
			fieldLogic[i][j] = n;
		}
	}



	while (window.isOpen())
	{
		Event event;

		if(game)
			 time = clock.getElapsedTime().asSeconds();

		Vector2i position = Mouse::getPosition(window);
		int x = position.x/w;
		int y = position.y/w;

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			if (event.type == event.MouseButtonReleased && event.mouseButton.button == Mouse::Left) {
				fieldShow[x][y] = fieldLogic[x][y];
				if (fieldLogic[x][y] == 9) {
					game = 0;
					for (int i = 0; i < 10; i++) {
						for (int j = 0; j < 10; j++) {
							fieldShow[i][j] = fieldLogic[i][j];
						}
					}
				}
				if (game)
					count++;
			}
			if (event.type == event.MouseButtonReleased && event.mouseButton.button == Mouse::Right){
				fieldShow[x][y] = 11;
			}

			window.clear(Color::White);
			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < 10; j++) {
					spriteTexture.setTextureRect(IntRect(fieldShow[i][j] * w, 0, w, w));
					spriteTexture.setPosition(i * w, j * w);
					window.draw(spriteTexture);
				}
			}
			bool complete = 1;
			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < 10; j++) {
					if (fieldLogic[i][j] != 9 && fieldLogic[i][j] != fieldShow[i][j])
						complete = 0;
					else if (fieldLogic[i][j] == 9 && fieldShow[i][j] != 11)
						complete = 0;
				}
			}
			if (complete)
				game = 0;
			spriteStatusBar.setPosition(0, 320);
			if (game == 1 || (game == 0 && complete == 1)) {
				spriteHappyFace.setPosition(0, 320);
				window.draw(spriteHappyFace);
			}
			else {
				window.draw(spriteStatusBar);
			}
			GameTime.setString(std::to_string(time));
			GameTime.setPosition(31, 344);
			Score.setString(std::to_string(count));
			Score.setPosition(219, 344);
			window.draw(GameTime);
			window.draw(Score);

			


			window.display();
		}
	}
	
	return 0;
}