#ifndef _lab_graphic_ParticleEmitter_hpp_
#define _lab_graphic_ParticleEmitter_hpp_

#include <list>

#include <allegro5/allegro.h>

#include "lab/graphic/ParticleSystem.hpp"

namespace lab {
namespace graphic {

class ParticleEmitter {
	private:
		ParticleSystem* mTarget; // Dissociation of the Buffer of the display and this buffer for blending.
		
		int mSpawnRate, mSpawnNum, mSpawnCount;
	
	public:
		/*!
		 * \brief Constructor.
		 */
		ParticleEmitter (ParticleSystem* target, int spawn_rate, int spawn_num);
		
		/*!
		 * \brief Destructor.
		 */
		virtual ~ParticleEmitter ();
		
		/*!
		 * \brief Generate a particle.
		 */
		virtual void generateParticle (particle* part) = 0;
		
		/*!
		 * \brief Update the particle emitter.
		 */
		virtual void update ();
		
		/*!
		 * \brief Set the spawn rate.
		 */
		void setSpawnRate (int rate) {mSpawnRate = rate;}
		
		/*!
		 * \brief Set the number of particles to spawn.
		 */
		void setSpawnNum (int num) {mSpawnNum = num;}
};

}}

#endif

