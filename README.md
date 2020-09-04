# ImageMoments
Accurate calculation of raw image moments with O(N+M) multiplications for grayscale images. See article [here](https://arxiv.org/abs/2008.11083).

### Raw Image Moments
For a grayscale image or pixel array of size (N, M), the calculation of raw image moments typically requires O(N.M) multiplications, this can be very costly for large images (for binary images there are much faster methods, they won't be discussed here). 
More information can be found [here](https://en.wikipedia.org/wiki/Image_moment).

### The Discrete Radon Transformation
The DRT algorithm reduces this problem from 2D moments of an NxM array, to 1D moments of 4 projection line integrals. The original image can be projected vertically, horizontally, at 45 & 135 degrees, and then summed along those axes. The 2D moments become linear combinations of 1D moments of these line integrals and there is no loss of information. This reduces the number of multiplications from O(N.M) to O(N+M). See the timings on an Intel Core i5 7th Gen below. Note, the Naive algorithm is the baseline O(N.M); the OpenCV algorithm and resultant timings are with and without SSE2/AVX optimisation; the DRT algorithm and times are also shown with and without SSE2/AVX optimisation.

### Results

| Algorithm<br>Image Size |  Naïve<br>uSec |   OCV<br>uSec | OCV-AVX2<br>uSec |  DRT<br>uSec | DRT-AVX2<br>uSec |
|:-----------------------:|-------:|------:|---------:|-----:|---------:|
|        4032x3024        | 472386 | 17373 |     8700 | 5600 |     3330 |
|        3000x3000        | 348870 | 12840 |     6400 | 4000 |     2390 |
|        2000x2000        | 153940 |  5540 |     2800 | 1500 |      856 |
|        1500x1500        |  85810 |  3100 |     1600 |  870 |      485 |
|        1000x1000        |  37320 |  1374 |      710 |  390 |      223 |
|         750x750         |  21123 |   775 |      410 |  220 |      127 |
|         400x400         |   5932 |   222 |      110 |   69 |       38 |
|         200x200         |   1459 |    56 |       29 |   19 |       12 |
<br>

![Timings](https://github.com/wild-ig/drt_moments/raw/master/DRTvsOpenCV.png)