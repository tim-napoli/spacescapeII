/*
 * Tâches du mode SinglePlayer.
 */

#ifndef _solo_Tasks_hpp_
#define _solo_Tasks_hpp_
 
#include "lab/activity/Task.hpp"
#include "lab/graphic/Renderer.hpp"
#include "lab/graphic/Text.hpp"
#include "lab/event/Event.hpp"

class Game;

class GameTask : public lab::activity::Task {
	protected:
		static Game* game;
	
	public:
		GameTask ();
		
		~GameTask ();
		
		virtual void execute (const lab::event::Event& event) const = 0;
		
		static void setGame (Game* game);
};


class SwitchExitTask : public GameTask {
	public:
		SwitchExitTask () : GameTask () {};
		
		~SwitchExitTask () {};
		
		void execute (const lab::event::Event& event) const {
			(void) event;
			GameTask::game->switchExit ();
		}
};

class ExitTask : public GameTask {
	public:
		ExitTask () : GameTask () {};
		
		~ExitTask () {};
		
		void execute (const lab::event::Event& event) const {
			(void) event;
			GameTask::game->exit ();
		}
};

class RestartTask : public GameTask {
	public:
		RestartTask () : GameTask () {};
		
		~RestartTask () {};
		
		void execute (const lab::event::Event& event) const {
			(void) event;
			GameTask::game->mToRestart = true;
		}
};

class SwitchPauseTask : public lab::activity::Task {
	private:
		int* mGameState;
		lab::graphic::Renderer* mRenderer;
		lab::graphic::Text* mText;
		
	public:
		SwitchPauseTask (int* game_state, lab::graphic::Renderer* renderer, lab::graphic::Text* text);
		
		~SwitchPauseTask ();
		
		void execute (const lab::event::Event& event) const;
};

class SwitchMusicTask : public lab::activity::Task {
	private:
		Game* mGame;
		
	public:
		SwitchMusicTask (Game* game);
		
		~SwitchMusicTask ();
		
		void execute (const lab::event::Event& event) const;
};

class NameSeizureTask : public GameTask {

	public:
		NameSeizureTask () : GameTask () {};
		~NameSeizureTask () {};

		void execute (const lab::event::Event& event) const {
			int keycode = event.getParameter ("keycode").getValue<int> ();
			int unichar = event.getParameter ("unichar").getValue<int> ();
			ALLEGRO_USTR* name = GameTask::game->mNameSeizureText->getText ();
	
			if (keycode == ALLEGRO_KEY_BACKSPACE) {
				if (al_ustr_length (name) > 0) {
					int offset = al_ustr_offset (name, al_ustr_length (name) - 1);
					al_ustr_remove_chr (name, offset);
				}
			}
			else if (al_ustr_length (name) < 32) {
				ALLEGRO_USTR* chars = al_ustr_new ("azertuiopqsdfghjklmwxcvbnAZERTYUIOPQSDFGHJKLMWXCVBN0123456789_éèç'\"$£$*ù!:;,.=+-* ");
				if (al_ustr_find_chr (chars, 0, unichar) >= 0) {
					al_ustr_append_chr (name, unichar);
				}
				al_ustr_free (chars);
			}
		}
};

class FinishNameSeizureTask : public GameTask {
	public:
		FinishNameSeizureTask () : GameTask () {};
		
		~FinishNameSeizureTask () {};
		
		void execute (const lab::event::Event& event) const {
			(void) event;
		
			ALLEGRO_USTR* name = GameTask::game->mNameSeizureText->getText ();
			if (al_ustr_length (name) > 0) {
				GameTask::game->mFinishNameSeizure = true;
			}
		}
};

#endif


