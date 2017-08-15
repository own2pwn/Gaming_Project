/*
 * SendDataToPython.cpp
 *
 *  Created on: 14 Aug 2017
 *      Author: sheun
 */

#include "SendDataToPython.h"

SendDataToPython::SendDataToPython() {
	cout<<"sending image data to python"<<endl;

}

SendDataToPython::~SendDataToPython() {

}


boost::python::dict SendDataToPython::objectInformationToDict(vector< vector<KeyPoint> > vectorToSend, vector<int>x_coordinate,vector<int>y_coordinate)
{
	//iterator for each objects
	typename vector< vector<KeyPoint> >::iterator iterEachObject;
	//iterator for each keypoint for each object
	typename vector<KeyPoint>::iterator iterKeyPoints;

	//map/dictionary will hold the keypoints acciociated with each object
	boost::python::dict keypointMap;
	int i = 0;

	for (iterEachObject = vectorToSend.begin(); iterEachObject != vectorToSend.end(); ++iterEachObject)
	{
		//feature arrays

		boost::python::list objectInformation;// overall list that will hold objects coordinate position in the image and its feature point
		boost::python::list keyPointList; // list holding objects keypoint
		boost::python::list coorPointList; // list holding objects x and y coordinates in the image.

		coorPointList.append(x_coordinate[i]);
		coorPointList.append(y_coordinate[i]);


		objectInformation.append(coorPointList);

		//get information of every identified keypoint of the objects and put that into a list
		for(iterKeyPoints = iterEachObject->begin(); iterKeyPoints != iterEachObject->end(); ++iterKeyPoints)
		{
			boost::python::list individualKeypointArray;

			individualKeypointArray.append(iterKeyPoints->pt.x);
			individualKeypointArray.append(iterKeyPoints->pt.y);
			individualKeypointArray.append(iterKeyPoints->size);
			individualKeypointArray.append(iterKeyPoints->angle);
			individualKeypointArray.append(iterKeyPoints->response);
			individualKeypointArray.append(iterKeyPoints->octave);
			keyPointList.append(individualKeypointArray);
		}

		objectInformation.append(keyPointList);
		keypointMap[i] = objectInformation;
		++i;

	}

	return keypointMap;
}
