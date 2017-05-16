#include "solo/Game.hpp"
#include "solo/Tasks.hpp"

/*************************************************** Game Task ********************************************************/
Game* GameTask::game = NULL;

GameTask::GameTask () {

}

GameTask::~GameTask () {

}

void GameTask::setGame (Game* g) {
	GameTask::game = g;
}

/*************************************************** Switch Pause Task ************************************************/
SwitchPauseTask::SwitchPauseTask (int* game_state, lab::graphic::Renderer* renderer, lab::graphic::Text* text) {
	mGameState = game_state;
	mRenderer = renderer;
	mText = text;
}

SwitchPauseTask::~SwitchPauseTask () {

}

void SwitchPauseTask::execute (const lab::event::Event& event) const {
	(void) event;
	if (*mGameState == Game::STATE_PAUSE) {
		mRenderer->removeDrawable (mText);
		*mGameState = Game::STATE_PLAY;
	}
	else if (*mGameState == Game::STATE_PLAY) {
		*mGameState = Game::STATE_PAUSE;
		mRenderer->addDrawable (mText);
	}
}

/*************************************************** Switch music task ************************************************/
SwitchMusicTask::SwitchMusicTask (Game* game) {
	mGame = game;
}
		
SwitchMusicTask::~SwitchMusicTask () {

}

void SwitchMusicTask::execute (const lab::event::Event& event) const {
	(void) event;
	mGame->music ();
}


