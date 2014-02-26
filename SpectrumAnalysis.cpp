/*
 * SpectrumAnalysis.cpp
 *
 *  Created on: Feb 23, 2014
 *      Author: vlad
 */

#include "SpectrumAnalysis.h"
#include "stdlib.h"

SpectrumAnalysis::SpectrumAnalysis(string configurationFile)
{
	f_out = new TFile("nReport.root","RECREATE");

	LoadConfigData(configurationFile);
	LoadSpectrumData();

	FitAll();
	WriteAll();
}

SpectrumAnalysis::~SpectrumAnalysis() {
	for(int i = 0 ;i < numberOfSpectrums ; i++) {
		delete [] allSpectrums[i];
	}
	delete [] allSpectrums;

	delete [] dataFileNames;

	f_out->Close();
}

void SpectrumAnalysis::LoadConfigData(string configurationFile)
{
	string s;
	ifstream in;
	in.open(configurationFile.c_str());

//	int i = 0;
	size_t cr = 0;
	size_t l = 0;

	// Load path with data
	cr = 8;
	while (in >> s) {
		l = s.length();
		if (l < cr) continue;
		if (s.substr(0,cr) == "DATADIR=") {
			dataPath = s.substr(cr, l-cr);
			cout << dataPath << endl;
		}
		break;
	}

	// Load number of spectrums
	cr = 20;
	while (in >> s) {
		l = s.length();
		if (l < cr) continue;
		if (s.substr(0,cr) == "NUMBER_OF_SPECTRUMS=") {
			numberOfSpectrums = atoi(s.substr(cr, l-cr).c_str());
			cout << numberOfSpectrums << endl;
		}
		break;
	}

	// Load spectrums data filenames
	dataFileNames = new string[numberOfSpectrums];
	cr = 6;
	int sn = 0;
	while (in >> s) {
		l = s.length();
		if (l < cr) continue;

		if ((s.substr(0,1) == "d") && (s.substr(l-4,l) == ".txt")) {
			if (sn < numberOfSpectrums) {
				dataFileNames[sn++] = s;
			}
		}
	}
//	for (int i = 0; i < numberOfSpectrums; ++i) {
//		cout << dataFileNames[i] << endl;
//	}

	in.clear();
	in.close();
}

void SpectrumAnalysis::LoadSpectrumData()
{
	model = new MathModel("model");
	allSpectrums = new Spectrum*[numberOfSpectrums];
	for (int i = 0; i < numberOfSpectrums; ++i) {
		allSpectrums[i] = new Spectrum(dataPath + "/x.txt", dataPath + "/" + dataFileNames[i]);
//		allSpectrums[i]->Fit(model);
//		allSpectrums[i]->Write();
	}
}

void SpectrumAnalysis::FitAll()
{
	for (int i = 0; i < numberOfSpectrums; ++i) {
		allSpectrums[i]->Fit(model);
	}
}

void SpectrumAnalysis::WriteAll()
{
	for (int i = 0; i < numberOfSpectrums; ++i) {
		allSpectrums[i]->Write();
	}
}
