/*
https://www.geeksforgeeks.org/samsung-interview-experience-set-39-campus-r-d-noida/
https://www.careercup.com/page?pid=samsung-interview-questions

A Doctor travels from a division to other division where divisions are connected like a graph(directed graph) and 
the edge weights are the probabilities of the doctor going from that division to other connected division but the 
doctor stays 10mins at each division now there will be given time and had to find the division in which he will be 
staying by that time and is determined by finding division which has high probability.

Input is number of test cases followed by the number of nodes, edges, time after which we need to find the division 
in which he will be there, the edges starting point, end point, probability.

Note: If he reaches a point where there are no further nodes then he leaves the lab after 10 mins and the traveling 
time is not considered and during that 10min at 10th min he will be in next division, so be careful

2
6 10 40 
1 2 0.3 1 3 0.7 3 3 0.2 3 4 0.8 2 4 1 4 5 0.9 4 4 0.1 5 6 1.0 6 3 0.5 6 6 0.5
6 10 10 
1 2 0.3 1 3 0.7 3 3 0.2 3 4 0.8 2 4 1 4 5 0.9 4 4 0.1 5 6 1.0 6 3 0.5 6 6 0.5

6 0.774000  
3 0.700000
*/

#include<iostream>
#include<vector>
using namespace std;

void docProb(const vector<vector<double>>& graph, int nodes, int time, int curNode, double p, vector<double>& answer) {
    if (time <= 0) {
        answer[curNode] += p;  // Add the current probability to the answer for the current node
        return;
    }

    for (int i = 0; i < nodes; i++) {  // 0-based indexing for nodes
        if (graph[curNode][i] != 0) {
            double nextP = p * graph[curNode][i];  // Multiply the current probability by the transition probability
            docProb(graph, nodes, time - 10, i, nextP, answer);  // Recursive call for next node
        }
    }
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        int nodes, edges, time;
        cin >> nodes >> edges >> time;
        
        // Initialize the graph with probabilities, 0-based indexing
        vector<vector<double>> arr(nodes, vector<double>(nodes, 0));

        int from, to;
        double prob;
        for (int i = 0; i < edges; i++) {
            cin >> from >> to >> prob;
            arr[from - 1][to - 1] = prob;  // Adjusting for 0-based indexing
        }

        // Initialize the answer vector with zeros
        vector<double> answer(nodes, 0.0);

        // Start from node 0 (assuming 0-based indexing), with initial probability of 1.0
        docProb(arr, nodes, time, 0, 1.0, answer);
        
        // Select the node with the maximum probability
        double finalProb = 0.0;
        int finalNode = 0;

        for (int i = 0; i < nodes; i++) {
            if (answer[i] > finalProb) {
                finalProb = answer[i];
                finalNode = i + 1;  // Convert back to 1-based indexing for output
            }
        }

        cout << finalNode << " " << finalProb << "\n";
    }
    return 0;
}

