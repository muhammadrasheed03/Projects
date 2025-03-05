//Amazon Delivery / Traveling Salesman Problem

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <ctime>
#include <chrono>
using namespace std;

class Address {
private:
    double i, j; //coordinates of each address
    int date; //optional field
public:
    //constructor
    Address(double x, double y, int date=0): i(x), j(y), date(date) {} ;

    //manhattan distance (whole numbers only)
    double distance_man(Address a) {
        return abs(a.geti() - i) + abs(a.getj() - j);
    }

    //euclidian distance (straight line)
    double distance_euc(Address a) {
        double delx = abs(i - a.geti());
        double dely = abs(j - a.getj());
        return sqrt(pow(delx, 2) + pow(dely, 2));
    }

    //getters
    double geti() {
        return i;
    }
    double getj() {
        return j;
    }
    double getdate() {
        return date;
    }

    //check if two addresses are the same
    bool equals(const Address& other) {
        return (i == other.i && j == other.j);
    }
};


class AddressList {
protected:
    vector<Address> list = {}; //stores Address objects
public:
    //constructor
    AddressList(vector<Address> field) : list(field) {}; //passing in a vector of Addresses
    AddressList() {}; //default empty constructor

    //add a unique address
    void add_address(Address add) {
        for (int i = 0; i < list.size(); i++) {
            if (list[i].geti() == add.geti() && list[i].getj() == add.getj()) {
                return; //skips repeats of same coordinates
            }
        }
        list.push_back(add);
    }

    void add_address(Address add, int pos) {
        if (pos < 0 || pos > list.size()) throw std::out_of_range("Position is out of bounds.");
        list.insert(list.begin() + pos, add);
    }

    void remove_address(int k) {
        if (k < 0 || k >= list.size()) return;
        list.erase(list.begin() + k);
    }

    //returns the Address at a specific index in list
    Address get_address(int index) {
        if (index < 0 || index >= list.size()) { //check for bounds
            throw std::out_of_range("Index is out of bounds.");
        }
        return list[index];
    }

    //returns a reference to the list
    vector<Address>& get_list() { return list; }

    //returns the size of the list
    int num_of_address() {
        return list.size();
    }

    //calculates total length in the order the Addresses were added (no route finding)
    double length() {
        if (list.empty()) return 0;
        double totLength = 0;
        for (int i = 1; i < list.size(); i++) {
            totLength += list[i-1].distance_euc(list[i]); //distance from one to the next
        }
        return totLength;
    }

    //returns the Address with coordinates closest to the passed Address
    Address index_closest_to(Address address) {
        if (list.empty()) {
            throw runtime_error("Address list is empty.");
        }

        Address closestAddress = list[0];
        double minDistance = address.distance_euc(list[0]);

        for (Address& addr : list) { //find the min of distances to each address in the list
            double currentDistance = address.distance_euc(addr);
            if (currentDistance < minDistance) {
                minDistance = currentDistance;
                closestAddress = addr;
            }
        }
        return closestAddress;
    }

    //generates a greedy list of addresses based on proximity
    //used for greedy_route()
    vector<Address> greedy_list() {
        Address we_are_here = Address(0,0); //starting at origin/depot
        vector<Address> new_list = {};
        vector<Address> curr_list = list;

        while(!list.empty()) {
            we_are_here = index_closest_to(we_are_here);
            for (int i = 0; i < list.size(); ++i) {
                if (we_are_here.equals(list[i])) {
                    list.erase(list.begin() + i);
                    break;
                }
            }
            new_list.push_back(we_are_here);
        }

        list = curr_list; //restore list to original state
        return new_list; //addresses ordered by proximity to use for greedy_route
    }

    //generates a greedy route following the greedy list
    AddressList greedy_route() {
        auto new_list = greedy_list();
        return AddressList(new_list);
    }

    //converts the address list to a string representation in format (i, j)
    string as_string() {
        string s = "";
        for (int i = 0; i < list.size(); i++) {
            s += "(" + to_string(list[i].geti()) + "," + to_string(list[i].getj()) + ") ";
        }
        return s;
    }

    //converts the address list to a string representation in format i j (with line breaks)
    string as_string2() {
        string s = "";
        for (int i = 0; i < list.size(); i++) {
            s += to_string(list[i].geti()) + " " + to_string(list[i].getj()) + "\n";
        }
        return s;
    }
};

class Route : public AddressList { //extends the AddressList to factor in depots and the true route
public:
    double length() {
       double totLength = AddressList::length();
       //length from last node back to depot
       double new_length =  totLength + get_address(num_of_address() - 1).distance_euc(Address(0, 0));
       //length from depot to first node
       new_length += get_address(0).distance_euc(Address(0, 0));
       return new_length; //total length of traversing the route including traveling to/from the depot
   }

   //greedy route specific to the route class
    Route greedy_route() {
        return Route(greedy_list());
    }

    //returns a copy of the Route
    Route copy() { return Route(list); }

    //override both as_string functions to include the depot start/end
    string as_string() {
        string s = "(0, 0) ";
        s += AddressList::as_string();
        s += "(0, 0)";
        return s;
    }

    string as_string2() {
        string s = "0 0\n";
        s += AddressList::as_string2();
        s += "0 0";
    }
};

//optimizes a given route based on the 2-opt algorithm
void opt2(Route& route) {
    if (route.num_of_address() < 4) return;
    bool improvement = true;

    while (improvement) {
        improvement = false;

        for (size_t m1 = 1; m1 < route.num_of_address() - 2; m1++) {
            for (size_t n1 = m1 + 1; n1 < route.num_of_address() - 1; n1++) {
                double origDist = route.get_address(m1 - 1).distance_euc(route.get_address(m1)) +
                                  route.get_address(n1).distance_euc(route.get_address(n1 + 1));

                double newDist = route.get_address(m1 - 1).distance_euc(route.get_address(n1)) +
                                 route.get_address(m1).distance_euc(route.get_address(n1 + 1));

                if (newDist < origDist) {
                    reverse(route.get_list().begin() + m1, route.get_list().begin() + n1 + 1);
                    improvement = true;
                }
            }
        }
    }
}

//performs 2-opt on two routes, which act as two paths for two trucks working the same address list
void multipath_opt2(Route& r1, Route& r2) {
    opt2(r1);
    opt2(r2);
}

//performs 2-opt on two routes, but factors in optimization by transferring addresses between the routes
void multipath_opt2_switching(Route& r1, Route& r2) {
    bool improvement = true;
    int max_it = 1000;
    int it = 0;

    while (improvement && (it < max_it)) {
        improvement = false;
        multipath_opt2(r1, r2); // Optimize by reversing segments independently first
        double originalTotalLength = r1.length() + r2.length();

        Route prev_r1 = r1;
        Route prev_r2 = r2;
        
        // Switch addresses from r2 to r1
        for (int i = 1; i < r2.num_of_address() - 1; i++) {
            Address addr = r2.get_address(i);
            AddressList list2 = r2;
            list2.remove_address(i);

            for (int j = 1; j <= r1.num_of_address() - 1; j++) {
                AddressList list1 = r1;
                list1.add_address(addr, j);

                double newTotalLength = list1.length() + list2.length();
                if (newTotalLength < originalTotalLength) {
                    r1 = Route(list1.get_list());
                    r2 = Route(list2.get_list());
                    multipath_opt2(r1, r2);
                    improvement = true;
                    originalTotalLength = newTotalLength;
                    break;
                }
            }
            if (improvement) break;
        }

        // Switch addresses from r1 to r2
        for (int i = 1; i < r1.num_of_address() - 1; i++) {
            Address addr = r1.get_address(i);
            AddressList list1 = r1;
            list1.remove_address(i);

            for (int j = 1; j <= r2.num_of_address() - 1; j++) {
                AddressList list2 = r2;
                list2.add_address(addr, j);

                double newTotalLength = list1.length() + list2.length();
                if (newTotalLength < originalTotalLength) {
                    r1 = Route(list1.get_list());
                    r2 = Route(list2.get_list());
                    multipath_opt2(r1, r2);
                    improvement = true;
                    originalTotalLength = newTotalLength;
                    break;
                }
            }
            if (improvement) break;
        }

        // Break if no meaningful change in routes
        if (r1.as_string() == prev_r1.as_string() && r2.as_string() == prev_r2.as_string()) {
            break;
        }
        ++it;
    }
    multipath_opt2(r1, r2); //final reordering of segments for optimal performance
}


/*
 * Everything above this comment is part of the underlying structures and functions to create an optimal route
 * using different algorithms. The following is code to create an easy-to-use, interactive UI
 */

int input_type() {
    int ans = 0;
    cout << "Select a number for how you want your input:" << endl;
    cout << "(1) Random addresses" << endl;
    cout << "(2) Enter addresses by hand" << endl;
    cout << "(3) Input and read addresses from a file" << endl;
    cout << "(-1) Pre-generated admin addresses" << endl;
    cin >> ans;

    if (ans == -1) return -1;
    while (ans < 1 || ans > 3) {
        cout << "Incorrect input. Enter 1 for random addresses, 2 to input your own addresses, or 3 for admin addresses: ";
        cin >> ans;
    }
    return ans;
}

AddressList randomList() { //returns a list of randomly generated addresses
    int num;
    numRandom:
    cout << "How many random addresses do you want to generate? ";
    cin >> num;
    srand(static_cast<unsigned int>(time(0)));
    while (num <= 0) {
        cout << "Incorrect input. Please try again." << endl;
        goto numRandom; //jumps back to marker to ask again
    }

    //picks num addresses between 0 and 1
    AddressList a;
    for (int i = 0; i < num; ++i) {
        a.add_address(Address((double)rand() / (double)RAND_MAX, (double)rand() / (double)RAND_MAX));
    }
    cout << num << " random addresses have been added." << endl;
    return a;
}

AddressList userList() { //allows the user to input specific addresses
    cout << "You chose to enter your own addresses." << endl;
    AddressList a;
    while (true) {
        double x, y;
        cout << "X-coordinate of the address: "; cin >> x;
        cout << "Y-coordinate of the address: "; cin >> y;
        a.add_address(Address((double)x, (double)y));
        int choice;
        notValid:
        cout << "Do you want to:" << endl;
        cout << "(1) Enter another address" << endl;
        cout << "(2) Remove last address" << endl;
        cout << "(3) Exit" << endl;
        cin >> choice;
        if (choice < 1 || choice > 3) goto notValid;

        if (choice == 2) a.remove_address(a.num_of_address()-1);
        else if (choice == 3) break;
    }
    return a;
}

AddressList fileList() {
    AddressList a;

    string filename;
    cout << "Enter the file name (with extension) to load the addresses from: ";
    cin >> filename;

    ifstream file(filename);
    if (!file) {
        throw std::runtime_error("Error opening file.");
        return a;
    }

    double x, y;
    while (file >> x >> y) a.add_address(Address((double)x, (double)y));
    cout << "All addresses have been loaded." << endl;
    file.close();

    return a;
}

AddressList adminList() { //uses a preset list of addresses
    AddressList a;
    // Between 0-1
    /*
    a.add_address(Address(0.624408, 0.419675));
    a.add_address(Address(0.483786, 0.992894));
    a.add_address(Address(0.561247, 0.870578));
    a.add_address(Address(0.796820, 0.148507));
    a.add_address(Address(0.961681, 0.968222));
    a.add_address(Address(0.912917, 0.393072));
    a.add_address(Address(0.358372, 0.155930));
    a.add_address(Address(0.717286, 0.425558));
    a.add_address(Address(0.347336, 0.670337));
    a.add_address(Address(0.352194, 0.329899));
    a.add_address(Address(0.611439, 0.456755));
    a.add_address(Address(0.681565, 0.067957));
    a.add_address(Address(0.154753, 0.936122));
    a.add_address(Address(0.402950, 0.384277));
    a.add_address(Address(0.544600, 0.094101));
    */

    //Between 0-15

    a.add_address(Address(1, 2));
    a.add_address(Address(4, 0));
    a.add_address(Address(9, 8));
    a.add_address(Address(1, 2));
    a.add_address(Address(5, 5));
    a.add_address(Address(8, 9));
    a.add_address(Address(3, 3));
    a.add_address(Address(10, 10));
    a.add_address(Address(7, 6));
    a.add_address(Address(10, 10));
    a.add_address(Address(1, 4));
    a.add_address(Address(13, 9));
    a.add_address(Address(3, 5));
    a.add_address(Address(9, 11));
    a.add_address(Address(12, 12));
    a.add_address(Address(8, 13));
    a.add_address(Address(0, 1));
    a.add_address(Address(2, 3));
    a.add_address(Address(11, 9));

    return a;
}

int main() {
    int input = input_type(); //asks user how they want to get Addresses
    AddressList addrList; //the address list that route(s) will be made from

    switch(input) {
    case 1:
        addrList = randomList();
        break;
    case 2:
        addrList = userList();
        break;
    case 3:
        addrList = fileList();
        break;
    case -1:
        addrList = adminList();
        break;
    default:
        break;
    }

    //output route details
    Route r = Route(addrList);
    cout << "Your route, including start/end at the depot: " << r.as_string() << endl;
    cout << "Length of route in list order: " << addrList.length() << endl;
    cout << "Length of greedy route (proximity): " << addrList.greedy_route().length() << endl;

    cout << "Length of 2-opt algorithm route (1 path): ";
    Route r2opt = r; opt2(r2opt); //makes a copy and modifies that
    cout << r2opt.length() << endl;

    cout << "Length of 2-opt algorithm route (2 path, no switching):" << endl;
    Route r1, r2; //each will store half of Route r
    for (int i = 0; i < r.num_of_address(); ++i) {
        if (i >= r.num_of_address() / 2) {
            r2.add_address(r.get_address(i));
        } else {
            r1.add_address(r.get_address(i));
        }
    }
    multipath_opt2(r1, r2);
    cout << "\tPath 1 - " << r1.length() << endl;
    cout << "\tPath 2 - " << r2.length() << endl;
    cout << "\tTotal - " << r1.length() + r2.length() << endl;
    //cout << "Route 1: " << r1.as_string() << endl;
    //cout << "Route 2: " << r2.as_string() << endl;

    cout << "Length of 2-opt algorithm route (2 path, with switching):" << endl;
    Route r1_swap, r2_swap; //each will store half of Route r
    for (int i = 0; i < r.num_of_address(); ++i) {
        if (i >= r.num_of_address() / 2) {
            r2_swap.add_address(r.get_address(i));
        } else {
            r1_swap.add_address(r.get_address(i));
        }
    }
    multipath_opt2_switching(r1_swap, r2_swap);
    cout << "\tPath 1 - " << r1_swap.length() << endl;
    cout << "\tPath 2 - " << r2_swap.length() << endl;
    cout << "\tTotal - " << r1_swap.length() + r2_swap.length() << endl;
    //cout << "Route 1: " << r1_swap.as_string() << endl;
    //cout << "Route 2: " << r2_swap.as_string() << endl;

    return 0;
}
