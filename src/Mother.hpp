#ifndef _Mother_hpp_
#define _Mother_hpp_

#include <list>
#include <string>

#include "lab/Exception.hpp"
#include "ennemies/Ennemy.hpp"

class Mother {
	private:
		std::list<ennemy::Ennemy*>* mEnnemies;
		//std::list<Bonus*>* mBonus;
		
		void giveBirth (const std::string& name) throw lab::Exception;
};

#endif

