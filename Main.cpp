#define _CRT_SECURE_NO_WARNINGS
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Player.h"
#include "Platform.h"
#include "Enemy.h"
#include "Slide.h"
#include "Coin.h"
#include "Itembox.h"
#include "Menu.h"
#include <string>
#include <cstdio>
#include <algorithm>
#include <utility>
using namespace std;

void Showtext(int x, int y, string word, int size, sf::RenderWindow& window, sf::Font* font)
{
	sf::Text text;
	text.setFont(*font);
	text.setPosition(x, y);
	text.setString(word);
	text.setCharacterSize(size);
	text.setFillColor(sf::Color::Black);
	window.draw(text);
}


int updatascore(string a, int b)
{
	FILE* fp;
	char temp[255];
	int score[6];
	string name[6];
	vector<pair<int, string>> userScore;

	fp = fopen("score.txt", "r");
	if (fp == nullptr) {
		printf("Error opening file for reading\n");
		return 1;
	}

	for (int i = 0; i < 5; i++) {
		fscanf(fp, "%s", temp);
		name[i] = temp;
		fscanf(fp, "%d", &score[i]);
		userScore.push_back(make_pair(score[i], name[i]));
	}

	fclose(fp);

	// Assuming 'a' and 'b' are defined earlier in your code
	name[5] = a;  // Replace with the actual value of 'a'
	score[5] = b;

	userScore.push_back(make_pair(score[5], name[5]));
	sort(userScore.begin(), userScore.end(), greater<pair<int, string>>());  // Sort in descending order

	fp = fopen("score.txt", "w");
	if (fp == nullptr) {
		printf("Error opening file for writing\n");
		return 1;
	}

	for (int i = 0; i < 5; i++) {
		fprintf(fp, "%s %d\n", userScore[i].second.c_str(), userScore[i].first);
	}

	fclose(fp);

	return 0;
}

void Showscoreboard(sf::RenderWindow& window)
{
	sf::Font font;
	font.loadFromFile("font/Minecraft.ttf");
	FILE* fp;
	char temp[255];
	int score[6];
	string name[6];
	fp = fopen("score.txt", "r");
	for (int i = 0; i < 5; i++)
	{
		char no[3] = { '1' + i };
		no[1] = '.';
		no[2] = '\0';
		Showtext(230, 180 + 40 * i, no, 30, window, &font);
		fscanf(fp, "%s", &temp);
		Showtext(280, 180 + 40 * i, temp, 30, window, &font);
		fscanf(fp, "%d", &score[i]);
		char sc[10];
		int k = 0, j;
		if (score[i] == 0)
			sc[k++] = 48;
		while (score[i] > 0)
		{
			sc[k++] = score[i] % 10 + 48;
			score[i] /= 10;
		}
		sc[k] = '\0';
		char show[10];
		for (j = 0; j < strlen(sc); j++)
		{
			show[j] = sc[strlen(sc) - 1 - j];
		}
		show[j] = '\0';
		Showtext(700, 180 + 40 * i, show, 30, window, &font);
	}
	fclose(fp);

}

int main() 
{
	float time_enemy_1 = 0;
	float time_coin = 0;
	float time_item = 0;
	int score = 0;
	sf::RenderWindow window(sf::VideoMode(1024, 512), "WILD RUSH!", sf::Style::Close );
	sf::Texture playerTexture;
	playerTexture.loadFromFile("image/Dino.png");
	sf::Texture playerslTexture;
	playerslTexture.loadFromFile("image/Dinosl.png");
	Player player(&playerTexture, sf::Vector2u(2, 1), 0.3f,150.0f,200.0f);
	Slide slide(&playerslTexture, sf::Vector2u(2, 1), 0.3f, 150.0f);
	sf::Texture bearTexture;
	bearTexture.loadFromFile("image/bear.png");
	sf::Texture batTexture;
	batTexture.loadFromFile("image/bat.png");
	sf::Texture coingoldTexture;
	coingoldTexture.loadFromFile("image/coingold.png");
	sf::Texture coinsilverTexture;
	coinsilverTexture.loadFromFile("image/coinsilver.png");
	sf::Texture itemboxTexture;
	itemboxTexture.loadFromFile("image/giftred.png");

	sf::Font font;
	if (!font.loadFromFile("font/Minecraft.ttf"))
	{
		// error...
	}

	float timess ;
	float time_item2=0.0f;
	string namestr;
	sf::Text clockk;
	clockk.setFont(font);
	clockk.setString("TIME : ");
	clockk.setCharacterSize(30);
	clockk.setFillColor(sf::Color::Black);
	clockk.setPosition(412, 0);

	sf::Text clocktext;
	clocktext.setFont(font);
	clocktext.setCharacterSize(30);
	clocktext.setFillColor(sf::Color::Black);
	clocktext.setPosition(512, 0);

	sf::Text text;
	text.setFont(font);
	text.setString("SCORE : ");
	text.setCharacterSize(30);
	text.setFillColor(sf::Color::Red);
	//text.setPosition(0, 0);

	sf::Text scoretext;
	scoretext.setFont(font);
	scoretext.setCharacterSize(30);
	scoretext.setFillColor(sf::Color::Red);
	scoretext.setPosition(150, 0);

	std::vector<Platform> platforms;
	std::vector<Enemy> enemys;
	std::vector<Coin> coins;
	std::vector<Itembox> itemboxs;
	sf::Texture bgTT;
	bgTT.loadFromFile("image/background.png");
	Platform bg(&bgTT, sf::Vector2f(1024.0f, 512.0f), sf::Vector2f(512.0f, 256.0f));
	platforms.push_back(Platform(nullptr, sf::Vector2f(1200.0f, 245.0f), sf::Vector2f(500.0f, 520.0f)));
	/*Platform platform1(nullptr, sf::Vector2f(400.0f, 200.0f), sf::Vector2f(500.0f, 200.0f));
	Platform platform2(nullptr, sf::Vector2f(400.0f, 200.0f), sf::Vector2f(500.0f, 0.0f));
	Platform platform2(nullptr, sf::Vector2f(1000.0f, 200.0f), sf::Vector2f(500.0f, 500.0f));*/

	sf::Texture menuTT;
	menuTT.loadFromFile("image/mainmenuu.png");
	Platform menu(&menuTT, sf::Vector2f(1024.0f, 512.0f), sf::Vector2f(512.0f, 256.0f));

	sf::Texture nameTT;
	nameTT.loadFromFile("image/enteryourname.png");
	Platform name(&nameTT, sf::Vector2f(1024.0f, 512.0f), sf::Vector2f(512.0f, 256.0f));

	sf::Texture overTT;
	overTT.loadFromFile("image/gameover.png");
	Platform over(&overTT, sf::Vector2f(1024.0f, 512.0f), sf::Vector2f(512.0f, 256.0f));

	sf::Texture scoreboardTT;
	scoreboardTT.loadFromFile("image/scoreboard.png");
	Platform scoreboard(&scoreboardTT, sf::Vector2f(1024.0f, 512.0f), sf::Vector2f(512.0f, 256.0f));

	sf::Texture pauseTT;
	pauseTT.loadFromFile("image/paused.png");
	Platform pause(&pauseTT, sf::Vector2f(1024.0f, 512.0f), sf::Vector2f(512.0f, 256.0f));


	float deltaTime = 0.0f;
	sf::Clock clock;
	srand(clock.restart().asSeconds());
	int state = 0;
	int status = -1;

	while (window.isOpen()) 
	{
		
		
		deltaTime = clock.restart().asSeconds();
		if (deltaTime > 1.0f / 20.0f)
			deltaTime = 1.0f / 20.0f;
		

		sf::Event evnt;
		while (window.pollEvent(evnt)) 
		{
			if (evnt.type == sf::Event::Closed)
				window.close();
			if (state == 2)
			{
				if (evnt.type == sf::Event::TextEntered)
				{
					namestr.push_back(evnt.text.unicode);
					cout << namestr<<'\n';
				}
				if (!namestr.empty() && namestr.back() == 8)
				{
					namestr.pop_back();
					if (!namestr.empty())
						namestr.pop_back();

				}
				if (!namestr.empty() && !(namestr.back() >= 'a' && namestr.back() <= 'z' || namestr.back() >= 'A' && namestr.back() <= 'Z' || namestr.back() >= '0' && namestr.back() <= '9'))
				{
					namestr.pop_back();
				}
			}
			if (state == 1)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
				{
					state = 5;
					while (sf::Keyboard::isKeyPressed(sf::Keyboard::P));
				}
			}
		}
		int x = sf::Mouse::getPosition(window).x;
		int y = sf::Mouse::getPosition(window).y;


		if (state == 0)
		{
			

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && x >= 410.0f && x <= 640.0f && y >= 215.0f && y <= 300.0f)
			{
				state = 1;
				timess = 90;
				coins.clear();
				enemys.clear();
				itemboxs.clear();
				score = 0;
				player.body.setPosition(356.0f, 240.0f);
				slide.body.setPosition(356.0f, 1000.0f);
				namestr.clear();
				status = -1;
			}
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && x >= 720.0f && x <= 960.0f && y >= 215.0f && y <= 300.0f)
			{
				break;
			}
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && x >= 75.0f && x <= 320.0f && y >= 215.0f && y <= 300.0f)
			{
				state = 4;
				while (sf::Mouse::isButtonPressed(sf::Mouse::Left));
			}
			menu.Draw(window);
			
		}
		else if (state == 1)
		{
			timess -= deltaTime;
			time_coin += deltaTime;
			if (time_coin >= 0.8)
			{
				int random = rand() % 4;
				time_coin -= 0.8;
				if (random == 0)
					coins.push_back(Coin(&coingoldTexture, sf::Vector2u(6, 1), 0.1f, 200.0f, -2.0f, 20));
				else if (random == 1)
					coins.push_back(Coin(&coinsilverTexture, sf::Vector2u(6, 1), 0.1f, 200.0f, -2.0f, 10));
				else if (random == 2)
					coins.push_back(Coin(&coinsilverTexture, sf::Vector2u(6, 1), 0.1f, 200.0f, -160.0f, 10));
				else if (random == 3)
					coins.push_back(Coin(&coingoldTexture, sf::Vector2u(6, 1), 0.1f, 200.0f, -160.0f, 20));
			}
			time_enemy_1 += deltaTime;
			if (time_enemy_1 >= 3)
			{
				time_enemy_1 -= 3;
				if (rand() % 2)
					enemys.push_back(Enemy(&bearTexture, sf::Vector2u(4, 1), 0.4f, 100.0f, 20.0f, 60, 80, -40));
				else
					enemys.push_back(Enemy(&batTexture, sf::Vector2u(2, 1), 0.5f, 100.0f, -120.0f, 80, 60, -30));

			}

			time_item += deltaTime;
			if (time_item >= 13)
			{
				int random = rand() % 6;
				time_item -= 13;
				itemboxs.push_back(Itembox(&itemboxTexture, sf::Vector2u(1, 1), 6.5f, 200.0f, -20.0f, random));
				
			}

			player.Update(deltaTime);
			slide.Update(deltaTime, player.canSlide);
			for (Enemy& enemy : enemys)
			{
				enemy.Update(deltaTime);
			}
			for (Coin& coin : coins)
			{
				coin.Update(deltaTime);
			}
			for (Itembox& itembox : itemboxs)
			{
				itembox.Update(deltaTime);
			}
			sf::Vector2f direction;

			Collider playerCollision = player.GetCollider();
			for (Platform& platform : platforms)
				if (platform.GetCollider().CheckCollision(playerCollision, direction, 1.0f))
					player.OnCollision(direction);
			for (Coin& coin : coins)
				if (coin.GetCollider().CheckCollision(playerCollision, direction, 1.0f))
				{
					coin.body.setPosition(-500, coin.body.getPosition().y);
					if(status==1)
						score += coin.point;
					score += coin.point;
					//printf("%d\n", score);
				}
			for (Enemy& enemy : enemys)
				if (enemy.GetCollider().CheckCollision(playerCollision, direction, 1.0f))
				{
					enemy.body.setPosition(-500, enemy.body.getPosition().y);
					
					if(status==5)
						score -= enemy.point;
					else
						score += enemy.point;
					//printf("%d\n", score);
				}
			for (Itembox& itembox : itemboxs)
				if (itembox.GetCollider().CheckCollision(playerCollision, direction, 1.0f))
				{
					itembox.body.setPosition(-500, itembox.body.getPosition().y);
					if (itembox.key == 0)
					{
						status = 0;
						timess += 5;
					}
					else if (itembox.key == 1)
					{
						status = 1;
					}
					else if(itembox.key == 2)
					{
						status = 2;
						score -= 50;
						
					}
					else if (itembox.key == 3)
					{
						status = 3;
						score -= 100;
					}
					else if (itembox.key == 4)
					{
						status = 3;
						score -= 150;
					}
					else if (itembox.key == 5)
					{
						status = 3;
					}
					

				}

			Collider slideCollision = slide.GetCollider();
			for (Coin& coin : coins)
				if (coin.GetCollider().CheckCollision(slideCollision, direction, 1.0f))
				{
					coin.body.setPosition(-500, coin.body.getPosition().y);
					score += coin.point;
					//printf("%d\n", score);
				}
			for (Enemy& enemy : enemys)
				if (enemy.GetCollider().CheckCollision(slideCollision, direction, 1.0f))
				{
					enemy.body.setPosition(-500, enemy.body.getPosition().y);
					score += enemy.point;
					//printf("%d\n", score);
				}
			for (Itembox& itembox : itemboxs)
				if (itembox.GetCollider().CheckCollision(slideCollision, direction, 1.0f))
				{
					itembox.body.setPosition(-500, itembox.body.getPosition().y);
					if (itembox.key == 0)
					{
						status = 0;
						timess += 5;
					}
					else if (itembox.key == 1)
					{
						status = 1;
					}
					else if (itembox.key == 2)
					{
						status = 2;
						score -= 10;

					}
					else if (itembox.key == 3)
					{
						status = 3;
						score -= 20;
					}
					else if (itembox.key == 4)
					{
						status = 3;
						score -= 30;
					}
					else if (itembox.key == 5)
					{
						status = 3;
					}

				}
			if (timess < 0)
			{
				while (sf::Keyboard::isKeyPressed(sf::Keyboard::A)|| sf::Keyboard::isKeyPressed(sf::Keyboard::W)|| sf::Keyboard::isKeyPressed(sf::Keyboard::S)|| sf::Keyboard::isKeyPressed(sf::Keyboard::D));
				state=2;
			}
			char str[1000];
			sprintf(str, "%.2f", timess);
			clocktext.setString(str);
			if (score < 0)
				state = 3;
			//char str[1000];
			sprintf(str, "%d", score);
			scoretext.setString(str);
			window.clear(sf::Color(150, 150, 150));
			for (Platform& platform : platforms)
				platform.Draw(window);
			bg.Draw(window);
			player.Draw(window);
			for (Enemy& enemy : enemys)
			{
				enemy.Draw(window);
			}
			for (Coin& coin : coins)
			{
				coin.Draw(window);
			}
			for (Itembox& itembox : itemboxs)
			{
				itembox.Draw(window);
			}
			slide.Draw(window);
			window.draw(clockk);
			window.draw(clocktext);
			window.draw(text);
			window.draw(scoretext);
			if (status != -1)
			{
				time_item2 += deltaTime;
				if (time_item2 >= 5.0f)
				{
					time_item2 = 0;
					status = -1;
				}
				if (time_item2 <= 2)
				{
					if (status == 0)
					{
						Showtext(380, 100, "Time up 5 second", 30, window, &font);
					}
					else if (status == 1)
					{
						Showtext(440, 100, "Coin x2", 30, window, &font);
					}
					else if (status == 2)
					{
						Showtext(440, 100, "Score -50", 30, window, &font);
					}
					else if (status == 3)
					{
						Showtext(440, 100, "Score -100", 30, window, &font);
					}
					else if (status == 4)
					{
						Showtext(440, 100, "Score -150", 30, window, &font);
					}
					else if (status == 5)
					{
						Showtext(360, 100, "Switch enemy point 5 second", 30, window, &font);
					}
				}
			}
		}
		if (state == 2)
		{

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && x >= 415.0f && x <= 610.0f && y >= 305.0f && y <= 375.0f)
			{
				state = 0;
				updatascore(namestr, score);
				while (sf::Mouse::isButtonPressed(sf::Mouse::Left));
			}
			name.Draw(window);
			char num[10];
			sprintf(num, "score : %d", score);
			Showtext(400, 100, num, 50, window, &font);
			if (namestr.empty())
				Showtext(220, 160, "Enter name", 100, window, &font);
			else
				Showtext(220, 160, namestr, 100, window, &font);
			//printf("%s\n",namestr);
			//printf("%d %d %d\n", x, y, sf::Mouse::isButtonPressed(sf::Mouse::Left));
		}
		if (state == 3)
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) )
			{
				state = 0;
				while (sf::Mouse::isButtonPressed(sf::Mouse::Left));
			}
			over.Draw(window);
		}
		if (state == 4)
		{
			//printf("%d %d %d\n", x, y, sf::Mouse::isButtonPressed(sf::Mouse::Left));
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && x >= 440.0f && x <= 595.0f && y >= 425.0f && y <= 495.0f)
			{
				state = 0;
				while (sf::Mouse::isButtonPressed(sf::Mouse::Left));
			}
			scoreboard.Draw(window);
			Showscoreboard(window);
		}
		if (state == 5)
		{
			//printf("%d %d %d\n", x, y, sf::Mouse::isButtonPressed(sf::Mouse::Left));
			pause.Draw(window);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && x >= 425.0f && x <= 635.0f && y >= 130.0f && y <= 200.0f)
			{
				state = 1;
				while (sf::Mouse::isButtonPressed(sf::Mouse::Left));
			}
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && x >= 425.0f && x <= 635.0f && y >= 250.0f && y <= 330.0f)
			{
				state = 0;
				while (sf::Mouse::isButtonPressed(sf::Mouse::Left));
			}
		}






		window.display();
	}



	return 0;
}

