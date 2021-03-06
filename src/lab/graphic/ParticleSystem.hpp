#ifndef _lab_graphic_ParticleSystem_hpp_
#define _lab_graphic_ParticleSystem_hpp_

#include <list>

#include <allegro5/allegro.h>

#include "lab/math/Vector.hpp"
#include "lab/graphic/Drawable.hpp"

namespace lab {
namespace graphic {

struct particle {
	float x, y, sx, sy, ax, ay;
	int w, h;
	int life;
	ALLEGRO_COLOR color;
	ALLEGRO_BITMAP* bitmap;
};

#define init_particle_addr(part,_x,_y,_sx,_sy,_ax,_ay,_w,_h,_life,_color,_bitmap)	\
part->x = _x;\
part->y = _y;\
part->sx = _sx;\
part->sy = _sy;\
part->ax = _ax;\
part->ay = _ay;\
part->w = _w;\
part->h = _h;\
part->life = _life;\
part->color = _color;\
part->bitmap = _bitmap;

/*!
 * \brief A particle system is an object which will stock some particles of the game, and manage them.
 */
class ParticleSystem : public Drawable {
	private:
		unsigned int mMaxSize;				// The number of particles which can be in this system.
		ALLEGRO_BITMAP* mBuffer; 			// Dissociation of the display buffer and this buffer for blending (to avoid
											// blending on alreday drawn places).
		
		std::list<particle> mParticles;
	
	public:
		/*!
		 * \brief Constructor.
		 * \param dimensions The dimensions of the buffer used by the particle system.
		 * \param max_particles The maximum of particles this system can have.
		 */
		ParticleSystem (math::Vector<int> dimensions, int zindex, unsigned int max_particles);
		
		/*!
		 * \brief Destructor.
		 */
		~ParticleSystem ();
		
		/*!
		 * \brief Add a particle to the particle system.
		 */
		void addParticle(const particle& p);
		
		/*!
		 * \brief Update the particle system.
		 */
		void update ();
		
		/*!
		 * \brief Draw the particles of this system.
		 */
		void draw () const;
		
		/*!
		 * \brief Remove all particles from this system.
		 */
		void clearParticles ();
};

}}

#endif

