## Writeup Template

### You can use this file as a template for your writeup if you want to submit it as a markdown file, but feel free to use some other method and submit a pdf if you prefer.

---

**Advanced Lane Finding Project**

The goals / steps of this project are the following:

* Compute the camera calibration matrix and distortion coefficients given a set of chessboard images.
* Apply a distortion correction to raw images.
* Use color transforms, gradients, etc., to create a thresholded binary image.
* Apply a perspective transform to rectify binary image ("birds-eye view").
* Detect lane pixels and fit to find the lane boundary.
* Determine the curvature of the lane and vehicle position with respect to center.
* Warp the detected lane boundaries back onto the original image.
* Output visual display of the lane boundaries and numerical estimation of lane curvature and vehicle position.

[//]: # (Image References)

[image1]: ./examples/undistort_output.png "Undistorted"
[image2]: ./test_images/test1.jpg "Road Transformed"
[image3]: ./examples/binary_combo_example.jpg "Binary Example"
[image4]: ./examples/warped_straight_lines.jpg "Warp Example"
[image5]: ./examples/color_fit_lines.jpg "Fit Visual"
[image6]: ./examples/example_output.jpg "Output"
[video1]: ./project_video.mp4 "Video"

## [Rubric](https://review.udacity.com/#!/rubrics/571/view) Points

### Here I will consider the rubric points individually and describe how I addressed each point in my implementation.  

---

### Writeup / README

#### 1. Provide a Writeup / README that includes all the rubric points and how you addressed each one.  You can submit your writeup as markdown or pdf.  [Here](https://github.com/udacity/CarND-Advanced-Lane-Lines/blob/master/writeup_template.md) is a template writeup for this project you can use as a guide and a starting point.  

You're reading it!

### Camera Calibration

#### 1. Briefly state how you computed the camera matrix and distortion coefficients. Provide an example of a distortion corrected calibration image.

The code for this step is contained in the first code **cell 1** of the IPython notebook located in "./project2.ipynb".

I start by preparing "object points", which will be the (x, y, z) coordinates of the chessboard corners in the world. Here I am assuming the chessboard is fixed on the (x, y) plane at z=0, such that the object points are the same for each calibration image.  Thus, `objp` is just a replicated array of coordinates, and `objpoints` will be appended with a copy of it every time I successfully detect all chessboard corners in a test image.  `imgpoints` will be appended with the (x, y) pixel position of each of the corners in the image plane with each successful chessboard detection.  

I then used the output `objpoints` and `imgpoints` to compute the camera calibration and distortion coefficients using the `cv2.calibrateCamera()` function.  I applied this distortion correction to the test image using the `cv2.undistort()` function and obtained this result: 

![alt text][image1](./output_images/undist_calibration1.jpg)

### Pipeline (single images)

#### 1. Provide an example of a distortion-corrected image.
In **cell 2** of `project2.ipynb`
To demonstrate this step, I will describe how I apply the distortion correction to one of the test images like this one:
![alt text][image2](./output_images/undist_calibration1.jpg)

#### 2. Describe how (and identify where in your code) you used color transforms, gradients or other methods to create a thresholded binary image.  Provide an example of a binary image result.

I used a combination of color and gradient thresholds to generate a binary image (thresholding steps at ** cell 3 ** in `project2.ipynb` ).  Here's an example of my output for this step.  (note: this is not actually from one of the test images)

![alt text][image3](./output_images/binary_test1.jpg)

#### 3. Describe how (and identify where in your code) you performed a perspective transform and provide an example of a transformed image.
In **cell 4** of `project2.ipynb`
The code for my perspective transform includes a function called `warp()`, which appears in **cell 4** in the file `project2.ipynb` (./project2.ipynb).  The `warp()` function takes as inputs an image (`img`), as well as source (`src`) and destination (`dst`) points.  I chose the hardcode the source and destination points in the following manner:

```python
src = np.float32([
    [165, 720],
    [570, 470],
    [740, 470],
    [1135, 720]])
    
dst = np.float32([
    [150, 720], 
    [150, 0],                         
    [1130, 0],            
    [1130, 720]])
```

This resulted in the following source and destination points:

| Source        | Destination   | 
|:-------------:|:-------------:| 
| 165, 720      | 150, 720      | 
| 570, 470      | 150, 0          |
| 740, 470      | 1130, 0        |
| 1135, 720    | 1130, 720    |

I verified that my perspective transform was working as expected by drawing the `src` and `dst` points onto a test image and its warped counterpart to verify that the lines appear parallel in the warped image.

![alt text][image4](./output_images/warped_binary_test5.jpg)

#### 4. Describe how (and identify where in your code) you identified lane-line pixels and fit their positions with a polynomial?

Then I did some other stuff and fit my lane lines with a 2nd order polynomial kinda like this:
In **cell 5** of `project2.ipynb`
I used `find_lane_pixels()`  to get `leftx, lefty, rightx, righty, out_img` as input for `fit_polynomial()`  to get `left_fit, right_fit`  which are polynomial coefficients and `out_img` with sliding windos drew on it.

![alt text][image5](./output_images/fit_polynomial_test5.jpg)

#### 5. Describe how (and identify where in your code) you calculated the radius of curvature of the lane and the position of the vehicle with respect to center.

I did this in **cell 6** in my code in `project2.ipynb`
I passed polynomial coefficients `left_fit, right_fit`  obtained from last step into function `curvature()`  to get `left_curvature, right_curvature and center` of binary warped image.


#### 6. Provide an example image of your result plotted back down onto the road such that the lane area is identified clearly.

I implemented this step in **cell 7** in my code in `project2.ipynb` in the function `draw_lane_area()`  and `add_info()`.  Here is an example of my result on a test image:

![alt text][image6](./output_images/line_detected_test5.jpg)

---

### Pipeline (video)

#### 1. Provide a link to your final video output.  Your pipeline should perform reasonably well on the entire project video (wobbly lines are ok but no catastrophic failures that would cause the car to drive off the road!).

Here's a [link to my video result](./project_video_output.mp4)

---

### Discussion

#### 1. Briefly discuss any problems / issues you faced in your implementation of this project.  Where will your pipeline likely fail?  What could you do to make it more robust?

Here I'll talk about the approach I took, what techniques I used, what worked and why, where the pipeline might fail and how I might improve it if I were going to pursue this project further. 
* 1. Parameter tuning really took me a lot of time. Sometimes when they worked well for straight lane lines, they didn't work well for curved lane lines, and vice versa. I finally tried to make them look good on both curved and straightforward lane lines, but far from perfect.
* 2. Calcualted curvature of both lane lines is another challenge. At first I got some ridiculous results like over 50,000 meters, then I looked back to my calculation function, parameters and even units. The final number of curverture looks OK, though I occasionally obtain some number that is very inaccurate.
* 3. I also implement my pipeline on [challenge video](./challenge_video_output.mp4). As you can see in the video, the colored lane area wobbles frequently, sometimes even went out of lane lines or just colored half of them. Reasons may be high curverture of lane lines or heavy shadows on the road.
* 4. Addition of some other color channels and/or sobel thresholds may help improve the lane lind finding under various shadow or lightness condition. But when it comes to some severe environments like lightless night or crowded local drive way, the algorithm may fail again. We need some additional sensors besides camera.
