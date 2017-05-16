#ifndef _lab_util_Heightmap_hpp_
#define _lab_util_Heightmap_hpp_

#include <vector>

namespace lab {
namespace util {

template <typename T>
class Heightmap {
	private:
		int mWidth, mHeight;
		std::vector<T>* mLines;

		void generate (int x1, int y1, int x2, int y2, double coef);

	public:
		Heightmap (int width, int height);

		~Heightmap ();

		void generate (T base_height, double coef);

		std::vector<T>& operator [] (int x);

		int getWidth () const {return mWidth;}
		int getHeight () const {return mHeight;}
};

template <typename T>
Heightmap::Heightmap (int width, int height) {
	mLines = new std::vector<T> [width];
	for (int i = 0; i < width; i++) {
		mLines [i].resize (height);
		for (int j = 0; j < height; j++) {
			mLines [i] [j] = 0;
		}
	}

	mWidth = width;
	mHeight = height;
}

template <typename T>
Heightmap::~Heightmap () {
	delete [] mLines;
}

template <typename T>
void Heightmap::generate (int x1, int y1, int x2, int y2, double coef) {
	if (x1 != x2 && y1 != y2) {
		int x = x1 + ((x2 - x1) >> 1);
		int y = y1 + ((y2 - y1) >> 1);

		mLines [x] [y] = ((mLines [x1] [y1] + mLines [x1] [y2] + mLines [x2] [y1] + mLines [x2] [y2]) >> 2) + coef * rand () % 100 - coef * 50;
		mLines [x] [y1] = ((mLines [x1] [y1] + mLines [x2] [y1]) >> 1) + coef * rand () % 100 - coef * 50;
		mLines [x1] [y] = ((mLines [x1] [y1] + mLines [x1] [y2]) >> 1) + coef * rand () % 100 - coef * 50;
		mLines [x2] [y] = ((mLines [x2] [y1] + mLines [x2] [y2]) >> 1) + coef * rand () % 100 - coef * 50;
		mLines [x] [y2] = ((mLines [x1] [y2] + mLines [x2] [y2]) >> 1) + coef * rand () % 100 - coef * 50;

		generate (x1, y1, x, y, coef);
		generate (x, y1, x2, y2, coef);
		generate (x1, y, x, y2, coef);
		generate (x, y, x2, y2, coef);
	}
}

template <typename T>
void Heightmap::generate (T base_height, double coef) {
	mLines [0] [0] = base_height;
	mLines [0] [mHeight - 1] = base_height;
	mLines [mWidth - 1] [mHeight - 1] = base_height;
	mLines [mWidth - 1] [0] = base_height;

	generate (0, 0, mWidth - 1, mHeight - 1, coef);
}

template <typename T>
std::vector<T>& Heightmap::operator [] (int x) {
	return mLines [x];
}

}}

#endif
