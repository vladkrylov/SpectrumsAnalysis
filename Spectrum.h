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
#include "TCanvas.h"
#include "TLegend.h"

class Spectrum {
public:
	Spectrum();
	Spectrum(int spectrumTime, string);
	virtual ~Spectrum();

	void Init(string);
	void Test();

	void Fit(MathModel* );
	void Write();
	void WriteToPDF(string pdfname, char mode = 'c');

	double GetAmp(int peakId);
	double GetMean(int peakId);
	double GetArea(int peakId);
	double GetPartialArea(int peakId);

private:
	int nop;
	int spectrum_time;
	vector<double> x;
	vector<double> y;
	unsigned int numberOfPoints;
	string name;
	TCanvas* c;
	TLegend *legend;
	TGraph *gr;
	TF1 *ftot;
	TF1** fpart;
	double* params;
	double fullArea;

	void FillX(string);
	void FillY(string);
	void Fill(string);

	size_t Min(size_t, size_t);
};

#endif /* SPECTRUM_H_ */
