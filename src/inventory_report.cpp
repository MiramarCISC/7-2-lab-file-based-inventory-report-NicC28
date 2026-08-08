#include "inventory_report.hpp"
#include <fstream>
#include <iomanip>
#include <iostream>

using namespace std;

bool isValidQuantity(int quantity) {
    // TODO: Return true when quantity is 0 or greater.
    if (quantity >= 0)
    {
        return true;
    }
    else
    {
        return false;
    }
    
}

bool isValidPrice(double price) {
    // TODO: Return true when price is 0 or greater.
    if (price >= 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

double calculateItemValue(const InventoryItem& item) {
    // TODO: Return quantity multiplied by price.
    // If quantity or price is invalid, return 0.0.
    if (isValidQuantity(item.quantity) && isValidPrice(item.price))
    {
        return (item.quantity*item.price);
    }
    else
    {
        return 0.0;
    }
    
}

int readInventoryFile(string filename, InventoryItem items[], int maxItems) {
    // TODO:
    // Open the input file.
    // Read records in this format: sku name quantity price
    // Store valid records in the items array.
    // Stop when the file ends or maxItems is reached.
    // Return the number of records stored.
    if(items == nullptr)
    {
        return 0;
    }
    ifstream inFile(filename);
     if (!inFile.is_open())
    {
        return 0;
    }
    string sku;
    string name;
    int quantity;
    double price;
    int stored = 0;
    for (int i = 0; i < maxItems; i++)
    {
        inFile >> sku >> name >> quantity >> price;

        if (inFile.fail())
        {
            break;
        }

        items[i].sku = sku;
        items[i].name = name;
        items[i].quantity = quantity;
        items[i].price = price;

        stored++;
    }
    inFile.close();
    return stored;
}

bool writeInventoryReport(string filename, const InventoryItem items[], int count) {
    // TODO:
    // Open the output file.
    // Write each item and its total value.
    // Write the total inventory value.
    // Return true if the report was written successfully.
    if(items == nullptr)
    {
        return false;
    }
    ofstream outFile(filename);
    if (!outFile.is_open())
    {
        return false;
    }
    double total = 0.0;
    for (int i = 0; i < count; i++)
    {
        double value = calculateItemValue(items[i]);
        total += value;
        outFile << items[i].sku << " "
                << items[i].name << " "
                << items[i].quantity << " "
                << items[i].price << " "
                << value << "\n";
    }

    outFile << "Total inventory value: " << total << "\n";

    outFile.close();

    return true;
}

double calculateTotalInventoryValue(const InventoryItem items[], int count) {
    // TODO:
    // Return the sum of all item values.
    // Return 0.0 for null arrays or invalid counts.
    double sum = 0.0;
    if(items == nullptr)
    {
        return 0.0;
    }
    for (int i = 0; i < count; i++)
    {
        double value = calculateItemValue(items[i]);
        sum += value;
        
    }

    return sum;
}

int findItemBySku(const InventoryItem items[], int count, string sku) {
    // TODO:
    // Search for a matching SKU.
    // Return the index if found.
    // Return -1 if not found.
    if(items == nullptr)
    {
        return -1;
    }
    for (int i = 0; i < count; i++)
    {
      if(items[i].sku == sku)
        {
            return i;
        }
    }
    return -1;
}

int findHighestValueItemIndex(const InventoryItem items[], int count) {
    // TODO:
    // Return the index of the item with the highest item value.
    // Return -1 for null arrays or invalid counts.
    double greatest = -1.0;
    int dex = -1;
    if(items == nullptr)
    {
        return dex;
    }
    for (int i = 0; i < count; i++)
    {
      if(calculateItemValue(items[i]) > greatest)
        {
            greatest = calculateItemValue(items[i]);
            dex = i;
        }

    }
    return dex;
}
