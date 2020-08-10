# ImageMoments
Accurate calculation of raw image moments with O(N+M) multiplications for grayscale images. 

### Raw Image Moments
For a grayscale image or pixel array of size (N, M), the calculation of raw image moments typically requires O(N.M) multiplications, this can be very costly for large images (for binary images there are much faster methods, they won't be discussed here). 
More information can be found [here](https://en.wikipedia.org/wiki/Image_moment)

### The Discrete Radon Transformation
The DRT algorithm reduces this problem from 2D moments of an NxM array, to 1D moments of 4 projection arrays. The original image can be projected vertically, horizontally, at 45 & 135 degrees, and hen summed along those axes. The raw moments then become linear combinations of 1D moments of these arrays and there is no loss of information. This reduces the number of multiplications from O(N.M) to O(N+M). See the timings on an Intel Core i5 7th Gen (Note, the Naive algorithm is the baseline O(N.M); the OpenCV algorithm and resultant timings are with and without SSE2/AVX optimisation, the DRT algorithm and times are also shown with and without SSE2/AVX optimisation: 
![Timings](https://github.com/wild-ig/drt_moments/raw/master/DRTvsOpenCV.png)