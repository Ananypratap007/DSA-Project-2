// Spring 2023
// Data Structures
// Project 2

#include <iostream>
#include <string>
#include <fstream> // for reading fileInput

using namespace std;


class RecordNotFoundException {
private:
    string message;

public:
    RecordNotFoundException(const string& message) : message(message) {}

    const string& getMessage() const {
        return message;
    }
};

class WrongDataTypeException {
    private:
    string message;
public:
    WrongDataTypeException(const string& message) : message(message) {}
    const string& wrongColumn() const {
        return message;
    }

};

class tableClass {
protected:
    string** myTable; // 2D string array to store all values (strings and numbers)
    string* DTarray; // 1D array to store the data types of each column
    int noRows, noCols; // number of rows and columns
public:
    //Constructors
    
    tableClass() {
    noRows = 0;
    noCols = 0;
    myTable = nullptr;
    DTarray = new string[noCols];
    }

    tableClass(int rows, int cols) {
        noRows = rows;
        noCols = cols;

        myTable = new string*[noRows];
        for (int i = 0; i < noRows; ++i) {
             myTable[i] = new string[noCols];
            for (int j = 0; j < noCols; ++j) {
                myTable[i][j] = "";
            }
        }

             DTarray = new string[noCols];
    }
    //setter for DTarray
  void setData(string* arr) {
        
         for (int j = 0; j < noCols; j++) {
            DTarray[j] = arr[j];
        }
    }

 
    // Overload the [] operator to access a row in myTable
    string* operator[](int i) { 
        return myTable[i]; }

    //File reading Method
    void readCSV(string filename){
        ifstream infile(filename);

        // Check if file is open
        if (!infile.is_open()) {
            cout << "Error opening file " << filename << endl;
            return;
        }
    
        // Read each line of the file and store it in the 2D array
        string line;
        int row = 0;
        while (getline(infile, line)) {
            // Split the line into fields using comma delimiter
            size_t pos = 0;
            string field;
            int col = 0;
            while ((pos = line.find(",")) != string::npos) {
                field = line.substr(0, pos);
                myTable[row][col] = field;
                ++col;
                line.erase(0, pos + 1);
            }
            myTable[row][col] = line; // last field in the row
            ++row;
        }

        // Close the file
        infile.close();
    }
    


    //Output Method
    void  display() {

         for (int j = 0; j < noCols; j++) {
            cout<< DTarray[j] << "\t" ;
        }
        cout<< endl;
        for (int i = 0; i < noRows; i++) {
            for (int j = 0; j < noCols; j++) {
              cout << myTable[i][j] << "\t";
            }
         cout << endl;
        }
    }


    //Sort the table
    void sortTable(){
        int comp = 0;

       for (int i = 0; i < noRows - 1; i++) {
        
             for (int j = 0; j < noRows - i - 1; j++) {
            // Compare the values in the first column
                comp = myTable[j][0].compare(myTable[j+1][0]);
                 if (comp > 0) {
                     // Swap the rows
                     string* temp = myTable[j];
                     myTable[j] = myTable[j+1];
                     myTable[j+1] = temp;
                }
            }
       }
    }





    //Search record

    string searchRecord(string str){ // str will be from the first column
     // FOR FIRST COL str is in the first column
       
        string a;
        for (int i = 0; i < noRows; i++) {
            int comp = str.compare(myTable[i][0]);
            if (comp ==0) {
                   for (int j = 0; j < noCols; j++) {
                            a  += myTable[i][j] + " ";
                        }
             
               return a;
                     
            }
        }
        throw RecordNotFoundException("Record not Found");
    }

     
    //Search value from table
    void searchValue(string str){
        cout<< "Searching for " << str << endl;

        int check = 0;
        for (int i = 0; i < noRows; i++) {
            for (int j = 0; j < noCols; j++) {
                if (myTable[i][j] == str) {
                    cout << "Found in (" << i << ", " << j << ")" << endl;
                    check++;
                }
            }
        }
        if(check > 0) {
            return;
        }
        else{
       cout<< "Value not found" << endl;
        }
        return;
    }
         

    //Getters

    int getNumberRows(){
        return noRows;
    } // returns the number of rows

    int getNumberCols(){
        return noCols;
    } // returns the number of columns


    //Find the minimum value for a given column
    double findMin(int colNumber){
        double minValue = 100000;
       // minValue = stod(myTable[0][colNumber]);

       if(DTarray[colNumber] == "int"){
        //1st creat an array to store the integers
        int* arrayInt = new int[noRows];

        //2nd convert strings to integers while storing then in arrayInt
            for (int i = 0; i < noRows; i++) {
                arrayInt[i] = std::stoi(myTable[i][colNumber]);
            }

        //3rd search for the minimum number 
            for (int i = 0; i < noRows; i++) {
                if (arrayInt[i] < minValue) {
                minValue = arrayInt[i];
                }
            }
            return minValue;
       }

       //For Floating Types
       else if(DTarray[colNumber] == "float"){
        //1st creat an array to store the floating numbers
            float* arrayFloating = new float[noRows];

        //2nd convert strings to floating while storing them in arrayfloating
            for (int i = 0; i < noRows; i++) {
                arrayFloating[i] = std::stof(myTable[i][colNumber]);
            }

        //3rd search for the minimum number 
            for (int i = 1; i < noRows; i++) {
                if (arrayFloating[i] < minValue) {
                minValue = arrayFloating[i];
                }
            }
            return minValue;
       }

        throw WrongDataTypeException("This column is not of a numeric data type");
    } // returns the min of the given column



    tableClass* getColumns(int colLeft, int colRight){// returns a tableClass with a set of columns from colLeft to colRight indices
        // Assumes colLeft and colRight are valid indices
       
        int width = colRight - colLeft;
          int offset = colLeft;
        tableClass* newTable = new tableClass(noRows, width);
     
     
        for (int i = 0; i < noRows; i++) {
            for (int j = 0; j < width; j++) {
                newTable->myTable[i][j] = myTable[i][j+offset];
            }
        }  
        for (int j = 0; j < width; j++) {
            newTable->DTarray[j] = DTarray[j + offset];
        }

        return newTable;
    }


    tableClass* getRows(int rowTop, int rowBottom){ // returns a tableClass with a set of rows from rowTop to rowBottom indices
      // Assumes rowTop and rowBottom are valid indices

    int height = rowBottom - rowTop;//2
    int offset = rowTop;//3
    tableClass* newTable = new tableClass(height, noCols);

        for (int i = 0; i < height; i++) {
            for (int j = 0; j < noCols; j++) {
                newTable->myTable[i][j] = myTable[i + offset][j];
            }
        }   
        for (int j = 0; j < noCols; j++) {
            newTable->DTarray[j] = DTarray[j];
        }

        return newTable;
        // delete newTable;
    }

    tableClass* getRowsCols(int colLeft, int colRight, int rowTop, int rowBottom){// returns a tableClass with the data between the cols and rows given
       // Assumes colLeft, colRight, rowTop, and rowBottom are valid indices
        int width = colRight-colLeft; 
        int height = rowBottom - rowTop; 
        int offsetR = rowTop;
        int offsetC = colLeft; 
        tableClass* newTable = new tableClass(height, width);
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                newTable->myTable[i][j] = myTable[i+offsetR][j+ offsetC];
            }
        }
           
        for (int j = 0; j < width; j++) {
            newTable->DTarray[j] = DTarray[j];
        }
        return newTable;

    }
    //Destructor

    ~tableClass(){
        for (int i = 0; i < noRows; ++i) {
            delete[] myTable[i];
        }
           delete[] myTable;
    }
    
};


int main()
{
	int numRows;
    int numCols;
	string fileName;
	char option;


   cin >> numRows >> numCols >> fileName;
	cout << "NumRows: " << numRows << endl;
	cout << "NumCols: " << numCols << endl;
	cout << "FileName: " << fileName << endl;

       string* DTtype = new string[numCols];
        for (int i = 0; i < numCols; ++i) {
                 cin >> DTtype[i];
        }
   
        

    // Create a new tableClass object
    tableClass* table = new tableClass(numRows, numCols);
    table->setData(DTtype);
    
   // TODO: read the file input name and call readCSV()
      table->readCSV(fileName); //read the file
      table->sortTable();

    // TODO: start reading the options till the end of the file
     while (cin >> option) {
        
             switch (option) {
                case 'F': { //Find value in record/row and return entire row
                    string findValue;
                    string record;
                    cin >> findValue; 
                    try{
                    record = table->searchRecord(findValue);
                    // If the record is found, print its content
                    
                            cout << "Record found: " <<endl;
                            cout<< record;
                        
                        cout << endl;
                      
                    }catch(const RecordNotFoundException& e){
                        
                        cout << e.getMessage() << endl;
                    }
                    
                    break;
                }
                   
                case 'V': { // Find value in entire table and display row & col no.
                    string findValue;
                    cin >> findValue;
                    table->searchValue(findValue);
                    break;
                }
                   
                case 'D': { // Display myTable
                         table->display();
                    break;
                }
                   
                case 'I': { // Find the min of col no. given
                    int colNum;
                    double requiredValue;
                    cin >> colNum;
                    if(colNum< table->getNumberCols()){ // Checking if it is in bound
                        try{
                            requiredValue = table->findMin(colNum);
                            cout<< "Min of " << colNum << " is " << requiredValue << endl;
                        }catch(const WrongDataTypeException& e){
                            cout << e.wrongColumn() << endl;
                        }
                    }
                    else{
                        cout<< "Column Number " << colNum << " out of bounds" << endl;
                    }   
                                   
                    break;
                }
                   
                case 'C': { //return a tableClass object with subset of rows and all cols b/w given interval
                    int startCol, endCol;
                     cin >> startCol >> endCol;
                    if(startCol < table->getNumberCols() & endCol < table->getNumberCols() ){
                    tableClass* a = table->getColumns(startCol, endCol);
                    a->display();
                    }
                    else{
                        cout<< "Out Of bound" << endl;
                    }
                    break;
                }
                
                case 'R': { // return a tableClass object with subset of rows and all cols b/w given interval
                    int startRow, endRow;
                    cin >> startRow >> endRow;
                    if(startRow < table->getNumberRows() & endRow < table->getNumberRows() ){
                    tableClass* a = table->getRows(startRow, endRow);
                    a->display();
                    }
                    else{
                        cout<< "Out Of bound" << endl;
                    }
                    break;
                }
               
                case 'S': { // return a tableClass object with subset of rows and all cols b/w given interval
                    int startCol, endCol, startRow, endRow;
                    cin >> startCol >> endCol >> startRow >> endRow;
                    if(startCol < table->getNumberCols() & endCol < table->getNumberCols() &
                                startRow < table->getNumberRows() & endRow < table->getNumberRows() ){

                    tableClass* a = table->getRowsCols(startCol, endCol, startRow, endRow);
                    a->display();
                    }
                    else{
                         cout<< "Out Of bound" << endl;
                    }
                    break;
                }
                   
                default:
                    cout << "Invalid option: " << option << endl;
                    break;
            }
        }

   

 
    return 0;
    delete table;
    delete[] DTtype;
}