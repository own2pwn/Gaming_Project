//============================================================================
// Name        : transistor_vision.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include<iostream>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/opencv.hpp>
#include<iostream>
#include<vector>
#include <algorithm>

#include "yingyang.h"
#include "SeperateObjects.h"
#include "featureextraction.h"

using namespace std;
using namespace cv;


int main()
{

	//get image
	Mat3b img = imread("/home/sheun/Pictures/transistor_images/transistor2.jpg");

	//grayscale, and use imadjust for to get a high constrast version (the base for "lightworld")
	Mat1b gray;
	//convert to grayscale
	cvtColor(img, gray, COLOR_RGB2GRAY);
	//smooth image
	blur(gray, gray, Size(3,3));
	Mat1b Original_image_clone = gray.clone();
    //convert to binary
	ying_yang world_view;
	Mat1b dark_world_view = world_view.binary(gray);
	Mat1b light_world_view = world_view.binary_Inverse(gray);
	//**********************************************************************************
    // Perform the distance transform algorithm
    Mat dist;
    distanceTransform(light_world_view, dist, CV_DIST_L2, 3);
    // Normalize the distance image for range = {0.0, 1.0}
    // so we can visualize and threshold it
    normalize(dist, dist, 0, 1., NORM_MINMAX);
    imshow("Distance Transform Image", dist);
    // Threshold to obtain the peaks
    // This will be the markers for the foreground objects
    threshold(dist, dist, 0.045, 1., CV_THRESH_BINARY);
    // Dilate a bit the dist image
    Mat kernel1 = Mat::ones(3, 3, CV_8UC1);
    dilate(dist, dist, kernel1);
    imshow("Peaks", dist);

    // Create the CV_8U version of the distance image
    // It is needed for findContours()
    Mat dist_8u;
    dist.convertTo(dist_8u, CV_8U);
    // Find total markers
    vector<vector<Point> > contours;
    findContours(dist_8u, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
    // Create the marker image for the watershed algorithm
    Mat markers = Mat::zeros(dist.size(), CV_32SC1);
    // Draw the foreground markers
    for (size_t i = 0; i < contours.size(); i++)
        drawContours(markers, contours, static_cast<int>(i), Scalar::all(static_cast<int>(i)+1), -1);
    // Draw the background marker
    circle(markers, Point(5,5), 3, CV_RGB(255,255,255), -1);
    imshow("Markers", markers*10000);

    // Perform the watershed algorithm
    watershed(img, markers);
    Mat mark = Mat::zeros(markers.size(), CV_8UC1);
    markers.convertTo(mark, CV_8UC1);
    bitwise_not(mark, mark);
//    imshow("Markers_v2", mark); // uncomment this if you want to see how the mark
                                  // image looks like at that point
    // Generate random colors
    vector<Vec3b> colors;
    for (size_t i = 0; i < contours.size(); i++)
    {
        int b = theRNG().uniform(0, 255);
        int g = theRNG().uniform(0, 255);
        int r = theRNG().uniform(0, 255);
        colors.push_back(Vec3b((uchar)b, (uchar)g, (uchar)r));
    }
    // Create the result image
    Mat dst = Mat::zeros(markers.size(), CV_8UC3);
    // Fill labeled objects with random colors
    for (int i = 0; i < markers.rows; i++)
    {
        for (int j = 0; j < markers.cols; j++)
        {
            int index = markers.at<int>(i,j);
            if (index > 0 && index <= static_cast<int>(contours.size()))
                dst.at<Vec3b>(i,j) = colors[index-1];
            else
                dst.at<Vec3b>(i,j) = Vec3b(0,0,0);
        }
    }
    // Visualize the final image
    imshow("Final Result", dst);
    cout<<contours.size()<<endl;
	//***********************************************************************************
	imshow("dark world view", dark_world_view);
	imshow("light world view", light_world_view);

	//get objects in each world view
	SeperateObjects worldObjects;
	vector <Mat1b> dark_world_objects  = worldObjects.BoundBox(dark_world_view, gray,Original_image_clone, 0); // the 2nd parameter is because we want the boxes to be on the original image
	vector <Mat1b> light_world_objects = worldObjects.BoundBox(light_world_view, gray,Original_image_clone, 1);

	feature_extraction features_of_objects;
	vector< vector<KeyPoint> > features_of_dark_world_objects = features_of_objects.featurePoints(dark_world_objects,0);
	vector< vector<KeyPoint> > features_of_light_world_objects = features_of_objects.featurePoints(light_world_objects,1);


	cout<<features_of_light_world_objects.size()<<endl;
	cout<<features_of_dark_world_objects.size()<<endl;
	//namedWindow( "Objects in both worlds", CV_WINDOW_NORMAL );
	//imshow ("Objects in both worlds",Original_image_clone);

	cvWaitKey();
	return 0;

}
