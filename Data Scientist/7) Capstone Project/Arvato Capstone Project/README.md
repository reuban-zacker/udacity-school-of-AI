# DSND_Term2_Capstone_Arvato

1. [Project Introduction](#intro)
2. [File Descriptions](#files)
3. [Results](#results)
4. [Licensing, Authors, and Acknowledgements](#licensing)
5. [Feedback](#fb)

## Project Introduction<a name="intro"></a>

By creating customer segmentation and comparing to general population, one can know which part of the general population are more likely to be customer and which part are not. I analyzed demographics data for customers of a mail-order sales company in Germany, comparing it to demographics information for the general population.    
Firstly, I used different approaches to pre-process the data, and then I used unsupervised learning techniques, PCA (Principle Componets Analysis) and k-NN (k-nearest neighbor algorithm), to perform customer segmentation and to identify the core customer traits of the company.    
Secondly, with demographics information for targets of a marketing campaign for the company, I used different models to predict which individuals are most likely to convert into customers.    



## File Descriptions <a name="files"></a>

Since the dataset offered by **AZ Direct GmbH** is private and cannot be published, only the meta-data is uploaded here.

- Arvato_Project_Workbook.ipynb: The main analysis file
- DIAS_Attributes_Values_2017.xlsx: the meta-data (a detailed mapping of data values for each feature in alphabetical order)
- DIAS_Information_Levels_Attributes_2017.xlsx: the meta-data (a top-level list of attributes and descriptions, organized by informational category)
- predic_result_lr.csv - the rediction results (used logistic regression)
- predic_result_lr_PCA20.csv - the rediction results (used logistic regression and 20 PCA componets only)
- predic_result_rf.csv - the rediction results (used random forest)



## Results<a name="results"></a>

- Segementation part:    
Using PCA and KMeans, I got the results as follows.
    - The population who tend to be customer: The people who may be adults and usually shop online.
    - The population who might not be customer: The people who are not rich, nor focusing on the brand of cars. However, they tend to use cars often. Some of them might have some anti-society characteristics.    

- Supervised Learning Prediction part:    
The results were not good. For the three models (logistic regression, random forest and k-NN), none of them has good precision even used GridSearch.


## Licensing, Authors, Acknowledgements<a name="licensing"></a>

Everything need to follow Udacity's Terms of Use and other policies. The use of the **AZ Direct GmbH** data is solely to
complete the data mining task which is part of the **Unsupervised
Learning** and **Capstone** projects for the Udacity Data
Science Nanodegree program. Using the **AZDirect GmbH** data in any other context is prohibited.

## Feedback<a name="fb"></a>

If you have any comments, ideas or feedback, feel free to leave your message either here or the post at [medium](https://medium.com/@rubszion/handling-and-investing-customer-segmentation-for-arvato-financial-services-6094c8361e34?). And thank your in advance !
