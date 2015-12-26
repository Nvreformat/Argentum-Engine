#ifndef MISC_H
#define MISC_H

struct Dimension
{
	double X = 0;
	double Y = 0;

	Dimension(double X, double Y)
	{
		this->X = X;
		this->Y = Y;
	}
	Dimension() {}
};

#endif
