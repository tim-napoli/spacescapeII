#ifndef _Score_hpp_
#define _Score_hpp_

#include <string>

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>

#include "lab/Exception.hpp"
#include "lab/graphic/Drawable.hpp"
#include "lab/graphic/Text.hpp"

typedef struct score_entry {
	ALLEGRO_USTR* name;
	long score;
} score_entry;

class Score : public lab::graphic::Drawable {
	private:
		int mNumScores;
		score_entry mScores [10];
		
		ALLEGRO_FONT *mNormalFont, *mLittleFont;
		
		lab::graphic::Text* mScoreText;
		lab::graphic::Text* mNameTexts [10];
		lab::graphic::Text* mScoreTexts [10];

	public:
		Score (ALLEGRO_FONT* normal, ALLEGRO_FONT* little);
		
		~Score ();
	
		void load (const std::string& path);
		
		void save (const std::string& path) throw (lab::Exception);
	
		void draw () const;
		
		bool isIn (long score) const;
		
		void add (ALLEGRO_USTR* name, long score);
};

#endif

