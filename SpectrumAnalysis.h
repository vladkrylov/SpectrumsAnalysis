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

private:
	string dataPath;
	int numberOfSpectrums;
	string* dataFileNames;
	Spectrum** allSpectrums;
	TFile *f_out;
	MathModel* model;

	void LoadConfigData(string);
	void LoadSpectrumData();

	void FitAll();
	void WriteAll();
};

#endif /* SPECTRUMANALYSIS_H_ */
