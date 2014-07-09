//============================================================================
// Name        : CSV.cpp
// Author      : Andrey
// Version     :
// Copyright   : Your copyright notice
// Description : Computer Stereo Vision in C++, Ansi-style
//============================================================================

#include <opencv2/opencv.hpp>
#include "SvImage.h"
#include "SvProcessorV1.h"
#include "SvProcessorV2.h"
#include <thread>
//#include <pcl/point_cloud.h>
//#include <pcl/point_types.h>
//#include <pcl/visualization/pcl_visualizer.h>
//#include <vtkRenderWindow.h>
//#include <pcl/visualization/cloud_viewer.h>
//#include <pcl/filters/statistical_outlier_removal.h>

using namespace cv;

void CallBackFunc(int event, int x, int y, int flags, void* userdata)
{
     if (event == EVENT_LBUTTONDOWN ) {

     } else if ( event == EVENT_RBUTTONDOWN ) {

     } else if ( event == EVENT_MBUTTONDOWN ) {

     } else if ( event == EVENT_MOUSEMOVE ) {

     }
}

int main(int argc, char** argv) {
	Mat matLeft = imread("img/left8.png", 1);
	Mat matRight = imread("img/right8.png", 1);
	Mat matStereo(Mat::zeros(matLeft.rows, matLeft.cols, CV_8U));

	SvImage left(matLeft);
	SvImage right(matRight);
	SvImage stereo(matStereo);

	int line = 0;

	SvProcessorV2 proc[4];

	for (int i = 0; i < 4; i++) {
		proc[i].setLeftImage(left);
		proc[i].setRightImage(right);
	}

	while (line < stereo.getHeight()) {
		for (int i = 0; i < 4; i++) {
			if (line < stereo.getHeight() && !proc[i].isActive()) {
				proc[i].run(stereo, line++);
			}
		}
	}

	//pcl::PointXYZRGB point;
	//pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZRGB>);
	//pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud_filtered (new pcl::PointCloud<pcl::PointXYZRGB>);

	/*cloud->resize(stereo.getHeight() * stereo.getWidth());

    for (int y = 0; y < stereo.getHeight(); y++) {
		for (int x = 0; x < stereo.getWidth(); x++) {
			int i = stereo.getWidth() * y + x;
			int value = stereo.getPixel(x, y, 0);
			if (value) {
				cloud->points[i].x = (x - (stereo.getWidth() / 2.0))/100.0;
				cloud->points[i].y = (-y + (stereo.getHeight() / 2.0))/100.0;
				cloud->points[i].z = (-stereo.getPixel(x, y, 0) * 6.0)/100.0;

				cloud->points[i].r = left.getPixel(x, y, 2);
				cloud->points[i].g = left.getPixel(x, y, 1);
				cloud->points[i].b = left.getPixel(x, y, 0);
			}
		}
    }*/
/*
    pcl::StatisticalOutlierRemoval<pcl::PointXYZRGB> sor;
	sor.setInputCloud(cloud);
	sor.setMeanK(50);
	sor.setStddevMulThresh(1.0);
	sor.filter(*cloud_filtered);
*/

    /*pcl::visualization::CloudViewer viewer("Simple Cloud Viewer");
    viewer.showCloud(cloud);
    while (!viewer.wasStopped ())
    {
    }*/

	imshow("Display Image", stereo.getCvMatrix());
	//setMouseCallback("Display Image", CallBackFunc, NULL);
	waitKey();

	return 0;
}
