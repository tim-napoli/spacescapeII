#ifndef _lab_gui_Gui_hpp_
#define _lab_gui_Gui_hpp_

namespace lab {
namespace gui {

class Gui : public lab::event::Listener, public lab::graphic::Drawable {
	private:
		std::list<Element*> mElements;
		std::list<Element*>::iterator mElementIt;
	
	public:
		Gui ();
		
		~Gui ();
	
		void notify (const lab::event::Event& event);
		
		void draw () const;
};

}}

#endif

