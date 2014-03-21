/*
 * Spectrum.h
 *
 *  Created on: Feb 19, 2014
 *      Author: vlad
 */

#ifndef SPECTRUM_H_
#define SPECTRUM_H_

#include "vector"
#include "Riostream.h"
#include "TGraph.h"
#include "MathModel.h"
#include "TF1.h"

class Spectrum {
public:
	Spectrum();
	Spectrum(string, string);
	virtual ~Spectrum();

	void Init(string, string);
	void Test();

	void Fit(MathModel* );
	void Write();

	double GetAmp(int);
	double GetMean(int);

private:
	int nop;
	vector<double> x;
	vector<double> y;
	unsigned int numberOfPoints;
	TGraph *gr;
	TF1 *ftot;
	TF1** fpart;

	void FillX(string);
	void FillY(string);

	size_t Min(size_t, size_t);
};

#endif /* SPECTRUM_H_ */
