#include <iostream>
#include <fstream>
#include <cstring>

#include "lab/util/Value.hpp"
#include "Score.hpp"

using namespace lab;
using namespace lab::graphic;
using namespace lab::math;

Score::Score (ALLEGRO_FONT* normal, ALLEGRO_FONT* little) :
		Drawable (Vector<int> (), Vector<int> (), Vector<int> (), 0.0f, 102) {
	mNumScores = 0;
	
	mNormalFont = normal;
	mLittleFont = little;
	
	mScoreText = new Text (Vector<int> (480, 140), Vector<int> (), 0.0f, 0, mNormalFont, al_map_rgb (0, 0, 200), 
						   "Best Scores", Text::ALIGN_CENTER);
}

Score::~Score () {
	delete mScoreText;
	for (int i = 0; i < mNumScores; i++) {
		al_ustr_free (mScores [i].name);
		delete mNameTexts [i];
		delete mScoreTexts [i];
	}
}

void Score::load (const std::string& path) {
	mNumScores = 0;

	std::ifstream file;
	file.open (path, std::ios::binary);
	if (file.is_open ()) {
		long score;
		char buf [256];
		int buf_size;
		
		while (!file.eof () && mNumScores < 10) {
			file.read ((char*) &score, sizeof (long));
			file.read ((char*) &buf_size, sizeof (int));
			file.read (buf, buf_size);
			
			if (!file.eof ()) {
				buf [buf_size] = '\0';
			
				mScores [mNumScores].score = score;
				mScores [mNumScores].name = al_ustr_new_from_buffer (buf, buf_size);
			
				// Construction des textes graphiques
				util::Value val (score);
				mScoreTexts [mNumScores] = new Text (Vector<int> (490, 180 + mNumScores * 16), Vector<int> (), 0.0f, 0,
													 mLittleFont, al_map_rgb (0, 255 - mNumScores * 25, mNumScores * 12), 
													 val.getValue (), Text::ALIGN_LEFT);
				mNameTexts [mNumScores]  = new Text (Vector<int> (470, 180 + mNumScores * 16), Vector<int> (), 0.0f, 0,
													 mLittleFont, al_map_rgb (0, 255 - mNumScores * 25, mNumScores * 12), 
													 buf, Text::ALIGN_RIGHT);
			
				mNumScores++;
			}
		}
		
		file.close ();
	}
}

void Score::save (const std::string& path) throw (lab::Exception) {
	std::ofstream file;
	file.open (path, std::ios::binary);
	if (file.is_open ()) {
		long score;
		
		for (int i = 0; i < mNumScores; i++) {
			score = mScores [i].score;
		
			file.write ((char*) &score, sizeof (long));
			
			
			char buffer [256] = "";
			al_ustr_to_buffer (mScores [i].name, buffer, 256);
			int buf_size = strlen (buffer);
			file.write ((char*) &buf_size, sizeof (int));
			file.write (buffer, buf_size);
		}

		file.close ();
	}
	else {
		throw lab::Exception (0, "Score::save error : Cannot write file " + path + ".");
	}
}

void Score::draw () const {
	ALLEGRO_TRANSFORM saved;
	
	al_copy_transform (&saved, al_get_current_transform ());

	mScoreText->getReady ();
	mScoreText->draw ();
	al_use_transform (&saved);
	
	for (int i = 0; i < mNumScores; i++) {
		mScoreTexts [i]->getReady ();
		mScoreTexts [i]->draw ();
		al_use_transform (&saved);
		mNameTexts [i]->getReady ();
		mNameTexts [i]->draw ();
		al_use_transform (&saved);
	}
}

bool Score::isIn (long score) const {
	if (mNumScores < 10) {
		return true;
	}

	for (int i = 0; i < mNumScores; i++) {
		if (score > mScores [i].score) {
			return true;
		}
	}
	
	return false;
}

void Score::add (ALLEGRO_USTR* name, long score) {
	if (mNumScores < 10) {
		int off = 0;
		
		while (mScores [off].score > score && off < mNumScores) {
			off++;
		}
	
		for (int i = mNumScores; i > off; i--) {
			mScores [i] = mScores [i - 1];
			
			mScoreTexts [i] = mScoreTexts [i - 1];
			mScoreTexts [i]->setPosition (Vector<int> (490, 180 + i * 16));
			mScoreTexts [i]->setColor (al_map_rgb (0, 255 - i * 25, i * 12));
			
			mNameTexts [i] = mNameTexts [i - 1];
			mNameTexts [i]->setPosition (Vector<int> (470, 180 + i * 16));
			mNameTexts [i]->setColor (al_map_rgb (0, 255 - i * 25, i * 12));
		}
		
		mScores [off].score = score;
		mScores [off].name = al_ustr_dup (name);
		
		util::Value val (score);
		mScoreTexts [off] = new Text (Vector<int> (490, 180 + off * 16), Vector<int> (), 0.0f, 0,
											 mLittleFont, al_map_rgb (255, 255, 255), 
											 val.getValue (), Text::ALIGN_LEFT);
		mNameTexts [off]  = new Text (Vector<int> (470, 180 + off * 16), Vector<int> (), 0.0f, 0,
											 mLittleFont, al_map_rgb (255, 255, 255), 
											 name, Text::ALIGN_RIGHT);
		
		mNumScores++;
	}
	else {
		for (int i = 0; i < mNumScores; i++) {
			if (score > mScores [i].score) {
			
				delete mScoreTexts [9];
				delete mNameTexts [9];
				al_ustr_free (mScores [9].name);
			
				for (int j = 9; j > i; j--) {
					mScores [j] = mScores [j - 1];
			
					mScoreTexts [j] = mScoreTexts [j - 1];
					mScoreTexts [j]->setPosition (Vector<int> (490, (180 + j * 16)));
					mScoreTexts [j]->setColor (al_map_rgb (0, 255 - j * 25, j * 12));
			
					mNameTexts [j] = mNameTexts [j - 1];
					mNameTexts [j]->setPosition (Vector<int> (470, (180 + j * 16)));
					mNameTexts [j]->setColor (al_map_rgb (0, 255 - j * 25, j * 12));
				}
			
				
			
				mScores [i].score = score;
				mScores [i].name = al_ustr_dup (name);
		
				util::Value val (score);
				mScoreTexts [i] = new Text (Vector<int> (490, 180 + i * 16), Vector<int> (), 0.0f, 0,
											mLittleFont, al_map_rgb (255, 255, 255), 
											val.getValue (), Text::ALIGN_LEFT);
				mNameTexts [i]  = new Text (Vector<int> (470, 180 + i * 16), Vector<int> (), 0.0f, 0,
											mLittleFont, al_map_rgb (255, 255, 255), 
											name, Text::ALIGN_RIGHT);
				
				break;
			}
		}
	}
}

