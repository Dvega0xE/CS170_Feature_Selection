#include "classifier.h"

Classifier::Classifier(){}

Classifier::~Classifier(){}

void Classifier::train(string filename){
    ifstream inFS(filename);
    string data;
    string value;
    int countID = 0;

    while(!inFS.eof()){
        Instance* dataPoint = new Instance();
        dataPoint->instanceID = countID;
        getline(inFS, data);
        istringstream iss(data);
        while(iss >> value){
            dataPoint->features.push_back(stod(value));
        }
        countID++;
        this->instances.push_back(dataPoint);
        if(dataPoint->features.size() != 0){
            dataPoint->classLabel = dataPoint->features.at(0);
        }
    }
    this->instances.pop_back();
    this->numFeatures = this->instances.at(0)->features.size()-1;
    inFS.close();
}

double Classifier::test(double instance_id){
    Instance* test_instance = this->instances.at(instance_id);
    vector<double> testVec1(test_instance->features.begin()+1, test_instance->features.end());
    int nearestNeighborID;
    double bestScore = DBL_MAX;

    for(int i = 0; i < instances.size(); i++){
        if(i == instance_id){
            continue;
        }
        vector<double> testVec2(instances.at(i)->features.begin()+1, instances.at(i)->features.end());
        if(vectors_distance(testVec1, testVec2) < bestScore){
            bestScore = vectors_distance(testVec1, testVec2);
            nearestNeighborID = i;
        }
    }
    //cout << "Best neighbor is instance " << nearestNeighborID << " with a distance of " << bestScore << " so label should be ";
    //cout << instances.at(nearestNeighborID)->classLabel << endl;
    return instances.at(nearestNeighborID)->classLabel;
}

