#include <SFML/Graphics.hpp>

#include <complex>
#include <iostream>

#include <math.h>

#define WIDTH 800
#define HEIGHT 600

#define ITS 0

int c_x, c_y = 0; // Current x and y position

double rbound_high = 1.0; // The complex plane bounds the window is mapped to.
double rbound_low = -2.0; // The real bounds...

double ibound_high = 1.0; // ...and the imaginary ones.
double ibound_low = -1.0;

bool done = false; // A flag for if the calculation is done.

sf::Clock timeClock;
sf::Time timeFinished;

bool printed = false; // A flag for if the time was already printed.

// This function gets the mapped complex equivalent to an (x, y) coordinate pair.
std::complex<double> getC(int x, int y) {
	std::complex<double> comp;

	comp.real(rbound_low + (rbound_high - rbound_low) * (double)x / (double)WIDTH); // (double) to force double division instead of idiv
	comp.imag(ibound_low + (ibound_high - ibound_low) * (double)y / (double)HEIGHT);

	return comp;
}

// The mandelbrot set function.
std::complex<double> m(std::complex<double> z, std::complex<double> c) {
	return z * z + c;
}

// This function iterates the m(z, c) function up to ITS times and checks if the bound (in this case sqrt(2)) is reached.
bool iter(std::complex<double> c) {
	std::complex<double> res;
	res.real(0.0); // Set the first z value to 0 + 0i.
	res.imag(0.0);

	for (int i = 0; i < ITS; i++) {
		res = m(res, c);
	}

	if (std::abs(res) > sqrt(2))
		return false;
	
	return true;
}

// Calculates the next coordinate. Simulates two nested for loops.
bool nextStep(void) {
	bool result;

	result = iter(getC(c_x, c_y));

	c_x++;
	if (c_x == WIDTH) { // If c_x reached the limit
		c_x = 0;
		c_y++;

		if (c_y == HEIGHT) { // If c_y reached the limit
			c_x = WIDTH - 1; // To avoid drawing outside of the image.
			c_y = HEIGHT - 1;
			done = true;

			timeFinished = timeClock.getElapsedTime(); // Get the elapsed time.
		}
	}

	return result;
}

int main(int argc, char **argv) {
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Mandelbrot Set Viewer");

	sf::Image screen;
	screen.create(WIDTH, HEIGHT, sf::Color::White);

	timeClock.restart(); // Set the clock to 0, because the clock starts counting at creation.

	while (window.isOpen()) {
		sf::Event event;
		
		while (window.pollEvent(event)) { // Closes the window at a close event.
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if (!done) {
			if (nextStep()) // Calculate if the next point is in the set and add it (or not).
				screen.setPixel(c_x, c_y, sf::Color::Black);

		} else if (!printed) { // If everything's done, print the elapsed time.
			std::cout << "Time elapsed when finished drawing: " << timeFinished.asSeconds() << "s." << std::endl;
			printed = true;
		}

		sf::Texture tex; // Make the sf::Image drawable.
		tex.loadFromImage(screen);
		sf::Sprite spr;
		spr.setTexture(tex);

		window.clear();

		window.draw(spr);

		window.display();
	}
}