/*
 * MathModel.cpp
 *
 *  Created on: Feb 23, 2014
 *      Author: vlad
 */

#include "MathModel.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>

MathModel::MathModel(string confile) {
	numberOfPeaks = -1;

	ifstream in;
	in.open(confile.c_str());

	string s;
	size_t cr = 0;
	size_t l = 0;

	// Load number of peaks
	cr = 16;
	while (in >> s) {
		l = s.length();
		if (l > cr) {
			if (s.substr(0,cr) == "NUMBER_OF_PEAKS=") {
				numberOfPeaks = atoi(s.substr(cr, l-cr).c_str());
				cout << "Number of peaks = " << numberOfPeaks << endl;
			}
		}
		break;
	}

	amp_min = new double[numberOfPeaks];
	amp_init = new double[numberOfPeaks];
	amp_max = new double[numberOfPeaks];

	mean_min = new double[numberOfPeaks];
	mean_init = new double[numberOfPeaks];
	mean_max = new double[numberOfPeaks];

	sigma_min = new double[numberOfPeaks];
	sigma_init = new double[numberOfPeaks];
	sigma_max = new double[numberOfPeaks];

	// Initializing model data
	for (int i = 0; i < numberOfPeaks; ++i) {
		amp_min[i] = -1.;
		amp_init[i] = -1.;
		amp_max[i] = -1.;

		mean_min[i] = -1.;
		mean_init[i] = -1.;
		mean_max[i] = -1.;

		sigma_min[i] = -1.;
		sigma_init[i] = -1.;
		sigma_max[i] = -1.;
	}

	// Reading model data from config file
	int peakNumber = 0;
	while (in >> s) {
		l = s.length();

		// read amp data
		cr = 8;
		if (l > cr) {
			if (s.substr(1,cr) == "AMP_MIN=") {
				peakNumber = atoi(s.substr(0, 1).c_str());
				if ((peakNumber > 0) && (peakNumber <= numberOfPeaks)) {
					amp_min[peakNumber-1] = atof(s.substr(cr+1, l-cr).c_str());
					cout << s << endl;
					continue;
				}
			}
		}

		cr = 9;
		if (l > cr) {
			if (s.substr(1,cr) == "AMP_INIT=") {
				peakNumber = atoi(s.substr(0, 1).c_str());
				if ((peakNumber > 0) && (peakNumber <= numberOfPeaks)) {
					amp_init[peakNumber-1] = atof(s.substr(cr+1, l-cr).c_str());
					continue;
				}
			}
		}

		cr = 8;
		if (l > cr) {
			if (s.substr(1,cr) == "AMP_MAX=") {
				peakNumber = atoi(s.substr(0, 1).c_str());
				if ((peakNumber > 0) && (peakNumber <= numberOfPeaks)) {
					amp_max[peakNumber-1] = atof(s.substr(cr+1, l-cr).c_str());
					continue;
				}
			}
		}


		// read mean data
		cr = 9;
		if (l > cr) {
			if (s.substr(1,cr) == "MEAN_MIN=") {
				peakNumber = atoi(s.substr(0, 1).c_str());
				if ((peakNumber > 0) && (peakNumber <= numberOfPeaks)) {
					mean_min[peakNumber-1] = atof(s.substr(cr+1, l-cr).c_str());
					continue;
				}
			}
		}

		cr = 10;
		if (l > cr) {
			if (s.substr(1,cr) == "MEAN_INIT=") {
				peakNumber = atoi(s.substr(0, 1).c_str());
				if ((peakNumber > 0) && (peakNumber <= numberOfPeaks)) {
					mean_init[peakNumber-1] = atof(s.substr(cr+1, l-cr).c_str());
					continue;
				}
			}
		}

		cr = 9;
		if (l > cr) {
			if (s.substr(1,cr) == "MEAN_MAX=") {
				peakNumber = atoi(s.substr(0, 1).c_str());
				if ((peakNumber > 0) && (peakNumber <= numberOfPeaks)) {
					mean_max[peakNumber-1] = atof(s.substr(cr+1, l-cr).c_str());
					continue;
				}
			}
		}

		// read sigma data
		cr = 10;
		if (l > cr) {
			if (s.substr(1, cr) == "SIGMA_MIN=") {
				peakNumber = atoi(s.substr(0, 1).c_str());
				if ((peakNumber > 0) && (peakNumber <= numberOfPeaks)) {
					sigma_min[peakNumber-1] = atof(s.substr(cr+1, l-cr).c_str());
					continue;
				}
			}
		}

		cr = 11;
		if (l > cr) {
			if (s.substr(1,cr) == "SIGMA_INIT=") {
				peakNumber = atoi(s.substr(0, 1).c_str());
				if ((peakNumber > 0) && (peakNumber <= numberOfPeaks)) {
					sigma_init[peakNumber-1] = atof(s.substr(cr+1, l-cr).c_str());
					continue;
				}
			}
		}

		cr = 10;
		if (l > cr) {
			if (s.substr(1,cr) == "SIGMA_MAX=") {
				peakNumber = atoi(s.substr(0, 1).c_str());
				if ((peakNumber > 0) && (peakNumber <= numberOfPeaks)) {
					sigma_max[peakNumber-1] = atof(s.substr(cr+1, l-cr).c_str());
					continue;
				}
			}
		}
	}

	// Verifying model data
	for (int i = 0; i < numberOfPeaks; ++i) {
		cout <<"Peak "<< i+1 <<":"<< endl;
		cout << "amplitude:" << amp_init[i] <<"   " << amp_min[i] <<"   " << amp_max[i] <<"   "<< endl;
		cout << "mean     :" << mean_init[i] <<"   " << mean_min[i] <<"   " << mean_max[i] <<"   "<< endl;
		cout << "sigma    :" << sigma_init[i] <<"   " << sigma_min[i] <<"   " << sigma_max[i] <<"   "<< endl;
	}

	modelName = "gaus(0)";
	char* temp_str;
	for (int i = 1; i < numberOfPeaks; ++i) {
		sprintf(temp_str, "%d", 3*i);
		modelName += string("+gaus(")  + string(temp_str) + string(")");
	}
//	cout << modelName << endl;

	in.clear();
	in.close();
}

MathModel::~MathModel() {
	delete[] amp_min;
	delete[] amp_init;
	delete[] amp_max;

	delete[] mean_min;
	delete[] mean_init;
	delete[] mean_max;

	delete[] sigma_min;
	delete[] sigma_init;
	delete[] sigma_max;
}

const char* MathModel::GetModel()
{
	return modelName.c_str();
}

int MathModel::GetNumberOfPeaks()
{
	return numberOfPeaks;
}

double MathModel::GetMinAmp(int i)
{
	if ((i>=0) && (i<numberOfPeaks))
		return amp_min[i];
	else
		return -1.;
}

double MathModel::GetMaxAmp(int i)
{
	if ((i>=0) && (i<numberOfPeaks))
		return amp_max[i];
	else
		return -1.;
}

double MathModel::GetMinMean(int i)
{
	if ((i>=0) && (i<numberOfPeaks))
		return mean_min[i];
	else
		return -1.;
}

double MathModel::GetMaxMean(int i)
{
	if ((i>=0) && (i<numberOfPeaks))
		return mean_max[i];
	else
		return -1.;
}

double MathModel::GetMinSigma(int i)
{
	if ((i>=0) && (i<numberOfPeaks))
		return sigma_min[i];
	else
		return -1.;
}

double MathModel::GetMaxSigma(int i)
{
	if ((i>=0) && (i<numberOfPeaks))
		return sigma_max[i];
	else
		return -1.;
}

double* MathModel::GetInitParameters()
{
	double* res = new double[3*numberOfPeaks];
	for (int i = 0; i < numberOfPeaks; ++i) {
		res[3*i] = amp_init[i];
		res[3*i+1] = mean_init[i];
		res[3*i+2] = sigma_init[i];
	}
	return res;
}

void MathModel::SetAmpLimits(int i, double min, double max)
{
	if ((i>0) && (i<numberOfPeaks)) {
		amp_min[i] = min;
		amp_max[i] = max;
		amp_init[i] = (min + max)/2;
	}
}

void MathModel::SetMeanLimits(int i, double min, double max)
{
	if ((i>=0) && (i<numberOfPeaks)) {
		mean_min[i] = min;
		mean_max[i] = max;
		mean_init[i] = (min + max)/2;
	}
}

void MathModel::SetSigmaLimits(int i, double min, double max)
{
	if ((i>0) && (i<numberOfPeaks)) {
		sigma_min[i] = min;
		sigma_max[i] = max;
		sigma_init[i] = (min + max)/2;
	}
}
