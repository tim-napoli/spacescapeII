#ifndef _lab_math_Matrix_hpp_
#define _lab_math_Matrix_hpp_

namespace lab {
namespace math {

/*!
 * \brief A template Matrix class.
 *
 * A Matrix object provides useful functions to manipulate Matrix. 
 */
template <typename T>
class Matrix {
	private:
		unsigned long mWidth, mHeight;
		std::vector<T> mCols;

	public:
		Matrix (unsigned long width, unsigned long height);

		Matrix (const Matrix& m);

		~Matrix ();

		int getWidth () const {return mWidth;}

		int getHeight () const {return mHeight;}

		std::vector<T>& operator [] (unsigned long col);

		Matrix<T> operator = (const Matrix<T>& m) const;

		Matrix<T> operator + (const Matrix<T>& m) const;

		Matrix<T> operator - (const Matrix<T>& m) const;

		Matrix<T> operator * (const Matrix<T>& m) const throw (lab::Exception);

		Matrix<T> operator * (T coef);

		Matrix<T>& operator += (const Matrix<T>& m);

		Matrix<T>& operator -= (const Matrix<T>& m);

		Matrix<T>& operator *= (const Matrix<T>& m) throw (lab::Exception);

		Matrix<T>& operator *= (T coef) throw (lab::Exception);
};

}}

#endif

