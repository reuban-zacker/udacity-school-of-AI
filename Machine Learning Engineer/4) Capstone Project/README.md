# MLND Capstone
Capstone for Udacity's Machine Learning Nanodegree

## Finding pairs of duplicate questions
This project is taken from the Kaggle platform, and is currently available under the name Quora
Question Pairs in this link: https://www.kaggle.com/c/quora-question-pairs. Quora is a platform where
anyone can make a question, and other users give answers. According to Quora, they receive over 100
million visits every month, so it's very common that the question someone asks has already been
answered by others. In order to make it easier for someone to find an answer, they use a Random Forest
model to identify duplicate questions.
This project is about finding a model that can determine whether a pair of questions has the same
meaning or not. The input data is a data set of about 400,000 pair of questions with a human provided
label stating if they have the same meaning. As for testing, Kaggle provides a set of unlabeled pairs,
which are then compared to their own human labeled results.

## Datasets
The necessary datasets for this project can be found in the webpage of the Kaggle's project, which is
the following: https://www.kaggle.com/c/quora-question-pairs/data under the names _train.csv.zip_ and 
_test.csv.zip_. Both of them should be put in a folder called _data_

## Code
All the necessary Python code used for this project can be found in the file named _MLND-Capstone.ipynb_.

## Software requirements
The following software is required to be installed in order to run the code:
* Python 3.5 or higher
* Scipy
* Numpy + MKL
* Pandas
* Matplotlib
* Tqdm
* Nltk (Natural Language ToolKit)
* Sklearn
* XGBoost (The instructions for installing this library are found here: 
http://xgboost.readthedocs.io/en/latest/build.html. When importing, the
path should be changed. In the iPython Notebook it can be found under the
name _mingw_path_)
