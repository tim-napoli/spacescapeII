#ifndef _lab_io_Mouse_hpp_
#define _lab_io_Mouse_hpp_

#include "lab/io/AllegroDevice.hpp"

namespace lab {
namespace io {

/*!
 * \brief The mouse device.
 *
 * The mouse will send events from "mouse" type. Subtypes are :
 * - "down" if a button of the mouse has been pressed ;
 * - "up" if a button of the miuse has been released ;
 * - "move" if the mouse has moved.
 * The parameters of a mouse event are :
 * - "x" The x position of the mouse (on the screen in absolute or scaled to match width video ?) ;
 * - "dx" The distance of the mouse on x since the last move.
 * - "y" The y position of the mouse ;
 * - "dy" The distance of the mouse on y since the last move.
 * - "z" The z position (the wheel) ;
 * - "dz" The distance of the mouse on z since the last move.
 * - "button" The button which has been pressed (can be 1 : left, 3 : right, 2 : middle).
 */
class Mouse : public AllegroDevice {
	public:
		Mouse ();
		
		~Mouse ();
		
		void initialize () throw (lab::Exception);
		
		void shutdown ();
		
		void handleInput ();
		
		void cycle ();
};

}}

#endif

