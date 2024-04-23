#include <chrono>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;
using namespace std::chrono;

unordered_map<std::string, int> colMap = {
        {"Cholesterol", 3},    {"Protein", 4},        {"Magnesium", 5},
        {"Potassium", 6},      {"Sodium", 7},         {"Zinc", 8},
        {"Iron", 9},           {"Carbs", 10},         {"VitaminA", 11},
        {"VitaminB12", 12},    {"VitaminE", 13},      {"VitaminK", 14},
        {"Monosaturated", 15}, {"Polysaturated", 16}, {"Saturated", 17}};

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
    inputFile.open("../food.csv");
    vector<pair<string, double>> foodList;
    string line = "";
    getline(inputFile, line);
    line = "";
    while (getline(inputFile, line)) {

        stringstream inputString(line);

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

void merge(vector<pair<string, double>> &data, int low, int mid, int high) {
    // Create temporary vectors to hold left and right halves
    int leftSize = mid - low + 1;
    int rightSize = high - mid;
    vector<pair<string, double>> left(leftSize);
    vector<pair<string, double>> right(rightSize);

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

void mergeSort(vector<pair<string, double>> &data, int low, int high) {
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

int partition(vector<std::pair<string, double>> &data, int low, int high) {
    // Choose a pivot element (last element in this case)
    pair<string, int> pivot = data[high];

    // Index of smaller element
    int i = (low - 1);

    // Partitioning loop
    for (int j = low; j <= high - 1; j++) {
        // Check if current element is smaller than the pivot
        if (data[j].second <= pivot.second) {
            i++;                    // increment index of smaller element
            swap(data[i], data[j]); // swap current element with smaller element
        }
    }

    // Place the pivot element in its correct position
    swap(data[i + 1], data[high]);
    return (i + 1);
}

void quickSort(vector<pair<string, double>> &data, int low, int high) {
    if (low < high) {
        // pi is partitioning index, data[p] is now at right place
        int pi = partition(data, low, high);

        // Recursively sort elements before and after partition
        quickSort(data, low, pi - 1);
        quickSort(data, pi + 1, high);
    }
}

void printLargestItems(vector<pair<string, double>> &foodList, int order,
                       int amount, string measurement) {
    int listSize = 7413;
    int startIndex = listSize - amount + 1;

    // Print based on the order parameter
    string orderStr = (order == 1)   ? "Ascending"
                                     : (order == 2) ? "Descending"
                                                    : "Unsorted";
    cout << "Printing Items (" << orderStr << "):" << std::endl;

    if (order == 1) {
        // Ascending order (starting from startIndex and going up)
        for (int i = startIndex; i <= listSize; i++) {
            cout << listSize - i + 1 << ": " << foodList[i].first << ": "
                 << foodList[i].second << measurement << std::endl;
        }
    } else {
        // Descending order (starting from the end and going down)
        for (int i = listSize; i >= startIndex; i--) {
            cout << listSize - i + 1 << ": " << foodList[i].first << ": "
                 << foodList[i].second << measurement << std::endl;
        }
    }
}

int main() {
    int choiceNutrition, choiceSort, choiceRedo, choiceOrder, choiceNumber;
    string measurement;
    bool cycle = true;
    string nutritionTypes[] = {
            "Cholesterol", "Protein",  "Magnesium",     "Potassium",     "Sodium",
            "Zinc",        "Iron",     "Carbs",         "VitaminA",      "VitaminB12",
            "VitaminE",    "VitaminK", "Monosaturated", "Polysaturated", "Saturated"};

    while (cycle) {
        while (true) {
            cout << "Please enter the nutrition to be sorted by:\n"
                 << "1. Cholesterol (mg)" << endl
                 << "2. Protein (g)" << endl
                 << "3. Magnesium (mg)" << endl
                 << "4. Potassium (g)" << endl
                 << "5. Sodium (mg)" << endl
                 << "6. Zinc (mg)" << endl
                 << "7. Iron (mg)" << endl
                 << "8. Carbohydrate (g)" << endl
                 << "9. VitaminA (mcg)" << endl
                 << "10. VitaminB12 (mcg)" << endl
                 << "11. VitaminE (mg)" << endl
                 << "12. VitaminK (mcg)" << endl
                 << "13. Monosaturated Fat (g)" << endl
                 << "14. Polysaturated Fat (g)" << endl
                 << "15. Saturated Fat (g)" << endl;
            cin >> choiceNutrition;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Please enter a valid input" << endl;
            } else if (choiceNutrition < 1 || choiceNutrition > 15) {
                cout << "Please enter a valid option" << endl;
            } else {
                if (choiceNutrition == 2 || choiceNutrition == 4 ||
                    choiceNutrition == 8 || choiceNutrition == 13 ||
                    choiceNutrition == 14 || choiceNutrition == 15) {
                    measurement = "g";
                } else if (choiceNutrition == 9 || choiceNutrition == 10 ||
                           choiceNutrition == 12) {
                    measurement = "mcg";
                } else {
                    measurement = "mg";
                }
                break;
            }
        }
        while (true) {
            cout << "Please enter a sorting algorithm:" << endl
                 << "1. Merge Sort" << endl
                 << "2. Quick Sort" << endl
                 << "3. Unsorted" << endl;
            cin >> choiceSort;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Please enter a valid input" << endl;
            } else if (choiceSort == 1 || choiceSort == 2 || choiceSort == 3) {
                break;
            } else {
                cout << "Please enter a valid option" << endl;
            }
        }

        while (choiceSort != 3) {
            cout << "Please enter the desired order:" << endl
                 << "1. Ascending" << endl
                 << "2. Descending" << endl;
            cin >> choiceOrder;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Please enter a valid input" << endl;
            } else if (choiceOrder == 1 || choiceOrder == 2) {
                break;
            } else {
                cout << "Please enter a valid option" << endl;
            }
        }

        while (true) {
            cout << "Please enter the amount to be sorted. Max: 7413" << endl;
            cin >> choiceNumber;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Please enter a valid input" << endl;
            } else if (choiceNumber <= 0 || choiceNumber > 7413) {
                cout << "Please enter a number between 1 - 7413" << endl;
            } else {
                break;
            }
        }

        if (choiceSort == 1) {
            vector<pair<string, double>> foodList =
                    readFile(nutritionTypes[choiceNutrition - 1]);
            auto start = high_resolution_clock::now();
            mergeSort(foodList, 0, 7413);
            printLargestItems(foodList, choiceOrder, choiceNumber, measurement);
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stop - start);
            cout << "The merge sort algorithm took " << duration.count()
                 << " microseconds." << endl
                 << endl;
        } else if (choiceSort == 2) {
            vector<pair<string, double>> foodList =
                    readFile(nutritionTypes[choiceNutrition - 1]);
            auto start = high_resolution_clock::now();
            quickSort(foodList, 0, 7413);
            printLargestItems(foodList, choiceOrder, choiceNumber, measurement);
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stop - start);
            cout << "The quick sort algorithm took " << duration.count()
                 << " microseconds." << endl
                 << endl;
        } else if (choiceSort == 3) {
            vector<pair<string, double>> foodList =
                    readFile(nutritionTypes[choiceNutrition - 1]);
            printLargestItems(foodList, choiceOrder, choiceNumber, measurement);
        }

        cout << "Would you like to sort another nutrition?" << endl
             << "1. Yes" << endl
             << "2. No" << endl;
        cin >> choiceRedo;

        if (choiceRedo == 1) {
            cycle = true;
        } else {
            cout << "Thank you!" << endl;
            cycle = false;
        }
    }
    return 0;
}
