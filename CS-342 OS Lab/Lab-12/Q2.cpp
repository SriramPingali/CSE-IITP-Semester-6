#include <bits/stdc++.h>

using namespace std;

// Book keeping vectors 
// for all algorithms
int count_ = 0;
int slookup_thm = 0;
vector<double> slookup;
vector<double> slookup_time;

// Utility function for plotting graph
void plot(vector<double>&x, vector<double>&y, string title)
{
    int total_points = x.size();
    string x_label = "set xlabel \"Seek time (ms)\"";
    string y_label = "set ylabel \"#Cylinders\"";
    FILE *fp = fopen("data.txt", "w");
    for(int i=0; i<total_points; i++){
        fprintf(fp, "%lf %lf\n", x[i], y[i]);
    }
    fclose(fp);

    fp = fopen("script.gnuplot","w");
    
    //make script file
    title = "\"" + title + "\"";
    title = "set title " + title;
    
    fprintf(fp, "%s\n", title.c_str());
    fprintf(fp, "%s\n", x_label.c_str());
    fprintf(fp, "%s\n", y_label.c_str());

    fprintf(fp, "plot 'data.txt' with linespoints\n");
    fprintf(fp, "pause -1");
    fclose(fp);

    system("gnuplot 'script.gnuplot'");
}

// Utility function to simulate SLOOKUP
int SLOOKUP(int current, vector<int> requests, int flag)
{
    // If single request left, execute it
    if(requests.size() == 1)
    {
        slookup.push_back(requests[0]);
        return 0;
    }

    // Iterator to find index of element
    vector<int>::iterator it = std::find(requests.begin(), requests.end(), current);
    int index = it - requests.begin();

    // If an end reached, reverse
    if(index == 0 || index == requests.size() - 1)
    {
        if(count_ == 0)
            flag = (flag + 1) % 2;
        count_++;
    }
    
    // Move left or right according to flag
    if(flag == 0)
        current = requests[index - 1];
    else if(flag == 1)
        current = requests[index + 1];

    //Update log books
    // cout << "Removing: " << requests[index] << " Current: " << current << endl;
    slookup_thm += abs(requests[index] - current);
    slookup.push_back(requests[index]);
    slookup_time.push_back(slookup_thm * 5);
    requests.erase(it);

    SLOOKUP(current, requests, flag);
}

// Driver code
int main()
{
    int req;
    int temp;
    int size = 200;
    int current = 100;
    vector<int> requests;

    // No. of requests
    cout << "Enter number of requests" << endl;
    cin >> req;

    // Work queue
    cout << "Enter the work queue" << endl;
    requests.push_back(current);
    for (int i = 0; i < req; i++)
    {
        cin >> temp;
        requests.push_back(temp);
    }

    // Determine the direction
    int flag;
    sort(requests.begin(), requests.end());
    if(abs(current - requests[0]) <= abs(current - requests[requests.size() - 1]))
        flag = 0;
    else
        flag = 1;

    // Perform SLOOKUP
    cout << "S-LOOKUP Algorithm" << endl;
    slookup_time.push_back(0);
    SLOOKUP(current, requests, flag);
    requests.pop_back();
    cout << "Head Movement: " << slookup_thm << " Seek Time: " << slookup_thm * 5 << endl;

    // Plot graph
    plot(slookup_time, slookup, "SLOOKUP");

}