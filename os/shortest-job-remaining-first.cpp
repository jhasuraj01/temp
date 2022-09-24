#include <bits/stdc++.h>
using namespace std;

// Comparators
struct Process {
    string name;
    int arival_time;
    int service_time;
    int start_time;
    int end_time;
    int turn_around_time;
    int waiting_time;
};

vector<string> shortestJobRemainingFirstPremptive(vector<Process> processes) {
    auto shortestJobTop = [&](Process p1, Process p2) {
        if(p1.service_time != p2.service_time)
            return p1.service_time > p2.service_time;
        return p1.arival_time > p2.arival_time;
    };

    priority_queue<Process, vector<Process>, decltype(shortestJobTop)> order(shortestJobTop);

    int max_execution_time = 0;
    for(auto process: processes) max_execution_time += process.service_time;

    int curr_process = 0;
    int total_processes = processes.size();
    int execution_time = 0;
    int current_time = 0;
    vector<string> execution_order;

    while(execution_time < max_execution_time) {
        while(curr_process < total_processes && processes[curr_process].arival_time <= current_time) {
            order.push(processes[curr_process]);
            curr_process++;
        }

        if(!order.empty()) {
            Process process = order.top(); order.pop();
            execution_order.push_back(process.name);
            process.service_time -= 1;
            if(process.service_time > 0)
                order.push(process);
            execution_time++;
        }
        else {
            execution_order.push_back("-");
        }
        current_time++;
    }

    return execution_order;
}

vector<string> shortestJobRemainingFirstNonPremptive(vector<Process> processes) {
    auto shortestJobTop = [&](Process p1, Process p2) {
        if(p1.service_time != p2.service_time)
            return p1.service_time > p2.service_time;
        return p1.arival_time > p2.arival_time;
    };

    priority_queue<Process, vector<Process>, decltype(shortestJobTop)> order(shortestJobTop);

    int max_execution_time = 0;
    for(auto process: processes) max_execution_time += process.service_time;

    int curr_process = 0;
    int total_processes = processes.size();
    int execution_time = 0;
    int current_time = 0;
    vector<string> execution_order;

    while(execution_time < max_execution_time) {
        while(curr_process < total_processes && processes[curr_process].arival_time <= current_time) {
            order.push(processes[curr_process]);
            curr_process++;
        }

        if(!order.empty()) {
            Process process = order.top(); order.pop();
            for (int i = 0; i < process.service_time; ++i) {
                execution_order.push_back(process.name);
                execution_time++;
                current_time++;
            }
        }
        else {
            execution_order.push_back("-");
            current_time++;
        }
    }

    return execution_order;
}

vector<Process> input_processes() {
    
    cout << "Enter No. of Processes: " ;
    int N; cin >> N;

    vector<Process> processes;

    for(int i = 0; i < N; ++i) {
        Process process;
        cout << "Name: ";
        cin >> process.name;
        cout << "Arival Time: ";
        cin >> process.arival_time;
        cout << "Service Time: ";
        cin >> process.service_time;

        processes.push_back(process);
    }

    sort(processes.begin(), processes.end(), [&](Process p1, Process p2) {
        return p1.arival_time <= p2.arival_time;
    });

    return processes;
}

void calculateFactors(vector<Process> &processes, vector<string> &execution_order) {
    // process_name -> start, end;
    map<string, pair<int, int>> start_end;

    for (int i = 0; i < execution_order.size(); ++i)
    {
        string process_name = execution_order[i];
        if(start_end.count(process_name)) {
            start_end[process_name].second = i+1;
        }
        else {
            start_end[process_name].first = i;
            start_end[process_name].second = i+1;
        }
    }

    for(auto &process: processes) {
        process.start_time = start_end[process.name].first;
        process.end_time = start_end[process.name].second;
        process.turn_around_time = process.end_time - process.arival_time;
        process.waiting_time = process.turn_around_time - process.service_time;
    }
}

void print_processes(vector<Process> processes, vector<string> execution_order) {

    cout << '\n' << string(51, '-') << " Table " << string(51, '-') << '\n';
    cout << "Name" << "\t"
            << "Arival Time" << "\t"
            << "Service Time" << "\t"
            << "Start Time" << "\t"
            << "End Time" << "\t"
            << "Turn Around Time" << "\t"
            << "Waiting Time"
            << '\n';
    for(auto process: processes) {
        cout << process.name << "\t"
             << process.arival_time << "\t\t"
             << process.service_time << "\t\t"
             << process.start_time << "\t\t"
             << process.end_time << "\t\t"
             << process.turn_around_time << "\t\t\t"
             << process.waiting_time
             << '\n';
    }
    cout << '\n' << string(109, '-') << '\n';

    cout << "Execution Order: ";
    for(auto name: execution_order) cout << name << "  ";
    cout << '\n';

    double avg_turn_around_time = 0, avg_waiting_time = 0;
    for(auto process: processes) {
        avg_turn_around_time += process.turn_around_time;
        avg_waiting_time += process.waiting_time;
    }
    avg_turn_around_time /= processes.size();
    avg_waiting_time /= processes.size();

    cout << "Average Turn Around Time: " << setprecision(2) << avg_turn_around_time << "\n";
    cout << "Average Waiting Time: " << setprecision(2) << avg_waiting_time << "\n";
}

int main() {
    vector<Process> processes = input_processes();
    vector<string> execution_order;

    cout << '\n' << string(15, '*') << "Shortest Job Remaining First Premptive**" << string(10, '*') << '\n';
    execution_order = shortestJobRemainingFirstPremptive(processes);
    calculateFactors(processes, execution_order);
    print_processes(processes, execution_order);

    
    cout << '\n' << string(13, '*') << "Shortest Job Remaining First Non Premptive" << string(10, '*') << '\n';
    execution_order = shortestJobRemainingFirstNonPremptive(processes);
    calculateFactors(processes, execution_order);
    print_processes(processes, execution_order);

    return 0;
}