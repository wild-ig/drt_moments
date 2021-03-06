/* 
MIT License

Copyright (c) 2020 wild-ig 
*/
#include <vector>
#include <numeric>
#include <opencv2\opencv.hpp>
#include "moments.hpp"

using namespace std;
using namespace cv;

//power arrays
double *d1, *d2, *d3, *d4, *a3;

double product(const vector<long> &mat, double power[], int many)
{
    double sum = 0.0;
    for(int i = 0; i < many; i++)
        sum += static_cast<double>(mat[i]) * power[i];

    return sum;
}

void pre_compute_power_arrays(const Size s) {
    const int width = s.width;
    const int height = s.height;

    //power arrays
    d1 = new double [width + height];
    d2 = new double [width + height];
    d3 = new double [width + height];
    a3 = new double [width + height];

    for (int k=0; k< width + height; ++k)
    {
        d1[k] = k;
        double k2 = static_cast<double>(k) * static_cast<double>(k);
        d2[k] = k2;
        d3[k] = k2 * static_cast<double>(k);
        a3[k] = pow(static_cast<double>(k - height + 1), 3);
    }
}


Moments drt_moments(const Mat& image)
{
    Size s = image.size();
    const int width = s.width;
    const int height = s.height;

    double m00, m01, m10, m11, m20, m02, m30, m12, m21, m03;

    // projection arrays
    vector<long> vert(width, 0);
    vector<long> horz(height, 0);
    vector<long> diag(width+height, 0);
    vector<long> anti(width+height, 0);

    long* hptr = &horz[0];
    long* vptr = &vert[0];
    long* dptr = &diag[0];
    long* aptr = &anti[height - 1];

    for (int i = 0; i < height; i++)
    {
        const uchar* p = image.ptr<uchar>(i);

        for(int j = 0; j < width; j++)
        {
            vptr[j] += p[j];
            hptr[i] += p[j];
            dptr[j] += p[j];
            aptr[j] += p[j];
        }

        dptr++;
        aptr--;
    }

    m00 = accumulate(begin(vert), end(vert), 0.0);
    m10 = product(vert, d1, width);
    m01 = product(horz, d1, height);
    m20 = product(vert, d2, width);
    m02 = product(horz, d2, height);
    m30 = product(vert, d3, width);
    m03 = product(horz, d3, height);
    m11 = (product(diag, d2, width+height) - m02 - m20) / 2.0;
    double temp_1 = product(diag, d3, width+height) / 6.0;
    double temp_2 = product(anti, a3, width+height) / 6.0;
    m12 = temp_1 + temp_2 - m30/3.0;
    m21 = temp_1 - temp_2 - m03/3.0;

    Moments m(m00, m10, m01, m20, m11, m02, m30, m21, m12, m03);

    return m;
}

