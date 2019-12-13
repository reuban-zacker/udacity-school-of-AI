# **Traffic Sign Recognition** 

## Writeup

---

**Build a Traffic Sign Recognition Project**

The goals / steps of this project are the following:
* Load the data set (see below for links to the project data set)
* Explore, summarize and visualize the data set
* Design, train and test a model architecture
* Use the model to make predictions on new images
* Analyze the softmax probabilities of the new images
* Summarize the results with a written report


[//]: # (Image References)

[image1]: ./WriteUp_images/original_calsses_distribution.jpg "Visualization"
[image2]: ./WriteUp_images/comparison_limit_30.jpeg "Grayscale and Normalization"
[image3]: ./WriteUp_images/Comparison_animal.jpeg "Grayscale and Normalization"
[image4]: ./WriteUp_images/augmented_examples.jpeg "Disformation examples"
[image5]: ./WriteUp_images/augmented_classes_distribution.jpeg "augmented classes distribution"
[image6]: ./WriteUp_images/2-stage%20ConvNet%20Architecture.png "ConvNet architecture"
[image7]: ./WriteUp_images/accuracy_result.jpeg "accuracy result"
[image8]: ./more_test_images/test0.jpg "Traffic Sign 1"
[image9]: ./more_test_images/test1.jpg "Traffic Sign 2"
[image10]: ./more_test_images/test2.jpg "Traffic Sign 3"
[image11]: ./more_test_images/test3.jpg "Traffic Sign 4"
[image12]: ./more_test_images/test4.jpg "Traffic Sign 5"
[image13]: ./WriteUp_images/possibility_distribution.jpeg "Classification Softmax Possibility"
[image14]: ./WriteUp_images/possiblity_distribution_wrong.jpeg "Wrong Classification Softmax Possibility"
[image15]: ./WriteUp_images/Possibility_distribution_right.jpeg "Classification Softmax Possibility"
[image16]: ./WriteUp_images/limit_30_distribution.jpeg "Visualization of possible result"
[image17]: ./WriteUp_images/traffic_light_distribution.jpeg "Visualization of possible result"

## Rubric Points
### Here I will consider the [rubric points](https://review.udacity.com/#!/rubrics/481/view) individually and describe how I addressed each point in my implementation.  

---
### Writeup / README

#### 1. Provide a Writeup / README that includes all the rubric points and how you addressed each one. 
You're reading it! and here is a link to my [project code](https://github.com/udacity/CarND-Traffic-Sign-Classifier-Project/blob/master/Traffic_Sign_Classifier.ipynb)

### Data Set Summary & Exploration

#### 1. Provide a basic summary of the data set. 
I used the pandas library to calculate summary statistics of the traffic
signs data set:

* The size of training set is 34799.
* The size of the validation set is 4410.
* The size of test set is 12630.
* The shape of a traffic sign image is (32, 32, 3).
* The number of unique classes/labels in the data set is 43.

#### 2. Include an exploratory visualization of the dataset.

Here is an exploratory visualization of the data set. It is a bar chart 
showing how the training data are distributed for 43 classes. From the image,
 we can notice that the images number for each class varies a lot. This issue
  will result in the bias of the training classifier result, which will tend 
  to rely more on the classes with more data. Therefore, the augmentation 
  step should be used to give a uniform distribution. 

![alt text][image1]

### Design and Test a Model Architecture

#### 1. Describe how you preprocessed the image data. 
As a first step, I decided to convert the RGB images to only Y channel 
because it will give a reliable image description, and also reduce the 
processed data volume so as to improve the computation time. In the 
paper of Sermanet and LeCun(2011), it was approved that the image without color 
outperformed than with color.
  
As a last step, I modify the images contrast value by *cv2.equalizeHist()*, and 
then normalized the image data with *np.mean()* and *np.std()*, which is 
called the global normalization. With the the local and global normalization,
 the images are easier to compare and the features are easier to be detected. 

Here are examples of a traffic sign image with versions of original, after 
converting Y, and after normalization,

![alt text][image2]![alt text][image3]




To add more data to the the data set, I used the *ImageDataGenerator()* from 
the keras library. It can generate different images with various position shift 
values, zoom factor, rotation ranges, etc. 

Here is an example of an original image and augmented images:

![alt text][image4]

After the data augmentation, the distribution of the data set is uniform, 
which is shown as below:

![alt text][image5]



#### 2. Describe what your final model architecture looks like including model type, layers, layer sizes, connectivity, etc.
Mt model architecture is built according to the model architecture of LeNet-5 
and a 2-stage ConvNet architecture described by Sermanet and Lecun(2011) in 'Traffic Sign 
Recognition with Multi-Scale Convolutional Network'. The concept is shown as:

![alt text][image6]

The special part of this architecture is that the first stage and the second 
stage Convotional output features are fit into the classifier, which will 
provide both general and detailed features. 

My final model consisted of the following layers:

| Layer         		|     Description	        					| 
|:---------------------:|:---------------------------------------------:| 
| Input         		| 32x32x1 image   							    | 
| Convolution 5x5     	| 1x1 stride, valid padding, outputs 28x28x64 	|
| RELU					|												|
| Max pooling	      	| 2x2 stride,  outputs 14x14x64 				|
| Dropout				|   											|
| Convolution 5x5	    | 1x1 stride, valid padding, outputs 10x10x128	|
| RELU					|												|
| Max pooling	      	| 2x2 stride,  outputs 5x5x128 				    |
| Dropout				|   											|
| Flatten				| 5x5x128 + 14x14x64 = 15744  			        |
| Fully connected		| outputs = 100   				                |
| Dropout				|                                        	    |
| Fully connected		| outputs = 50   				                |
| Dropout				|                                    		    |
| Logits		        | outputs = 43   				                |	
|						|												|
|						|												|
 


#### 3. Describe how you trained your model. 
To train the model, I used an Adam Optimizer to minimise the loss function. 
The batch size here is 50, which means I choose 50 samples each time to 
train. Within each training epoch, I repeat the training process 1000 times 
(batches per epoch); therefore, 50,000 samples are trained in each epoch. 
There are 60 epochs in the whole training process. The learning rate for the 
model is 0.0005, and the dropout factor is 0.5, so that half of the output 
will be set to 0, and the others are amplified to 2 times. 

#### 4. Describe the approach taken for finding a solution and getting the validation set accuracy to be at least 0.93. 
My final model results were:
* training set accuracy of 0.995.
* validation set accuracy of 0.957. 
* test set accuracy of 0.935.

This is a result for the training accuracy and validation accuracy 
during training epochs:

![alt text][image7]



* LeNet-5 and 2LConvNet are approved suitable for 
 classifying the traffic signs, and I utilized them as references and tuned 
 the parameters in this case. The first architecture is 6-16 features for the 
 1st and 2nd stage respectively, with 400-120 hidden units for fully connected layers. The other
 parameters are the same as the final architecture. The convolution layers 
 are used to detect the features and the fully connected layers aim to 
 classify the images. 
 
* However, this architecture faces a underfitting, and should be tuned to get 
 a better accuracy. The features number in 1st and 2nd stages 
 should be larger in order to get more information of the images. The 400-120
  hidden units can be adjusted, too.
 
* Too large convolution layers number and too many features will result in 
overfitting, while too few and small will cause underfitting. I used 6-16, 16-32, 32-64, 64-128, and 108-108 for the 1st and 2nd stage in 
convolution layers. The first three combinations did not provide a good 
validation accuracy. The 64-128 and 108-108 both show a acceptable result, but
 I chose 64-128, because it can save more time and storage.The same result 
will appear in the fully connection classification process. The hidden units in 
classifiers are 400-120, 120-60, and 100-50. In Sermanet's paper, 100-50 is 
used so that I also used them, which demonstrate a good result.  

* Increase the batch size will provide a better accuracy because in each 
training batch, the information 
is more general, rather than only including several kinds of traffic signs. 
However, larger batch size (eg. 128) will cause a "OOM" problem in my computer, 
and I can only choose a value under 100. The values 30, 50, 64, 86, 128 were tried,
 and 64 were chosen by the trade-off between accuracy and computation time as
  well as the storage space. 
  
* The larger learning rate will cause wiggle at large epochs, and also make it hard to converge; while too little 
learning rate will result in a very slow accuracy increase. In addition, as 
the epoch value is larger, the training and validation accuracy should be 
larger, but faces an underfitting if the both accuracy keeps small, and an 
overfitting with higher training accuracy and smaller validation accuracy at 
the end. Here, I choose 60, and the model is converged at epoch 60. 
   

* The important design is this model is that the MS architecture in flatten 
step, which include both 1st and 2nd stage output in convolution layers. It 
can include both the general and detailed features in the images so as to 
give a better classification. Additionally, in the training porcess, the 
dropout layers drop out the outputs with certain possibility(keep_prob) by 
changing them to 0, and times 1/keep_prob to the kept output. This method can
 prevent the overfitting. While in the validation and testing process, they 
 are not used. 
 

### Test a Model on New Images

#### 1. Choose five German traffic signs found on the web and provide them in the report. For each image, discuss what quality or qualities might be difficult to classify.

Here are five German traffic signs that I found on the web:

![alt text][image8] ![alt text][image9] 
![alt text][image10] ![alt text][image11] ![alt text][image12]

They have different dimensions, therefore I resize them and run preprocessed 
step to apply a normalization. The third and forth image might be difficult to 
classify because the pixels in the triangle are few, and the shape of them 
can be confused with others. The traffic signal sign's color are not used in 
classification, which makes it even more difficult to be distinguished. 


#### 2. Discuss the model's predictions on these new traffic signs and compare the results to predicting on the test set. 
Here are the results of the prediction:

| Image			               |     Prediction	        			    | 
|:----------------------------:|:--------------------------------------:| 
| Keep right      		       | Keep Right  							| 
| Stop    			           | Stop	  	                            |
| Dangerous curve to the right | Children crossing					    |
| Traffic signals      		   | Pedestrians				 		    |
| Speed limit (30km/h)		   | Speed limit (30km/h)				    |

The visualization of the test image and prediction possiblity is shown as:
![alt text][image13] ![alt text][image14] ![alt text][image15] 
The model was able to correctly guess 3 of the 5 traffic signs, which gives 
an accuracy of 60%. Comparing to the accuracy on the test set 
of 93.5%, it is slightly lower. This maybe due to the random selection of the 
new test images, as well as the classification disability to the low pixels
(blur) original images, and small signs in the triangles shape. 

#### 3. Describe how certain the model is when predicting on each of the five new images by looking at the softmax probabilities for each prediction. 
The distribution of the softmax possibilities for the two selected new test 
figures are shown as below:
![alt text][image16] ![alt text][image17] 

The prediction with the largest possibility for each test image is shown as 
below:

| Probability         	|     Prediction	        					| 
|:---------------------:|:---------------------------------------------:| 
| 1.         			| Keep Right   									| 
| 1.    				| Stop									     	|
| 0.56					| Children crossing								|
| 0.33	      			| Pedestrians					 				|
| 0.98				    | Speed limit (30km/h)      					|


For the first image, the model is very sure that this is a keep right
(probability of 1.0), and the image does contain a keep right sign. For the 
second image, it is also very sure that the image is a stop sign with 
possibility of 1.0. The third image's top three soft max probabilities were 
label 28(Children crossing), 20(Dangerous curve to the right), 26(Traffic 
signals), while the label should be 20 (Dangerous curve to the right). The 
forth image's prediction is pedestrian with possibility of 33%, and the 
second guess is label 30 (Children crossing) with 27% possibility, and the 
third guess is Traffic signals with 15% possibility. The fifth image is very 
sure the sign is Speed limit(30km/h) with 98% possibility. 


### (Optional) Visualizing the Neural Network (See Step 4 of the Ipython notebook for more details)
#### 1. Discuss the visual output of your trained network's feature maps. What characteristics did the neural network use to make classifications?


