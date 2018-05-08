/*
 * classifier.cpp
 *
 *  Created on: May 4, 2018
 *      Author: atpandey
 */


#include <iostream>
#include <sstream>
#include <fstream>
#include <math.h>
#include <vector>
#include "classifier.h"

using namespace std;

/**
 * Initializes GNB
 */
GNB::GNB() {
	left_lane_count=0;
	right_lane_count=0;
	keep_lane_count=0;
	total_train_label_count=0;

	//it's not necessary but am curating and segragating the data for each label type
	//vector<vector<double>> left_lane_data;
	//vector<vector<double>> right_lane_data;
	//vector<vector<double>> keep_lane_data;



	//vector because avgs/std are s/d/sdot/ddot

	//get sum first
	left_lane_sum ={0.0,0.0,0.0,0.0};
	right_lane_sum ={0.0,0.0,0.0,0.0};
	keep_lane_sum={0.0,0.0,0.0,0.0};
	//then avg
	left_lane_avg={0.0,0.0,0.0,0.0};
	right_lane_avg={0.0,0.0,0.0,0.0};
	keep_lane_avg={0.0,0.0,0.0,0.0};
	//then std dev
	left_lane_std={0.0,0.0,0.0,0.0};
	right_lane_std={0.0,0.0,0.0,0.0};
	keep_lane_std={0.0,0.0,0.0,0.0};

	//then probability
	prob_left_lane=0.0;
	prob_right_lane=0.0;
	prob_keep_lane=0.0;

	cout <<"Init Done"<<endl;


}

GNB::~GNB() {}

void GNB::train(vector<vector<double>> data, vector<string> labels)
{

	/*
		Trains the classifier with N data points and labels.

		INPUTS
		data - array of N observations
		  - Each observation is a tuple with 4 values: s, d,
		    s_dot and d_dot.
		  - Example : [
			  	[3.5, 0.1, 5.9, -0.02],
			  	[8.0, -0.3, 3.0, 2.2],
			  	...
		  	]

		labels - array of N labels
		  - Each label is one of "left", "keep", or "right".
	*/

	//Calculate averages and std dev
	//iterate through data and labels
	//build new vector for left/right/and/keep data (increase counters left_lane_count/right_lane_count/keep_lane_count)
	//sum s/d/sdot/ddot fields of these vector and divide for respective counts to get avg
	//after average calculate std as sqrt(sum(x[i]-std)/count)

	//For each label, compute the numerators of the means for each class
	//and the total number of data points given with that label.


	//Enh:add assert that labels and data size is same
	cout <<"Size of Data: "<<data.size()<<endl;
	cout <<"Size of labels: "<<labels.size()<<endl;


	//capture lane label data
	string out_file_name_left="./left_lane.txt";
	ofstream out_file_left (out_file_name_left, ofstream::out);
	if (!out_file_left.is_open())  {
		cerr << "Cannot open output file: " << out_file_name_left << endl;
		exit(EXIT_FAILURE);
	}

	string out_file_name_right="./right_lane.txt";
	ofstream out_file_right (out_file_name_right, ofstream::out);
	if (!out_file_right.is_open())  {
		cerr << "Cannot open output file: " << out_file_name_right << endl;
		exit(EXIT_FAILURE);
	}

	string out_file_name_keep="./keep_lane.txt";
	ofstream out_file_keep (out_file_name_keep, ofstream::out);
	if (!out_file_keep.is_open())  {
		cerr << "Cannot open output file: " << out_file_name_keep << endl;
		exit(EXIT_FAILURE);
	}





	for (int i=0; i<labels.size(); i++){
			if(labels[i]=="left") {
				left_lane_data.push_back(data[i]);

				for(int j=0;j<data[i].size();j++) {
					left_lane_sum[j] +=data[i][j];
					out_file_left << data[i][j]<<",";
				}
				out_file_left<<endl;

				left_lane_count++;
			}
			if(labels[i]=="right") {
				right_lane_data.push_back(data[i]);

				for(int j=0;j<data[i].size();j++) {
					right_lane_sum[j] +=data[i][j];
					out_file_right << data[i][j]<<",";
				}
				out_file_right<<endl;
				right_lane_count++;
			}
			if(labels[i]=="keep") {
				keep_lane_data.push_back(data[i]);

				for(int j=0;j<data[i].size();j++) {
					keep_lane_sum[j] +=data[i][j];
					out_file_keep << data[i][j]<<",";
				}
				out_file_keep<<endl;
				keep_lane_count++;
			}
		}

	cout<<"Left lane data: "<<left_lane_data.size()<<endl;
	cout<<"Right lane data: "<<right_lane_data.size()<<endl;
	cout<<"Keep lane data: "<<keep_lane_data.size()<<endl;

		//Average
		//Enh:add assert for vector size of left/right/keep_lane_data mismatch
		for(int i=0;i < left_lane_sum.size();i++){
			left_lane_avg[i]=left_lane_sum[i]/left_lane_count;
			right_lane_avg[i]=right_lane_sum[i]/right_lane_count;
			keep_lane_avg[i]=keep_lane_sum[i]/keep_lane_count;
			cout<<"IDX: "<<i <<" Avg left: "<<left_lane_avg[i]<<endl;
			cout<<"IDX: "<<i <<" Avg right: "<<right_lane_avg[i]<<endl;
			cout<<"IDX: "<<i <<" Avg keep: "<<keep_lane_avg[i]<<endl;
		}

		//std dev numerator
		//
		for (int i=0; i<labels.size(); i++){
			if(labels[i]=="left") {
				for(int j=0;j<data[i].size();j++) {
					left_lane_std[j] += pow((data[i][j]-left_lane_avg[j]),2);

				}

			}
			if(labels[i]=="right") {
				for(int j=0;j<data[i].size();j++) {
					right_lane_std[j] += pow((data[i][j]-right_lane_avg[j]),2);

				}

			}
			if(labels[i]=="keep") {
				for(int j=0;j<data[i].size();j++) {
					keep_lane_std[j] += pow((data[i][j]-keep_lane_avg[j]),2);

				}
			}
		}

		//std dev
		for(int j=0;j<left_lane_std.size();j++){
			left_lane_std[j] = sqrt(left_lane_std[j]/left_lane_count);
			right_lane_std[j] = sqrt(right_lane_std[j]/right_lane_count);
			keep_lane_std[j] = sqrt(keep_lane_std[j]/keep_lane_count);
			cout<<"IDX: "<<j <<" std left: "<<left_lane_std[j]<<endl;
			cout<<"IDX: "<<j <<" std right: "<<right_lane_std[j]<<endl;
			cout<<"IDX: "<<j <<" std keep: "<<keep_lane_std[j]<<endl;

		}


		//probs
		total_train_label_count=left_lane_count+right_lane_count+keep_lane_count;
		cout<<" left count: "<<left_lane_count<<endl;
		cout<<" right count: "<<right_lane_count<<endl;
		cout<<" keep count: "<<keep_lane_count<<endl;
		cout<<" total count: "<<total_train_label_count<<endl;

		prob_left_lane=double(left_lane_count)/double(total_train_label_count);
		prob_right_lane=double(right_lane_count)/double(total_train_label_count);
		prob_keep_lane=double(keep_lane_count)/double(total_train_label_count);
		cout<<" prior left: "<<prob_left_lane<<endl;
		cout<<" prior right: "<<prob_right_lane<<endl;
		cout<<" prior keep: "<<prob_keep_lane<<endl;


		//close the data capture file
		out_file_left.close();
		out_file_right.close();
		out_file_keep.close();
}


string GNB::predict(vector<double> sample)
{
	/*
		Once trained, this method is called and expected to return
		a predicted behavior for the given observation.

		INPUTS

		observation - a 4 tuple with s, d, s_dot, d_dot.
		  - Example: [3.5, 0.1, 8.5, -0.2]

		OUTPUT

		A label representing the best guess of the classifier. Can
		be one of "left", "keep" or "right".
		"""
		#
	*/

	//lane prob for each field, redundant looping, this can be done in gaussian prob itself
	vector<double> left_lane_prob1=gaussian_prob(left_lane_std,left_lane_avg,sample);
	vector<double> right_lane_prob1=gaussian_prob(right_lane_std,right_lane_avg,sample);
	vector<double> keep_lane_prob1=gaussian_prob(keep_lane_std,keep_lane_avg,sample);

	//conditional prob --> multiply each of the prob for s/d/sdot/ddot
	double left_p = 1.0;
	double keep_p = 1.0;
	double right_p = 1.0;
	for(int i=0;i<left_lane_prob1.size();i++){
		left_p *=left_lane_prob1[i];
		keep_p *= keep_lane_prob1[i];
		right_p *= right_lane_prob1[i];
	}


	//multiply by prior from train

	cout <<"Left p: "<<left_p<<endl;
	cout <<"right p: "<<right_p<<endl;
	cout <<"keep p: "<<keep_p<<endl;

	left_p *= prob_left_lane;
	right_p *= prob_right_lane;
	keep_p *= prob_keep_lane;

	//argmax
	double probs[3] = {left_p, keep_p, right_p};
	double max = left_p;
	double max_index = 0;
	for (int i=1; i<3; i++){
		if (probs[i] > max) {
			max = probs[i];
			max_index = i;
		}
	}

	return this->possible_labels[max_index];

}


vector<double> GNB::gaussian_prob(vector<double> std,vector<double> avg,vector<double> data){
	//for each filed in std/avg/data calculate prob function
	vector<double> prob_vect={0.0,0.0,0.0,0.0};
	for (int i=0;i<std.size();i++) {
		double const_fact=1.0/sqrt(2.0*M_PI*std[i]*std[i]);
		double exp_fact=-0.5*pow((data[i]-avg[i]),2) / (std[i]*std[i]);
		double prob= const_fact*exp(exp_fact);
		prob_vect[i]=prob;
	}

	return prob_vect;

}

/*
string GNB::predict(vector<double> sample)
{ */
	/*
		Once trained, this method is called and expected to return
		a predicted behavior for the given observation.

		INPUTS

		observation - a 4 tuple with s, d, s_dot, d_dot.
		  - Example: [3.5, 0.1, 8.5, -0.2]

		OUTPUT

		A label representing the best guess of the classifier. Can
		be one of "left", "keep" or "right".
		"""
		# TODO - complete this
	*/

	/*//Calculate product of conditional probabilities for each label.
	double left_p = 1.0;
	double keep_p = 1.0;
	double right_p = 1.0;
	for (int i=0; i<4; i++){
	    left_p *= (1.0/sqrt(2.0 * M_PI * pow(left_lane_std[i], 2))) * exp(-0.5*pow(sample[i] - left_lane_avg[i], 2)/pow(left_lane_std[i], 2));
	    keep_p *= (1.0/sqrt(2.0 * M_PI * pow(keep_lane_std[i], 2))) * exp(-0.5*pow(sample[i] - keep_lane_avg[i], 2)/pow(keep_lane_std[i], 2));
	    right_p *= (1.0/sqrt(2.0 * M_PI * pow(right_lane_std[i], 2))) * exp(-0.5*pow(sample[i] - right_lane_avg[i], 2)/pow(right_lane_std[i], 2));
	}


	cout <<"Left p: "<<left_p<<endl;
	cout <<"right p: "<<right_p<<endl;
	cout <<"keep p: "<<keep_p<<endl;
	//Multiply each by the prior
	left_p *= prob_left_lane;
	keep_p *= prob_keep_lane;
	right_p *= prob_right_lane;

    double probs[3] = {left_p, keep_p, right_p};
    double max = left_p;
    double max_index = 0;
    for (int i=1; i<3; i++){
        if (probs[i] > max) {
            max = probs[i];
            max_index = i;
        }
    }

	return this -> possible_labels[max_index];

} */


