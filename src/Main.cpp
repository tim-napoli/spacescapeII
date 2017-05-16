#include <iostream>

#include "lab/Engine.hpp"

#include "solo/Game.hpp"

int main (void) {
	lab::Engine engine ("Spacescape II", 60);
	
	engine.addActivity ("Solo", new Game (&engine));
	
	try {
		engine.initialize ();
	} catch (const lab::Exception& exception) {
		std::cerr << "Spacescape II initialize failure :\n\t" << exception.getMessage () << std::endl;
		return 1;
	}
	
	engine.loop ();
	engine.shutdown ();
	
	return 0;
}

