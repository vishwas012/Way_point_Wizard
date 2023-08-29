#include <bits/stdc++.h>
#include <unistd.h>

using namespace std;

void TaskScheduling(int n, int deadlines[], int penalties[]) {

    cout << "All deadlines to be entered in interval of 10 minutes" << endl;
    for (int i=0; i<n; i++) {
        cout << "Enter deadline of order " << i+1 << ": ";
        cin >> deadlines[i];
    }
    for (int i=0; i<n; i++) {
        cout << "Enter % of penalty if late (for order " << i+1 << "): " ;
        cin >> penalties[i];
    }
    pair<int, int> final_positions[100];
    for (int i=0; i<n; i++) {
        final_positions[i].first = penalties[i];
        final_positions[i].second = deadlines[i];
    }
    int tasks[100] = {0};
    int left_tasks = 0;
    bool left_checker[100];
    int bhai_dekhle[100];

    for (int i=0; i<100; i++) {
        left_checker[i] = true;
    }

    sort(final_positions, final_positions + n);

    for (int i=0, j=n-1; i<n/2; i++, j--)   {
        int temp = final_positions[i].first;
        final_positions[i].first = final_positions[j].first;
        final_positions[j].first = temp;
        int temp2 = final_positions[i].second;
        final_positions[i].second = final_positions[j].second;
        final_positions[j].second = temp2;
    }

    for (int i=0; i<n; i++) {
        for (int j=final_positions[i].second; j>0; j-=10) {
            if (tasks[j] == 0) {
                tasks[j] = j;
                for (int k=0; k<n; k++) {
                    if (final_positions[i].second == deadlines[k] && final_positions[i].first == penalties[k]) {
                        bhai_dekhle[j/10] = k+1;
                    }
                }
                left_checker[i] = false;
                break;
            }
        }
        if (left_checker[i] == true) {
            left_tasks++;
        }
    }

    for (int i=0; i<n; i++) {
        if (left_checker[i] == true) {
            for (int j=10; j<=n*10; j+=10) {
                if (tasks[j] == 0) {
                    tasks[j] = j;
                    for (int k=0; k<n; k++) {
                        if (final_positions[i].second == deadlines[k] && final_positions[i].first == penalties[k]) {
                            bhai_dekhle[j/10] = k+1;
                        }
                    }
                    break;
                }
            }
        }
    }

    cout << endl << "Orders should be delivered in thee given order: " << endl;
    for (int i=1; i<=n; i++) {
        cout << bhai_dekhle[i] << " ";
    }

    cout << endl << "Orders being delivered late = " << left_tasks << endl << endl;

    for (int i=0; i<n; i++) {
        if (left_checker[i] == true) {
            cout << "Late arrival is order with penalty " << final_positions[i].first << endl;
            cout << "Hence a discount of " << final_positions[i].first << " % is provided on the billing amount" << endl << endl;
        }
    }
}


int max(int a, int b) {
    return (a > b) ? a : b;
}

void printknapSack(int max_weight, int weight[], int profit[], int size_profit) {


    for (int i=0; i<size_profit; i++) {
        cout << "Enter order value of order no " << i+1 << ": ";
        cin >> profit[i];
    }
    for (int i=0; i<size_profit; i++) {
        cout << "Enter no of items in the order " << i+1 << ": ";
        cin >> weight[i];
    }
    cout << "Total items that can be taken: ";
    cin >> max_weight;
	int ary[size_profit + 1][max_weight + 1];
	for (int i = 0; i <= size_profit; i++) {
		for (int w = 0; w <= max_weight; w++) {
			if (i == 0 || w == 0)
				ary[i][w] = 0;
			else if (weight[i - 1] <= w)
				ary[i][w] = max(profit[i - 1] + ary[i - 1][w - weight[i - 1]], ary[i - 1][w]);
			else
				ary[i][w] = ary[i - 1][w];
		}
	}
	int total_value = ary[size_profit][max_weight];
	int weight_left = max_weight;
    cout << endl << "Carrying orders in the following order will get maximum profit with the given weight constarint" << endl << endl;
	for (int i = size_profit; i > 0 && total_value > 0; i--) {
		if (total_value == ary[i - 1][weight_left])
			continue;
		else {
			cout << "Value of order worth " << profit[i - 1] << endl;
			total_value = total_value - profit[i - 1];
			weight_left = weight_left - weight[i - 1];
		}
	}
}


void tsp(int graph[10][10], bool completed[10], int n, int cost, int currPos, int counter, int& ans){


	if (counter == n && graph[currPos][0]) {
		ans = min(ans, cost + graph[currPos][0]);
		return;
	}
	for (int i = 0; i < n; i++) {
		if (!completed[i] && graph[currPos][i]) {
			completed[i] = true;
			tsp(graph, completed, n, cost + graph[currPos][i], i, counter + 1, ans);
			completed[i] = false;
		}
	}
};


int main() {
    cout << endl << "----Welcome User----" << endl << endl;
    cout << "You have 3 choices to deliver the orders, choose accordingly and enter the details asked" << endl << endl;
    cout << endl;
    cout << "1. Find the best economic way to deliver all the orders" << endl << endl;
    cout << "2. Check which orders are possible to deliver getting maximum profit with quantity constraint" << endl << endl;
    cout << "3. What is the maximum numbers of orders to be delivered without imposing penalty" << endl << endl;
    int input;
    cin >> input;
    system("cls");
    if (input == 1) {
        int ary[10][10], n, cost = 0;
        int ans = INT_MAX;
        cout << "Enter the number of houses: ";
        cin >> n;
        n++;
        bool completed[10];
        for (int i=0; i<n; i++) {
            completed[i] = false;
        }
        completed[0] = true;
        cout << endl << "Enter the Cost Matrix (all distances in km)" << endl;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i != j) {
                    if (i == 0)
                        cout << endl << "Enter distance of house " << j << " from delivery point (PAAM): ";
                    else if (j == 0)
                        cout << endl << "Enter distance of PAAM from house " << i << ": ";
                    else
                        cout << endl << "Enter distance of house " << j << " from house no " << i << ": ";
                    cin >> ary[i][j];
                }
                else {
                    ary[i][j] = 0;
                }
            }
        }

        cout << endl << endl << "The distance matrix is:";
        for (int i = 0; i < n; i++) {
            cout << endl;
            for (int j = 0; j < n; j++)
                cout << "\t" << ary[i][j];
        }
        cout << endl << endl;
        tsp(ary, completed, n, 0, 0, 1, ans);
        cout << endl << "Minimum distance = " << ans << " km";
    }

    else if (input == 2) {
        cout << "Super Delivery mode" << endl << endl;
        cout << "Enter number of orders: ";
        int size_profit;
        cin >> size_profit;
        int max_weight, profit[size_profit], weight[size_profit];
        printknapSack(max_weight, weight, profit, size_profit);
    }

    else if (input == 3) {
        int number;
        cout << "Enter number of orders: ";
        cin >> number;
        int penalties[number], deadlines[number];
        TaskScheduling(number, deadlines, penalties);
    }
    return 0;
}


