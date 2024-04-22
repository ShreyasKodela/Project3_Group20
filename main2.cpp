#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

unordered_map<std::string, int> colMap = {
        {"Cholesterol", 3}, {"Protein", 4},  {"Magnesium", 5}, {"Potassium", 6},
        {"Sodium", 7},      {"Zinc", 8},     {"VitaminA", 9},  {"VitaminB12", 10},
        {"VitaminC", 11},   {"VitaminE", 12}};

int getColIndex(const string &colName,
                const unordered_map<std::string, int> &colMap) {
    // Look up the column name in the map
    auto it = colMap.find(colName);
    if (it == colMap.end()) {
        return -1; // Not found
    }
    return it->second; // Return the corresponding index
}

vector<pair<string, double>> readFile(string interest) {
    ifstream inputFile;
    inputFile.open("../food3.csv");
    vector<pair<string, double>> foodList;
    string line = "";
    getline(inputFile, line);
    line = "";
    while (getline(inputFile, line)) {

        stringstream inputString(line);

        // StudentId, Last Name, FirstName, Age, Phone Number, GPA
        string food_Category;
        string food_Description;
        string col_of_interest;
        int c = getColIndex(interest, colMap);

        for (int i = 0; i < 2; i++) {
            getline(inputString, food_Description, ',');
        }
        for (int i = 2; i < c; i++) {
            getline(inputString, col_of_interest, ',');
        }

        double val = stod(col_of_interest);
        foodList.emplace_back(food_Description, val);

        line = "";
    }
    return foodList;
}



void merge(std::vector<std::pair<string, double>>& data, int low, int mid, int high) {
    // Create temporary vectors to hold left and right halves
    int leftSize = mid - low + 1;
    int rightSize = high - mid;
    std::vector<std::pair<string, int>> left(leftSize);
    std::vector<std::pair<string, int>> right(rightSize);

    // Copy data to temporary vectors
    for (int i = 0; i < leftSize; i++) {
        left[i] = data[low + i];
    }
    for (int j = 0; j < rightSize; j++) {
        right[j] = data[mid + 1 + j];
    }

    // Merge the temporary vectors back into data
    int i = 0, j = 0, k = low;
    while (i < leftSize && j < rightSize) {
        if (left[i].second <= right[j].second) {
            data[k] = left[i];
            i++;
        } else {
            data[k] = right[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements (if any)
    while (i < leftSize) {
        data[k] = left[i];
        i++;
        k++;
    }
    while (j < rightSize) {
        data[k] = right[j];
        j++;
        k++;
    }
}

void mergeSort(std::vector<std::pair<string, double>>& data, int low, int high) {
    if (low < high) {
        // Find the middle point of the vector
        int mid = low + (high - low) / 2;

        // Sort the first and second halves recursively
        mergeSort(data, low, mid);
        mergeSort(data, mid + 1, high);

        // Merge the sorted halves
        merge(data, low, mid, high);
    }
}

int partition(std::vector<std::pair<string, double>>& data, int low, int high) {
    // Choose a pivot element (last element in this case)
    std::pair<string, int> pivot = data[high];

    // Index of smaller element
    int i = (low - 1);

    // Partitioning loop
    for (int j = low; j <= high - 1; j++) {
        // Check if current element is smaller than the pivot
        if (data[j].second <= pivot.second) {
            i++; // increment index of smaller element
            std::swap(data[i], data[j]); // swap current element with smaller element
        }
    }

    // Place the pivot element in its correct position
    std::swap(data[i + 1], data[high]);
    return (i + 1);
}

void quickSort(std::vector<std::pair<string, double>>& data, int low, int high) {
    if (low < high) {
        // pi is partitioning index, data[p] is now at right place
        int pi = partition(data, low, high);

        // Recursively sort elements before and after partition
        quickSort(data, low, pi - 1);
        quickSort(data, pi + 1, high);
    }
}

int main() {
    cout << "Available columns:" << endl;
    cout << "Cholesterol" << endl;
    cout << "Protein" << endl;
    cout << "Magnesium" << endl;
    cout << "Potassium" << endl;
    cout << "Sodium" << endl;
    cout << "Zinc" << endl;
    cout << "VitaminA" << endl;
    cout << "VitaminB12" << endl;
    cout << "VitaminC" << endl;
    cout << "VitaminE" << endl;

    // Prompt user for column of interest
    string interest;
    cout << "Enter the column you're interested in: ";
    getline(cin, interest);
    vector<pair<string, double>> foodList = readFile(interest);
    //cout << foodList[12].first; to check and see if the map function works
    //mergeSort(foodList, 0, 7413);
    quickSort(foodList, 0, 7413);
    cout << foodList[7413].first << " " << foodList[7413].second;
}
