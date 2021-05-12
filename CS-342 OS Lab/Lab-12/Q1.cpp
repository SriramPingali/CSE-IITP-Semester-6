#include <bits/stdc++.h>

using namespace std;

// Book keeping vectors 
// for all algorithms
int fcfs_thm = 0;
vector<double> fcfs;
vector<double> fcfs_time;
int scan_thm = 0;
vector<double> scan;
vector<double> scan_time;
int cscan_thm = 0;
vector<double> cscan;
vector<double> cscan_time;
int sstf_thm = 0;
vector<double> sstf;
vector<double> sstf_time;

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

// Utility function to simulate FCFS
int FCFS(int current, vector<int> requests)
{
    // If single request left, execute it
    if(requests.size() == 1)
    {
        fcfs.push_back(requests[0]);
        return 0;
    }

    // Iterator to find index of element
    vector<int>::iterator it = std::find(requests.begin(), requests.end(), current);
    int index = it - requests.begin();

    // Move head to next location
    current = requests[index + 1];

    // Update log books
    // cout << "Removing: " << requests[index] << " Current: " << current << endl;
    fcfs_thm += abs(requests[index] - current);
    fcfs.push_back(requests[index]);
    fcfs_time.push_back(fcfs_thm * 5);
    requests.erase(it);

    // Recursive call for next request
    FCFS(current, requests);
}

// Utility function to simulate SCAN
int SCAN(int current, vector<int> requests, int flag)
{
    // If single request left, execute it
    if(requests.size() == 1)
    {
        scan.push_back(requests[0]);
        return 0;
    }

    // Sorting essential for scan
    sort(requests.begin(), requests.end());

    // Iterator to find index of element
    vector<int>::iterator it = std::find(requests.begin(), requests.end(), current);
    int index = it - requests.begin();

    // If end reached, reverse
    if(index == 0)
    {
        flag = 1;
    }
    
    // Move head to next location
    if(flag == 0)
        current = requests[index - 1];
    else if(flag == 1)
        current = requests[index + 1];

    // Update log books
    // cout << "Removing: " << requests[index] << " Current: " << current << endl;
    scan_thm += abs(requests[index] - current);
    scan.push_back(requests[index]);
    scan_time.push_back(scan_thm * 5);
    requests.erase(it);

    // Recursive call for next request
    SCAN(current, requests, flag);
}

// Utility function to simulate CSCAN
int CSCAN(int current, vector<int> requests)
{
	// If single request left, execute it
    if(requests.size() == 1)
    {
        cscan.push_back(requests[0]);
        return 0;
    }

    // Sorting essential for cscan
    sort(requests.begin(), requests.end());

    // Iterator to find index of element
    vector<int>::iterator it = std::find(requests.begin(), requests.end(), current);
    int index = it - requests.begin();

    // Move head to next location
    if(index == 0)
    {
        current = 199;
    }
    else
        current = requests[index - 1];

    // Update log books
    // cout << "Removing: " << requests[index] << " Current: " << current << endl;
    cscan_thm += abs(requests[index] - current);
    cscan.push_back(requests[index]);
    cscan_time.push_back(cscan_thm * 5);
    requests.erase(it);

    // Recursive call for next request
    CSCAN(current, requests);
}

// Utility function to simulate SSTF
int SSTF(int current, vector<int> requests)
{
    // If single request left, execute it
    if(requests.size() == 1)
    {
        sstf.push_back(requests[0]);
        return 0;
    }

    // Sorting essential for sstf
    sort(requests.begin(), requests.end());

    // Iterator to find index of element
    vector<int>::iterator it = std::find(requests.begin(), requests.end(), current);
    int index = it - requests.begin();

    // Move head to next location
    if(index < requests.size() - 1)
    {
        // Check least distance
        int left = abs(requests[index - 1] - requests[index]);
        int right = abs(requests[index + 1] - requests[index]);
        if(left<=right)
            current = requests[index - 1];
        else
            current = requests[index + 1];
    }
    else if(index == requests.size() - 1)
        current = requests[index - 1];
    else if(index == 0)
        current = requests[index + 1];

    // Update log books
    // cout << "Removing: " << requests[index] << " Current: " << current << endl;
    sstf_thm += abs(requests[index] - current);
    sstf.push_back(requests[index]);
    sstf_time.push_back(sstf_thm * 5);
    requests.erase(it);

    // Recursive call for next request
    SSTF(current, requests);
}

// Utility function for sorting
bool sortbysec(const pair<string,int> &a,
              const pair<string,int> &b)
{
    return (a.second < b.second);
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

    // Perform FCFS
    cout << "FCFS Algorithm" << endl;
    fcfs_time.push_back(0);
    FCFS(current, requests);
    cout << "Head Movement: " << fcfs_thm << " Seek Time:" << fcfs_thm * 5 << endl;

    // Perform SCAN
    cout << "SCAN Algorithm" << endl;
    scan_time.push_back(0);
    requests.push_back(0);
    SCAN(current, requests, 0);
    requests.pop_back();
    cout << "Head Movement: " << scan_thm << " Seek Time: " << scan_thm * 5 << endl;

    // Perform CSCAN
    cout << "CSCAN Algorithm" << endl;
    cscan_time.push_back(0);
    requests.push_back(0);
    requests.push_back(199);
    CSCAN(current, requests);
    requests.pop_back();
    requests.pop_back();
    cout << "Head Movement: " << cscan_thm << " Seek Time: " << cscan_thm * 5 << endl;

    // Perform SSTF
    cout << "SSTF Algorithm" << endl;
    sstf_time.push_back(0);
    SSTF(current, requests);
    cout << "Head Movement: " << sstf_thm << " Seek Time: " << sstf_thm * 5 << endl;
    
    vector < pair<string, int> > order;
    order.push_back(make_pair("FCFS", fcfs_thm));
    order.push_back(make_pair("SCAN", scan_thm));
    order.push_back(make_pair("CSCAN", cscan_thm));
    order.push_back(make_pair("SSTF", sstf_thm));

    // performance order
    cout << "Optimal Algorithm order: " << endl;
    sort(order.begin(), order.end(), sortbysec);

    for (int i = 0; i < 4; ++i)
    {
    	cout << order[i].first << "> ";
    }
    cout << endl;

    // Plot any one graph
    cout << "Choose which graph to plot (FCFS=0/SCAN=1/CSCAN=2/SSTF=3): " << endl; 
    int graph;
    cin >> graph;

    switch(graph)
    {
    	case 0:
    		plot(fcfs_time, fcfs, "FCFS");
    	case 1:
    		plot(scan_time, scan, "SCAN");
    	case 2:
    		plot(cscan_time, cscan, "CSCAN");
    	case 3:
    		plot(sstf_time, sstf, "SSTF");
    }

}