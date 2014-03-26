/*
 * SpectrumAnalysis.cpp
 *
 *  Created on: Feb 23, 2014
 *      Author: vlad
 */

#include "SpectrumAnalysis.h"
#include "stdlib.h"
#include "TMath.h"

SpectrumAnalysis::SpectrumAnalysis(string configurationFile)
{
	f_out = new TFile("nReport.root","RECREATE");

	LoadConfigData(configurationFile);
	LoadSpectrumData();

	centers = new double*[model->GetNumberOfPeaks()];
	amplitudes = new double*[model->GetNumberOfPeaks()];
	partialAreas = new double*[model->GetNumberOfPeaks()];

	resGraphs = new TGraph*[model->GetNumberOfPeaks()];
	for(int i=0; i<model->GetNumberOfPeaks(); i++) {
		centers[i] = new double[numberOfSpectrums];
		amplitudes[i] = new double[numberOfSpectrums];
		partialAreas[i] = new double[numberOfSpectrums];

		resGraphs[i] = new TGraph();
	}
}

SpectrumAnalysis::~SpectrumAnalysis() {
	for(int i = 0 ;i < numberOfSpectrums ; i++) {
		delete [] allSpectrums[i];
	}
	delete [] allSpectrums;

	for(int i = 0; i < model->GetNumberOfPeaks() ; i++) {
		delete [] centers[i];
		delete [] amplitudes[i];
		delete [] partialAreas[i];

		delete [] resGraphs[i];
	}
	delete [] centers;
	delete [] amplitudes;
	delete [] partialAreas;

	delete [] resGraphs;

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
		allSpectrums[i] = new Spectrum(times[i], dataPath + "/" + dataFileNames[i]);
	}
}

void SpectrumAnalysis::FitAll()
{
	for (int i = 0; i < numberOfSpectrums; ++i) {
		allSpectrums[i]->Fit(model);
	}
}

void SpectrumAnalysis::WriteAll(string pdfname)
{
	for (int i = 0; i < numberOfSpectrums; ++i) {
		allSpectrums[i]->Write();
	}
	allSpectrums[0]->WriteToPDF(pdfname, 'o');
	for (int i = 1; i < numberOfSpectrums-1; ++i) {
		allSpectrums[i]->WriteToPDF(pdfname);
	}
	allSpectrums[numberOfSpectrums-1]->WriteToPDF(pdfname, 'f');

	for (int p = 0; p < model->GetNumberOfPeaks()-1; ++p) {
		resGraphs[p]->Write();
//		resGraphs[p]->Print(pdfname, Form("Graph"));
	}
}

void SpectrumAnalysis::Analyze()
{
	double t_mean = 0.;
	double t_disp = 0.;
	int  k = 0;

	for (int i = 0; i < 10; ++i) {
		FitAll();
		GetFitResults();
		k = 0;
		for (int j = 0; j < model->GetNumberOfPeaks(); ++j) {

			t_mean = saMean(centers[j], numberOfSpectrums);
			t_disp = saDisp(centers[j], numberOfSpectrums);
			if (t_disp > 1.) {
				k = 1;
				model->SetMeanLimits(j, t_mean - k * t_disp/(i+1), t_mean + k * t_disp/(i+1));
			} else {
				k++;
			}
			cout << "!------------------ Peak "<< j+1 <<"------------------!"<< endl;
			cout << "---------- Mean: "<< t_mean <<"---------- Disp: "<< t_disp << endl;
			for (int sp = 0; sp < numberOfSpectrums; ++sp) {
				cout << centers[j][sp] << endl;
			}
		}
		if (k==model->GetNumberOfPeaks()) break;
	}

	WriteAll("results.pdf");
}

void SpectrumAnalysis::GetFitResults()
{
	for (int p = 0; p < model->GetNumberOfPeaks(); ++p) {
		for (int sp = 0; sp < numberOfSpectrums; ++sp) {
			amplitudes[p][sp] = allSpectrums[sp]->GetAmp(p);
			centers[p][sp] = allSpectrums[sp]->GetMean(p);
			partialAreas[p][sp] = allSpectrums[sp]->GetPartialArea(p);

			resGraphs[p]->SetPoint(sp, times[sp], partialAreas[p][sp]);
		}
	}
}

double SpectrumAnalysis::saMean(const double* array, int size)
{
	double sum = 0;
	for (int i = 0; i < size; ++i) {
		sum += array[i];
	}
	return sum/size;
}

double SpectrumAnalysis::saDisp(const double* array, int size)
{
	double sum = 0;
	double xc = saMean(array, size);
	for (int i = 0; i < size; ++i) {
		sum += (array[i] - xc) * (array[i] - xc);
	}
	return TMath::Sqrt(sum/size);
}



