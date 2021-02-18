/* Shopping
 * Name: Lari Lantonen
 * Student number: 283531
 * UserID: lantonen
 * E-Mail: lari.lantonen@tuni.fi
 *
 * Notes about the program and it's implementation:
 * Basic idea is to help with datamanagement in store location and products data.
 * Has different kind of commands for finding information user wants.
 * Commands: chains, stores, selection, cheapest, products, quit.
 * */

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <iomanip>

using namespace std;

const double OUT_OF_STOCK = -1;
// Pricing structure for products, contains name and price
struct Pricing {
    string name;
    double price;
};

/* Info: Checks if searched product is found from data, if price is lowered changes it
 * Parameters: Data structure, product price, product name and price, store name and its location
 * Return: bool, true if product is found, false if product is not in searched data
 */
bool check(map <string, map <string, vector<Pricing>>>& data,
           double price, string productName, string storeName, string location){
    for(auto& structName : data.at(storeName).at(location)){
        //product is already added
        if(structName.name == productName){
            structName.price = price;
            return true;
        }
    }
    return false;
}


/* Info: Split function for input data and for users command
 * Parameters: given line, delimiter, bool for ignoring emptyt spaces
 * Return: vector with line splitted
 */
vector<string> split(const string& s, const char delimiter, bool ignore_empty = false){
    vector<string> result;
    string tmp = s;

    while(tmp.find(delimiter) != string::npos)
    {
        string new_part = tmp.substr(0, tmp.find(delimiter));
        tmp = tmp.substr(tmp.find(delimiter)+1, tmp.size());
        if(not (ignore_empty and new_part.empty()))
        {
            result.push_back(new_part);
        }
    }
    if(not (ignore_empty and tmp.empty()))
    {
        result.push_back(tmp);
    }
    return result;
}

/* Info: Fucntion that mainly builds the correct datastructure
 * Parameters: Data structure that will be modifyed, information vector is
 *      splitted line that contains information from given inputfile
 * Return: bool, true if input data read complited, false if something failed
 */
bool buildData(map <string, map <string, vector<Pricing>>>& data,
               vector<string> informationVector, vector<string>& allProducts){
    string storeName, location, productName;
    double price;
    map <string, vector<Pricing>> innerMap;
    vector<Pricing> productVector;

    // input lines are splitted into 4 parts
    if (informationVector.size() == 4){
        storeName = informationVector.at(0);
        location = informationVector.at(1);
        productName = informationVector.at(2);

        // if product is not added to vector allProducts it will be added
        if(find(allProducts.begin(),allProducts.end(),productName) == allProducts.end()){
            allProducts.push_back(productName);
        }
        // out of stock products
        if (informationVector.at(3) == "out-of-stock"){
            price = OUT_OF_STOCK;
        }
        else{
            price = stod(informationVector.at(3));
        }

        //using struct
        Pricing product = {productName, price};
        productVector.push_back(product);
        innerMap.insert({location, productVector});

        // chain is found
        if (data.find(storeName) != data.end()){
            //chain store location is found
            if(data.at(storeName).find(location) != data.at(storeName).end()){
                //if check is false that means product wasnt found so not check means product is found
                if(not check(data, price, productName, storeName, location)){
                    data.at(storeName).at(location).push_back(product);
                }
            }
            // chain found, but store location isnt found
            else{
                data.at(storeName).insert({location, productVector});
            }
        }
        //chain is not found
        else{
            data.insert({storeName, innerMap});
        }
        return true;
    }
    else{
        cout << "Error: the input file has an erroneous line" << endl;
        return false;
    }
}

/* Info: Reads the file and uses buildData() to build correct datastructure with one line at a time
 * Parameters: datastructure
 * Return: bool, true if input data read complited, false if something failed
 */
bool inputFunction(map <string, map <string, vector<Pricing>>>& data, vector<string>& allProducts ){
    vector<string> informationVector;
    string inputFileName = "";
    cout << "Input file: ";
    getline(cin, inputFileName);
    ifstream inputFile (inputFileName);

    if ( not inputFile ) {
        cout << "Error: the input file cannot be opened" << endl;
        return false;
    }
    else {
        string row;
        while ( getline(inputFile, row) ) {
            informationVector = split(row, ';', true);

            bool boolean = buildData(data, informationVector, allProducts);

            if(not boolean){
                return boolean;
            }
        }
    inputFile.close();
    }
    return true;
}

/* Info: find function that finds cheapest price or stores with cheapest price product
 * Parameters: data structure, command vector, lowest price, findStores that defines finding target
 * Return: bool, true if out of stock, false if product found with price
 */
bool find(map <string, map <string, vector<Pricing>>>& data, vector<string> partsVector,
          double& lowestPrice, bool findStores = false){
    bool isOutOfStock = true;
    bool productIsInSomeStore = false;

    for(auto storePair : data){
        for(auto locationPair : storePair.second){
            for(auto productStruct : locationPair.second){
                // if wanted product is same as ongoing product name and finding cheapest price
                if (partsVector.at(1) == productStruct.name and
                        productStruct.price >= 0 and findStores == false){
                    // updating lowest price
                    if(productStruct.price < lowestPrice) {
                        lowestPrice = productStruct.price;
                        isOutOfStock = false;
                        productIsInSomeStore = true;
                    }
                }
                // if store has product with lowest price
                else if(partsVector.at(1) == productStruct.name and
                        productStruct.price == lowestPrice and findStores == true){
                    cout << storePair.first << " " << locationPair.first <<endl;
                }
                // out of stock products
                else if(partsVector.at(1) == productStruct.name){
                    productIsInSomeStore = true;
                }
            }
        }
    }

    //if product isnt in store selection
    if (not productIsInSomeStore and findStores == false){
        cout << "The product is not part of product selection" << endl;
        return false;
    }
    return isOutOfStock;
}

/* Info: Make double 2 decimal number
 * Parameters: num, decimal number
 * Return: string with 2 decimals
 */
string numberStringTo2Decimals(double num){
    // Set precision to 2 digits
    ostringstream streamObj;
    streamObj << setprecision(2);

    ostringstream streamObj2;
    streamObj2 << fixed;
    streamObj2 << setprecision(2);
    streamObj2 << num;
    string strObj = streamObj2.str();
    return strObj;
}

/* Info: Finds store and prints it if bool value is true
 * Parameters: data structure, partsVector that contains given command, bool that determines is store printed
 * Return: bool true or false depending is store found from data
 */
bool findStore(map <string, map <string, vector<Pricing>>>& data,
               vector<string> partsVector, bool printOrNot = true){
    bool isFound = false;
    for(auto storePair : data){
        if (partsVector.at(1) == storePair.first){
            for(auto locationPair : data.at(partsVector.at(1))){
                if(printOrNot == true){
                    cout << locationPair.first <<endl;
                }
                isFound = true;
            }
        }
    }
    return isFound;
}

/* Info: If conditions for chains command, starts doing the command
 * Parameters: data structure, partsVector that contains given command
 */
void doChains(map <string, map <string, vector<Pricing>>>& data, vector<string>& partsVector){
    if (partsVector.size() == 1){
        for(auto storePair : data){
            cout << storePair.first <<endl;
        }
    }
    else{
        cout << "Error: error in command chains" <<endl;
    }
}

/* Info: If conditions for stores command, starts doing the command
 * Parameters: data structure, partsVector that contains given command
 */
void doStores(map <string, map <string, vector<Pricing>>>& data, vector<string>& partsVector){
    //if chain name is found
    if(partsVector.size() == 2){
        if(not findStore(data, partsVector)){
            cout << "Error: unknown chain name" <<endl;
        }
    }
    else{
        cout << "Error: error in command stores" <<endl;
    }
}

/* Info: If conditions for selection command, starts doing the command
 * Parameters: data structure, partsVector that contains given command
 */
void doSelection(map <string, map <string, vector<Pricing>>>& data, vector<string>& partsVector){
    if(partsVector.size() == 3){
        //chain name not found
        if(not findStore(data, partsVector, false)){
            cout << "Error: unknown chain name" <<endl;
        }
        // store location not found
        else if(data.at(partsVector.at(1)).find(partsVector.at(2))
                == data.at(partsVector.at(1)).end()){
            cout << "Error: unknown store" <<endl;
        }
        else{
            vector<string> tempVector = {};
            for(auto productStruct : data.at(partsVector.at(1)).at(partsVector.at(2))){
                if(productStruct.price < 0){
                    tempVector.push_back(productStruct.name + " out of stock");
                }
                else{
                    tempVector.push_back(productStruct.name + " "
                                         + numberStringTo2Decimals( productStruct.price));
                }
            }
            for(unsigned int i = 0; i < tempVector.size(); ++i){
                sort(tempVector.begin(),tempVector.end());
                cout << tempVector.at(i) <<endl;
            }
        }

    }
    else{
        cout << "Error: error in command selection" <<endl;
    }
}

/* Info: If conditions for cheapest command, starts doing the command
 * Parameters: data structure, partsVector that contains given command
 */
void doCheapest(map <string, map <string, vector<Pricing>>>& data, vector<string>& partsVector){
    if(partsVector.size() == 2){
        double lowestPrice = 1000000;
        // if product is out of stock
        if (find(data, partsVector, lowestPrice)){
            cout << "The product is temporarily out of stock everywhere" << endl;
        }
        else if(lowestPrice != 1000000){
            cout << numberStringTo2Decimals(lowestPrice)  << " euros" << endl;
            find(data, partsVector, lowestPrice, true);
        }
    }
    else{
        cout << "Error: error in command cheapest" << endl;
    }
}

/* Info: If conditions for products command, starts doing the command
 * Parameters: all products that stores has, partsVector that contains given command
 */
void doProducts(vector<string>& allProducts, vector<string>& partsVector){
    if(partsVector.size() == 1){
        for(auto name : allProducts){
            cout << name <<endl;
        }
    }
    else{
        cout << "Error: error in command products" << endl;
    }
}

int main()
{
    map <string, map <string, vector<Pricing>>> data;
    vector<string> allProducts;


    if (not inputFunction(data, allProducts)){
        return EXIT_FAILURE;
    }
    // no errors, everything ok
    else{
        sort(allProducts.begin(), allProducts.end());
        while(true){
            string line;
            cout << "> ";
            getline(cin, line);

            vector<string> partsVector = split(line, ' ', true);
            string command = partsVector.at(0);

            //QUIT
            if(command == "quit"){
                return EXIT_SUCCESS;
            }
            // CHAINS
            else if(command == "chains"){
                doChains(data, partsVector);
            }
            // STORES STORENAME
            else if(command == "stores"){
                doStores(data, partsVector);
            }
            //SELECTION STORENAME LOCATION
            else if(command == "selection"){
                doSelection(data, partsVector);
            }
            //CHEAPEST PRODUCTNAME
            else if(command == "cheapest"){
                doCheapest(data, partsVector);
            }
            //PRODUCTS
            else if(command == "products"){
                doProducts(allProducts, partsVector);
            }
            else {
                cout << "Error: unknown command: " << command <<endl;
            }
        }
    }
}
