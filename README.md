# ImageMoments
Accurate calculation of raw image moments with O(N+M) multiplications for grayscale images. 

### Raw Image Moments
For a grayscale image or pixel array of size (N, M), the calculation of raw image moments typically requires O(NM) multiplications, this can be very costly for large images (for binary images there are much faster methods, they won't be discussed here). 
More information can be found [here](https://en.wikipedia.org/wiki/Image_moment)

### The Discrete Radon Transformation
The DRT reduces this problem from 2D moments of an NxM array, to 1D moments of 4 projection arrays. The original image can be projected vertically, horizontally and at 45, 135 degrees, and summed along those axes. The raw moments then become linear combinations of 1D moments of these arrays and there is no loss of information. This reduces the number of multiplications from O(NM) to O(N+M)