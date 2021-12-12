#include "Wrapper.h"
#include "Engine.h"

class subject1 {
public:
	int f1(int x, int y) {
		return x - y;
	}
};

class subject2 {
public:
	int f2(int x) {
		return x * 4;
	}
};

void testProcess() {
	engine eng;

	subject1 subj1;
	subject2 subj2;

	wrapper wrap1(&subj1, &subject1::f1, {{"x", 0}, {"y", 0}});
	wrapper wrap2(&subj2, &subject2::f2, { {"x", 5}});

	eng.command("example1", &wrap1);
	eng.command("example2", &wrap2);

	std::cout << "Correct work" << std::endl;

	std::cout << "Example 1: " << eng.execute("example1", { { "x", 1 }, { "y", 2} }) << std::endl;
	std::cout << "Example 2: " << eng.execute("example2", {{ "x", 5 }}) << std::endl;

	std::cout << "Too many arguments example 1" << std::endl;
	try{
		std::cout << eng.execute("example1", { { "x", 1},  { "x", 2},  { "x", 3} }) << std::endl;
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}

	std::cout << "Not enough arguments example 1" << std::endl;
	try {
		std::cout << eng.execute("example1", {}) << std::endl;
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	
	std::cout << "Not enough arguments example 2" << std::endl;
	try {
		std::cout << eng.execute("example2", {}) << std::endl;
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}

	std::cout << "Wrong command example 1" << std::endl;
	try {
		std::cout << eng.execute("exampl1", { { "x", 1},  { "x", 2} }) << std::endl;
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}

	std::cout << "Wrong command example 2" << std::endl;
	try {
		std::cout << eng.execute("exampl2", { { "x", 1} }) << std::endl;
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}

int main() {
  testProcess();
	return 0;
}
