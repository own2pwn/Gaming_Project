/*
 * featureextraction.h
 *
 *  Created on: 24 Jul 2017
 *      Author: sheun
 */

#ifndef FEATUREEXTRACTION_H_
#define FEATUREEXTRACTION_H_

#include <stdio.h>
#include <iostream>
#include <vector>
#include "opencv2/core.hpp"
#include "opencv2/features2d.hpp"
#include "opencv2/xfeatures2d.hpp"
#include "opencv2/highgui.hpp"

using namespace cv;
using namespace cv::xfeatures2d;
using namespace std;

class feature_extraction {
public:
	feature_extraction();
	virtual ~feature_extraction();
	//get feature points of each objects in the vector
	vector< vector<KeyPoint> > featurePoints (vector<Mat> image,int world_number);


};

#endif /* FEATUREEXTRACTION_H_ */
