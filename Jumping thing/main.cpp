#include "pch.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include <iostream>
#include <sstream>
#include <list>
using namespace sf;

struct point
{
	int x, y;
};

int main()
{
	srand(time(0));

	//400, 533 original
	RenderWindow app(VideoMode(533, 533), "Some kind of game!");
	app.setFramerateLimit(60);


	///////////////// variables ///////////////////
	int x = 100, y = 100, h = 200, score = 0, skinTime = 0, distanceForShow = 0;
	float dx = 0, dy = 0, distance = 0;

	Texture t1, t2, t3, t4, t5, t6;
	t1.loadFromFile("images/background.png");
	t2.loadFromFile("images/platform.png");
	t3.loadFromFile("images/doodle.png");
	t4.loadFromFile("images/game_over.png");
	t5.loadFromFile("images/doodle2.png");
	t6.loadFromFile("images/fruit.png");

	Music music;
	music.openFromFile("audio/Over.ogg");
	music.play();
	music.setLoop(true);


	Font font;
	font.loadFromFile("fonts/American_Captain.ttf");

	Sprite sBackground(t1), sPlat(t2), sPers(t3), sgameOver(t4), sPersTwo(t5), sPersDefault(t3), sFruit(t6);
	point plat[20], fr[1];

	Clock vrijeme, distanceT;

	// randomly generates platforms
	for (int i = 0; i < 6; i++) {
		plat[i].x = rand() % 450;
		plat[i].y = rand() % 533;
		//if (((plat[i - 1].y + 30) > plat[i].y) && ((plat[i - 1].y - 30) < plat[i].y)) plat[i].y -= 30;
		//if ((plat[i - 1].x + 30) < plat[i].x) plat[i].x -= 50;
   	}

	for (int i = 0; i < 1; i++) {
		fr[i].x = rand() % 533;
		fr[i].y = rand() % 7000;
	} 

	//////////////////////////// game loop ////////////////////////////////
	while (app.isOpen()){
		Event e;
		while (app.pollEvent(e)) {
			if (e.type == Event::Closed)
				app.close();
		}

	// Keyboard
	if (Keyboard::isKeyPressed(Keyboard::Right)) x += 3;
	if (Keyboard::isKeyPressed(Keyboard::Left)) x -= 3;
	if (Keyboard::isKeyPressed(Keyboard::BackSpace)) app.close();
	if (Keyboard::isKeyPressed(Keyboard::Space)) sPers.setColor(Color (255, 000, 000));
	if (Keyboard::isKeyPressed(Keyboard::C)) sPers = sPersTwo;
	if (Keyboard::isKeyPressed(Keyboard::LShift)) sPers = sPersDefault;
	if (Keyboard::isKeyPressed(Keyboard::S)) dy = -50;



	// jumping
	float g, k;
	dy += 0.18; // how long the jump is (0.1 is long, 0.5 is short)
	if (dy > 0) dy += 0.30; // quicker falling
	y += dy;
	k = dy;
	g = y;

	// move screen up
	if (y < h) // this line -> platforms don't go up when you fall down; h is the middle, and y is blocked from going over (under) 200 by y = h!
		for (int i = 0; i < 6; i++){
			y = h;
			plat[i].y = plat[i].y - dy;
			if (plat[i].y > 533) {
				plat[i].y = 0; 
				plat[i].x = rand() % 450;
				//if (((plat[i - 1].y + 30) > plat[i].y) && ((plat[i - 1].y - 30) < plat[i].y)) plat[i].y -= 30;
				//if ((plat[i - 1].x + 30) < plat[i].x) plat[i].x -= 50;
				if (plat[i].x < 40) plat[i].x = 50;

			}
		}
	if (g < h)
		for (int i = 0; i < 1; i++) {
			g = h;
			fr[i].y = fr[i].y - k;
			if (fr[i].y > 533) { fr[i].y = -5000; fr[i].x = rand() % 533; }
		} 

	// jump from platform; score; dy > 0 means not getting hit by platform from below
	for (int i = 0; i < 6; i++)
		if ((x + 49 > plat[i].x) && (x < plat[i].x + 35)
			&& (y + 70 > plat[i].y) && (y + 56 < plat[i].y) && (dy > 0)) {
			dy = -10;
			score++;
			plat[i].x = 550;
			plat[i].y = 600;
			}

		float timer = 0, tTimer = 0;
		int time = 0, tTime = 0;
		timer = vrijeme.getElapsedTime().asSeconds();
		timer = ceilf(timer * 100) / 100;
		tTimer = distanceT.getElapsedTime().asSeconds();
		time += timer;
		tTime += tTimer;
		
		// distance calculation
		if (dy < 0){
			float ddy = fabs(dy);
			distance += tTimer * 1.2 * ddy;
			distanceT.restart();
			distanceForShow = distance;
		}
		else if (dy > 0) distanceT.restart();

		// fruit effect
		if ((x + 35 > fr[0].x) && (x < fr[0].x + 35) // first is to the left, second to the right
			&& (y + 75 > fr[0].y) && (y + 10 < fr[0].y)) { // first number below, second above
			sPers.setColor(Color(000, 255, 000));
			dy = -30;
			skinTime = time + 3;
			fr[0].x = 550;
			fr[0].y = 600;
			}

		if (skinTime == time) sPers = sPersDefault;
		
	
	sPers.setPosition(x, y);

	///// draw /////
	app.draw(sBackground);
	for (int i = 0; i < 2; i++) {
		sFruit.setPosition(fr[i].x, fr[i].y);
		app.draw(sFruit);
	}
	app.draw(sPers);
	for (int i = 0; i < 6; i++)
	{
		sPlat.setPosition(plat[i].x, plat[i].y);
		app.draw(sPlat);
	}

	// Counter
	std::stringstream ss, ssg, sst;
	ss << "Score: " << score /* << "   \n" << y << " " << dy << "  \n" << x << " " << dx */
		<< "\nDistance: " << distanceForShow
		<< "\nElapsed time: " << timer;

	Text text;
	text.setFont(font);
	text.setString(ss.str());
	text.setCharacterSize(20); // in pixels, not points!
	text.setFillColor(Color::White);
	//text.setStyle(Text::Bold);
	text.setPosition(16, 10);
	app.draw(text);

	// blocking character from exiting screen
	if (x > 467) x = 467;
	if (x < -22) x = -22;
	if (y > 750) { // game over screen
		app.draw(sgameOver); 
		music.pause();
			
		ssg << "Your score is: " << score << "\nDistance traveled: " << distanceForShow << " meters";
		Text gameOverScore;
		gameOverScore.setFont(font);
		gameOverScore.setString(ssg.str());
		gameOverScore.setCharacterSize(30);
		gameOverScore.setFillColor(Color::White);
		gameOverScore.setPosition(110, 118);
		app.draw(gameOverScore);
		
		if (time % 2 == 0) {
			Text tryAgain;
			tryAgain.setFont(font);
			tryAgain.setString("  Press Enter\nto try again!");
			tryAgain.setCharacterSize(80);
			tryAgain.setFillColor(Color::White);
			tryAgain.setPosition(90, 290);
			app.draw(tryAgain);
		} 

			if (Keyboard::isKeyPressed(Keyboard::Enter)){ // restart
				//gmusic.stop();
				music.play();
				score = 0;
				y = 0;
				x = 235;
				dy = -10;
				distance = 0;
				sPers.setColor(Color(255, 255, 255));
				vrijeme.restart();
					}
	}

	app.display();
	}
}