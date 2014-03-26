/*
 * SpectrumAnalysis.h
 *
 *  Created on: Feb 23, 2014
 *      Author: vlad
 */

#ifndef SPECTRUMANALYSIS_H_
#define SPECTRUMANALYSIS_H_

#include "Spectrum.h"
#include "Riostream.h"
#include "TFile.h"
#include "MathModel.h"
#include "TGraph.h"

class SpectrumAnalysis {
public:
	SpectrumAnalysis(string);
	virtual ~SpectrumAnalysis();

	void Analyze();

private:
	int times[12] = {1, 3, 7, 24, 26, 29, 240, 260, 300, 400, 600, 5000};
	string dataPath;
	int numberOfSpectrums;
	string* dataFileNames;
	Spectrum** allSpectrums;
	TFile *f_out;
	MathModel* model;
	TGraph** resGraphs;

	double** amplitudes;
	double** centers;
	double** partialAreas;

	void LoadConfigData(string);
	void LoadSpectrumData();

	void FitAll();
	void WriteAll(string pdfname);

	void GetFitResults();

	double saMean(const double* , int );
	double saDisp(const double* , int );
};

#endif /* SPECTRUMANALYSIS_H_ */
