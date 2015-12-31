#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <sstream>
using namespace std;

int main () {

  cout << "Welcome to the Fallout 4 Command Console Helper." << endl;
  cout << "This program helps you create scripts to run with the bat command on Fallout." << endl;
  cout << "The keyword 'item' is for item acquisition scripts, and 'perk' for perk addition." << endl;
  cout << "Please specify script type: ";

// Prepare input variables
  string scriptType;
  bool correctInput = false;
  string option1 = "item";
  string option2 = "perk";
  int option = 0;
  int itemAmount;

// Loop until a correct input is given
  while (correctInput == false){
    cin >> scriptType;

    // Turn the input into lowercase to make string comparisons
    // Code snippet taken from: http://stackoverflow.com/a/313990
    transform(scriptType.begin(), scriptType.end(), scriptType.begin(), ::tolower);
    if (scriptType.compare(option1) == 0){
      // Item script selected
      option = 1;
      cout << "Item script selected." << endl;
      correctInput = true;
    }
    else if (scriptType.compare(option2) == 0){
      // Perk script selected
      option = 2;
      cout << "Perk script selected." << endl;
      correctInput = true;
    }
    else{
      cout << "Input not recognized. Use the keywords 'item' or 'perk' without quotations." << endl;
      cout << "Please re-enter script type: ";
    }
  }

// Item script creation
if (option == 1){
  cout << "Please enter the IDs of the items you want  and separate them by a comma (example a,b,c,d): ";
  string itemList;
  cin >> itemList;

  // Amount of items added config
  itemAmount = 1;

  // Create and open the file to write to
  ofstream myfile;
  myfile.open ("items.txt");

  // Code snippet written with the help of: http://stackoverflow.com/a/11719617
  istringstream ss(itemList);
  string token;

  // Add comment to file
  myfile << "! Created with FO4ConsoleHelper\n";

  while(getline(ss, token, ',')) {
    myfile << "player.additem " << token << " " << itemAmount << "\n";
  }
  // Close the file since modifications are complete
  myfile.close();

  // Notify user
  cout << "\nScript created!" << endl;
  cout << "Move items.txt to Steam\\steamapps\\common\\Fallout 4" << endl;
  cout << "To run the script, open Fallout 4 and while playing press ~ on your keyboard." << endl;
  cout << "Then type: bat \"items.txt\" " << endl;
  cout << "Make sure your item IDs are correct if there are any problems." << endl;

  }

  // Perk script creation
  if (option == 2){

  }

  return 0;
}
