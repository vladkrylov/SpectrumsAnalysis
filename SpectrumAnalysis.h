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

class SpectrumAnalysis {
public:
	SpectrumAnalysis(string);
	virtual ~SpectrumAnalysis();

	void Analyze();

private:
	string dataPath;
	int numberOfSpectrums;
	string* dataFileNames;
	Spectrum** allSpectrums;
	TFile *f_out;
	MathModel* model;

	double** amplitudes;
	double** centers;

	void LoadConfigData(string);
	void LoadSpectrumData();

	void FitAll();
	void WriteAll();

	void GetFitResults();

	double saMean(const double* , int );
	double saDisp(const double* , int );
};

#endif /* SPECTRUMANALYSIS_H_ */
