#include <SFML/Graphics.hpp>

#include <complex>
#include <iostream>

#include <math.h>

#define WIDTH 800
#define HEIGHT 600

#define ITS 0

int c_x, c_y = 0; // Current x and y position

double rbound_high = 1.0;
double rbound_low = -2.0;

double ibound_high = 1.0;
double ibound_low = -1.0;

bool done = false;

sf::Clock timeClock;
sf::Time timeFinished;

bool printed = false;

std::complex<double> getC(int x, int y) {
	std::complex<double> comp;

	comp.real(rbound_low + (rbound_high - rbound_low) * (double)x / (double)WIDTH); // (double) to force double division instead of idiv
	comp.imag(ibound_low + (ibound_high - ibound_low) * (double)y / (double)HEIGHT);

	return comp;
}

std::complex<double> m(std::complex<double> z, std::complex<double> c) {
	return z * z + c;
}

bool iter(std::complex<double> c) {
	std::complex<double> res;
	res.real(0.0);
	res.imag(0.0);

	for (int i = 0; i < ITS; i++) {
		res = m(res, c);
	}

	if (std::abs(res) > sqrt(2))
		return false;
	
	return true;
}

bool nextStep(void) {
	bool result;

	result = iter(getC(c_x, c_y));

	c_x++;
	if (c_x == WIDTH) {
		c_x = 0;
		c_y++;

		if (c_y == HEIGHT) {
			c_x = WIDTH - 1;
			c_y = HEIGHT - 1;
			done = true;

			timeFinished = timeClock.getElapsedTime();
		}
	}

	return result;
}

int main(int argc, char **argv) {
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Mandelbrot Set Viewer");

	sf::Image screen;
	screen.create(WIDTH, HEIGHT, sf::Color::White);

	timeClock.restart();

	while (window.isOpen()) {
		sf::Event event;
		
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if (!done) {
			if (nextStep())
				screen.setPixel(c_x, c_y, sf::Color::Black);
		} else if (!printed) {
			std::cout << "Time elapsed when finished drawing: " << timeFinished.asSeconds() << "s." << std::endl;
			printed = true;
		}

		sf::Texture tex;
		tex.loadFromImage(screen);
		sf::Sprite spr;
		spr.setTexture(tex);

		window.clear();

		window.draw(spr);

		window.display();
	}
}