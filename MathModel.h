/*
 * MathModel.h
 *
 *  Created on: Feb 23, 2014
 *      Author: vlad
 */

#ifndef MATHMODEL_H_
#define MATHMODEL_H_

#include "Riostream.h"

class MathModel {
public:
	MathModel(string);
	virtual ~MathModel();

	const char* GetModel();
	int GetNumberOfPeaks();

	double GetMinAmp(int );
	double GetMaxAmp(int );
	double GetMinMean(int );
	double GetMaxMean(int );
	double GetMinSigma(int );
	double GetMaxSigma(int );

	double* GetInitParameters();

private:
	int numberOfPeaks;

	double* amp_min;
	double* amp_init;
	double* amp_max;

	double* mean_min;
	double* mean_init;
	double* mean_max;

	double* sigma_min;
	double* sigma_init;
	double* sigma_max;

	string modelName;
};

#endif /* MATHMODEL_H_ */
