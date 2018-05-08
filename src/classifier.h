/*
 * classifier.h
 *
 *  Created on: May 4, 2018
 *      Author: atpandey
 */

#ifndef CLASSIFIER_H
#define CLASSIFIER_H
#include <iostream>
#include <sstream>
#include <fstream>
#include <math.h>
#include <vector>

using namespace std;

class GNB {
public:

	vector<string> possible_labels = {"left","keep","right"};
	int left_lane_count;
	int right_lane_count;
	int keep_lane_count;
	int total_train_label_count;

	//it's not necessary but am curating and segragating the data for each label type
	vector<vector<double>> left_lane_data;
	vector<vector<double>> right_lane_data;
	vector<vector<double>> keep_lane_data;



	//vector because avgs/std are s/d/sdot/ddot

	//get sum first
	vector<double> left_lane_sum;
	vector<double> right_lane_sum;
	vector<double> keep_lane_sum;
	//then avg
	vector<double> left_lane_avg;
	vector<double> right_lane_avg;
	vector<double> keep_lane_avg;
	//then std dev
	vector<double> left_lane_std;
	vector<double> right_lane_std;
	vector<double> keep_lane_std;

	//then probability
	double prob_left_lane;
	double prob_right_lane;
	double prob_keep_lane;

	//gaussian naive prob
	double gauss_prob_left_lane;
	double gauss_prob_right_lane;
	double gauss_prob_keep_lane;

	/**
  	* Constructor
  	*/
 	GNB();

	/**
 	* Destructor
 	*/
 	virtual ~GNB();

 	void train(vector<vector<double> > data, vector<string>  labels);

  	string predict(vector<double>);

  	//gaussian prob function calculator
  	vector<double> gaussian_prob(vector<double> std,vector<double> avg,vector<double> data);
};

#endif
