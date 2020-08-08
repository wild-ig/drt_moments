/* 
MIT License

Copyright (c) 2020 wild-ig 
*/
#include <iostream>
#include <vector>
#include <numeric>
#include <Windows.h>
#include <opencv2\opencv.hpp>
#include "moments.hpp"

using namespace std;
using namespace cv;


int main(int argc, char *argv[]) {

    Mat image;
    Moments m_drt, m_ocv;
    double t_drt = 10.0, t_ocv = 10.0, t0, t1;

    if(argc == 1)
	    image = imread("images\\brain.jpg", IMREAD_GRAYSCALE);
    else
        image = imread(argv[1], IMREAD_GRAYSCALE);

	if (!image.data)
    {
        cout << "Could not find image" << endl;
        return -1;
    }
    
    if(!SetPriorityClass(GetCurrentProcess(), REALTIME_PRIORITY_CLASS))
        cout << "Could not set process priority";

    if(!SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_TIME_CRITICAL))
        cout << "Could not set thread priority";

    pre_compute_power_arrays(image.size());

    // Large test sample size to get the lowest time for each
    int iterations = 1000;
    while(iterations--) {
        t0 = (double)getTickCount();
        m_drt = drt_moments(image);
        t0 = ((double)getTickCount()-t0)/getTickFrequency();

        t1 = (double)getTickCount();
        m_ocv = cv::moments(image);
        t1 = ((double)getTickCount()-t1)/getTickFrequency();

        t_drt = (t0 < t_drt) ? t0 : t_drt;
        t_ocv = (t1 < t_ocv) ? t1 : t_ocv;
    }

    cout << "DRT: " << t_drt << endl;
    cout << "OCV: " << t_ocv << endl;

    cout << "[" << log10(m_drt.m00) << "] m00 [" << log10(m_ocv.m00) << "]" << endl;
    cout << "[" << log10(m_drt.m10) << "] m10 [" << log10(m_ocv.m10) << "]" << endl;
    cout << "[" << log10(m_drt.m01) << "] m01 [" << log10(m_ocv.m01) << "]" << endl;
    cout << "[" << log10(m_drt.m20) << "] m20 [" << log10(m_ocv.m20) << "]" << endl;
    cout << "[" << log10(m_drt.m02) << "] m02 [" << log10(m_ocv.m02) << "]" << endl;
    cout << "[" << log10(m_drt.m11) << "] m11 [" << log10(m_ocv.m11) << "]" << endl;
    cout << "[" << log10(m_drt.m30) << "] m30 [" << log10(m_ocv.m30) << "]" << endl;
    cout << "[" << log10(m_drt.m03) << "] m03 [" << log10(m_ocv.m03) << "]" << endl;
    cout << "[" << log10(m_drt.m21) << "] m21 [" << log10(m_ocv.m21) << "]" << endl;
    cout << "[" << log10(m_drt.m12) << "] m12 [" << log10(m_ocv.m12) << "]" << endl;

	return 0;
}
