# Gender-Prediction
A C++ project which can detect gender using Logistic Regression


### Results 

![Graph1](https://github.com/kaddy645/Gender-Prediction/blob/main/graph.png)

![Graph2](https://github.com/kaddy645/Gender-Prediction/blob/main/graph2.png)


![Flowchart](https://github.com/kaddy645/Gender-Prediction/blob/main/algo.png)

### Output


Test Case 1 :- \
Initial Cost => 0.693147 \
========= Start Training ========= \
Learning Rate / α is 0.45 \
Iterations are 1 Please wait for a moment.... \
========= Training Complete ========= \
Weights are 0.00201291 0.000703586 Theta (θ2 & θ3) \
Final Cost => 0.615877 biasWeight => 0.00511859 \
========= Start Testing ========= \
Threshold is 0.5 \
Testing Data of 2000 Please wait for a moment.... ========= Testing Complete ========= \
TotalMale 678 TotalFemale 1225 \
True Positive - Male 678 False Negative - Male 0 \
True Positive - Female 1129 False Negative - Female 96 \
Accuracy - 94.9553 % 


Test Case 2 :- \
Initial Cost => 0.693147 \
========= Start Training ========= \
Learning Rate / α is 0.01 \
Iterations are 25000 Please wait for a moment.... \
========= Training Complete ========= \
Weights are 0.0590647 0.0342875 Theta (θ2 & θ3) \
Final Cost => 0.0652292 biasWeight => 3.89047 \
========= Start Testing ========= \
Threshold is 0.7 \
Testing Data of 2000 Please wait for a moment.... ========= Testing Complete ========= \
TotalMale 1281 TotalFemale 622 \
True Positive - Male 774 False Negative - Male 507 \
True Positive - Female 622 False Negative - Female 0 \
Accuracy - 73.3579 % \
Time taken by training and testing together: 88 Seconds

Test Case 3:- \
Initial Cost => 0.693147 \
========= Start Training ========= \
Learning Rate / α is 1 \
Iterations are 3000 Please wait for a moment.... \
========= Training Complete ========= \
Weights are 0.13633 0.0490174 Theta (θ2 & θ3) \
Final Cost => 0.0257976 biasWeight => 9.70655 \
========= Start Testing ========= \
Threshold is 0.5 \
Testing Data of 2000 Please wait for a moment.... ========= Testing Complete ========= \
TotalMale 1600 TotalFemale 303 \
True Positive - Male 774 False Negative - Male 826 \
True Positive - Female 303 False Negative - Female 0 \
Accuracy - 56.5949 % \
Time taken by training and testing together: 10 Seconds 
