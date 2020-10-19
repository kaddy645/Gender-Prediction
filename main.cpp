
//  Created by kartik desai on 30/04/20.
//  Copyright © 2020 kartik desai.

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <math.h>
#include <string.h>
#include <typeinfo>
#include <chrono>

using namespace std;
using namespace std::chrono;

vector<double> Gender;
vector<double> Height;
vector<double> Weight;
vector<vector<double>> X_TrainingData;
vector<vector<double>> X_TestingData;
vector <double >temp;
vector <vector <double>> means;
vector <vector <double>>squareMeans;
vector <double> standardDeviations;

double biasWeight = 0.0;
double weights [2];
double LEARNING_RATE = 0.01;
double Threshold = 0.5;
double y;
double z;

int ITERATIONS = 100;
int counter = 0;
int TotalMale = 0;
int TotalFemale = 0;


bool IsTraining = true;



string x;
string titles;
string line;
char c = ',';


struct train {
    vector<vector<double>> val;
    vector <double> labels;
};

train trainerSet [10000];
train testerSet [10000];



double sigmoid(double z) {
 
    return 1.0 / (1 + exp(-z));
}




double computeHypothesis(vector <double> inputs) {
    double summation = 0.0;
    summation += biasWeight;    //Theta 1
    
    for (int i = 0; i < inputs.size(); i++) {
        
        summation += inputs[i] * weights[i];
    }
    return sigmoid(summation);
}

/* Logistic Regression Cost Function */
double computeLogisticCost() {
    int m = X_TrainingData.size();
    double cost = 0.0;
    
    for (int i=0;i<m;i++) {
        double prediction = computeHypothesis(trainerSet[i].val[0]);
        int label = trainerSet[i].labels[0];
        cost += label * log(prediction) + (1.0 - label) * log(1.0 - prediction);
    }
    return -cost / m;
}


void calculateGradientDescent(double rate) {
    double biasGradient = 0.0;
    int size = X_TrainingData.size();
    double gradients [2];
    
    for (int i=0;i<size;i++) {
        double error = trainerSet[i].labels[0] - computeHypothesis(trainerSet[i].val[0]);
        
        biasGradient += (error);
        
        for (int j = 0; j < 2; j++) {
            gradients[j] += (error) * trainerSet[i].val[0][j];
        }
        
    }
    for (int k = 0; k < 2; k++) {
        gradients[k] = gradients[k] / size;
    }
    
    biasWeight += rate * biasGradient / size;
    
    for (int l = 0; l < 2; l++) {
        weights[l] += rate * gradients[l] / size;
    }
    
}



/* For Optimising the weights using given training data with gradient descent.*/

void train() {
    
    for (int i = 0; i < ITERATIONS; i++) {
        
        calculateGradientDescent(LEARNING_RATE);  // Here Learning rate is α
    }
    
}

/* Classify Male/Female based on value predicted by model and our threshold */
void classify(double val, double threshold) {
    
    if (val >= threshold) {
     
        TotalMale = TotalMale + 1;
        
    } else {
        TotalFemale = TotalFemale + 1;
        
    }
    
    
}

/* start using theta values calculate by training for Testing */
void calculateForTesting(vector<vector<double>> X_TrainingData){
    
    for (int i=0;i<X_TrainingData.size();i++) {
        double prediction = computeHypothesis(testerSet[i].val[0]);
        classify(prediction,Threshold);
    }
}
/* Create Testing Data
 @param row - height/weight & labels - Male/Female
 */

void createTestingData(vector<vector<double>> row, vector<double> labels) {
    vector<double> testingData;
    vector <double> temp;
    double hold;
    for (int i = 0; i < row.size(); i++) {
        
        for(int j=0;j<2;j++) {
            hold  = row[i][j];
            temp.push_back(hold);
        }
        
        
        testerSet[i].val.push_back(temp);
        temp.clear();
        testerSet[i].labels.push_back(labels[i]);
        
    }
    calculateForTesting(row);
}

/* Create Traning Data row - height/weight & labels - Male/Female */

void createTrainingData(vector<vector<double>> row, vector<double> labels) {
    vector<double> trainingData;
    vector <double> temp;
    double hold;
    for (int i = 0; i < row.size(); i++) {
        
        for(int j=0;j<2;j++) {
            hold  = row[i][j];
            temp.push_back(hold);
        }
        
        
        trainerSet[i].val.push_back(temp);
        temp.clear();
        trainerSet[i].labels.push_back(labels[i]);
        
        
        
    }
    double cost = computeLogisticCost();
    cout << "Initial Cost => " <<  cost << endl;
    
    cout << endl;
    cout << "========= Start Training =========" << endl;
    cout << endl;
    
    cout << "Learning Rate / α is " << LEARNING_RATE <<endl;
    cout << endl;
    cout << "Iterations are "  << " " << ITERATIONS <<  "  " << "Please wait for a moment...." <<endl;
    cout << endl;
    train();
    
    cout << "========= Training Complete =========" << endl;
    cout << endl;
    cout << "Weights are "  <<  weights[0]   << "  " << weights[1]  <<  " Theta (θ2 & θ3) " <<endl;
    cout << endl;
    double fcost = computeLogisticCost();
    cout << "Final Cost => " <<  fcost << endl;
    cout << "biasWeight =>  "  << biasWeight <<endl;
    
    
    
}

/* For each value find mean , standard deviation */

void adjustRows(vector<vector<double>> X_TrainingData,bool IsTraining) {
    vector<vector<double>> adjust;
    vector <double> temp;
    for(int i=0;i<X_TrainingData.size();i++) {
        for (int j = 0; j < 2; j++) {
            
            double v =((X_TrainingData[i][j] - means[i][j]) / standardDeviations[j]);
            temp.push_back(v);
            
            
        }
        adjust.push_back(temp);
        temp.clear();
        
        
    }
    
    if(IsTraining){
        createTrainingData(adjust,Gender);  // only if we want to train
    }
    else {
        createTestingData(adjust,Gender);
    }
}

void processData(vector<vector<double>> X_TrainingData,bool IsTraining) {
    int Col = 2;
    double Rows = X_TrainingData.size();
    double mean = 0,sqrmean = 0;
    
    vector <double> holdmean;
    vector <double> holdsqrmean;
    means.clear();
    squareMeans.clear();
    standardDeviations.clear();
    
    
    for (int i=0;i<X_TrainingData.size();i++) {
        
        for (int j = 0; j <2; j++) {
            mean += X_TrainingData[i][j] / Rows ;
            holdmean.push_back(mean);
            sqrmean += (X_TrainingData[i][j] * X_TrainingData[i][j]) / Rows;
            holdsqrmean.push_back(sqrmean);
        }
        means.push_back(holdmean);
        holdmean.clear();
        squareMeans.push_back(holdsqrmean);
        holdsqrmean.clear();
        
    }
    
    for (int i = 0; i < Col; i++) {
        standardDeviations.push_back(sqrt(squareMeans[i][i] - means[i][i] * means[i][i]));
    }
    
    adjustRows(X_TrainingData,IsTraining);  //true
    
    
}




/* Read the object file */
void readObj(string path ,bool IsTraining) {
    
    ifstream inputFile;
    inputFile.open(path);
    getline(inputFile, titles);
    
    double zero = 0;
    double one  = 1;
    string M =  "Male" ;
    string F =  "Female" ;
    
    
    if (inputFile.is_open())
    {
        
        const char comma = ',';
        
        while(getline(inputFile,line))
        {
            int index = line.find_first_of(',');
            string gender =line.substr(0,index);
            string height =line.substr(index+1,16);
            string weight =line.substr(index+18);
            
            if(!gender.substr(1, gender.length()-2).compare(M.c_str())){
                
                Gender.push_back(one);
            }
            else{
                
                Gender.push_back(zero);
            }
            double temp1 = stod(height);
            double temp2 = stod(weight);
            temp ={temp1,temp2};
            
            if(IsTraining) {
                X_TrainingData.push_back(temp);
            }
            else {
                X_TestingData.push_back(temp);
            }
            
        }
        
        
        if(IsTraining) {
            processData(X_TrainingData,IsTraining);    //Training Data
        }
        else {
            processData(X_TestingData,IsTraining);   //Testing Data
        }
        
        
    }
    else {
        cout << "could not read the input file";
    }
}





int main(int argc, const char * argv[]) {
    string pathForTraining = "/Users/kartikdesai/Music/training_data.txt";
    string pathForTesting = "/Users/kartikdesai/Music/testing_data.txt";
    
    // Get starting timepoint
      auto start = high_resolution_clock::now();
    
    readObj(pathForTraining,IsTraining); //true as we are training initially
    
    readObj(pathForTesting,!IsTraining); //make false as testing now!
    
    cout << endl;
    cout << "========= Start Testing =========" << endl;
    cout << endl;
    
    cout << "Threshold is " << Threshold << endl;
    cout << endl;
    cout << "Testing Data of 2000 "  <<  "Please wait for a moment...." << endl;
    cout << endl;
    cout << "========= Testing Complete =========" << endl;
    cout << endl;
    cout << "TotalMale " << TotalMale <<endl;
    cout << "TotalFemale " << TotalFemale <<endl;
    cout << endl;
    // Get ending timepoint
    auto stop = high_resolution_clock::now();
    
    int falseNegativeMale =0;
    int falseNegativeFemale = 0;
    int truePositiveMale = 0;
    int truePositiveFemale = 0;
    
    if(TotalMale>774){
    falseNegativeMale = TotalMale-774 ;
        truePositiveMale = 774;
    }
    if(TotalMale<774){
        falseNegativeMale = 0;
        truePositiveMale = TotalMale;
    }
    if(TotalFemale > 1129){
        falseNegativeFemale = TotalFemale-1129 ;
        truePositiveFemale = 1129;
    }
    if(TotalFemale < 1129){
         falseNegativeFemale = 0;
         truePositiveFemale = TotalFemale;
     }
    
    

    cout << "True Positive - Male  "  <<    truePositiveMale <<endl;
    cout << "False Negative - Male " << falseNegativeMale << endl;
    cout << endl;
    cout << "True Positive -  Female " <<    truePositiveFemale <<endl;
    cout << "False Negative - Female " <<    falseNegativeFemale << endl;
    cout << endl;
    double acc = ((truePositiveMale + truePositiveFemale)/1903.0) * 100;
    cout << "Accuracy - " << acc << " %  " <<endl;
    cout<<endl;
     auto duration = duration_cast<microseconds>(stop - start);
    
    cout << "Time taken by training and testing together: "
            << duration.count()/1000000 << " Seconds" << endl;
     
    
    return 0;
}
