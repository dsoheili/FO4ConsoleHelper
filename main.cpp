#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <sstream>
#include <random>
#include <vector>
using namespace std;

string getRandomID (string path){
  ifstream the_file(path);
  vector<std::string> lines;
  string current_line;

  while (getline(the_file, current_line))
    lines.push_back(current_line);

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(0, lines.size());

  return lines[dis(gen)];
}


int main () {

  cout << "Welcome to the Fallout 4 Command Console Helper." << endl;
  cout << "This program helps you create scripts to run with the bat command on Fallout." << endl;
  cout << "The keyword 'item' is for item acquisition scripts, and 'perk' for perk addition." << endl;
  cout << "To generate a starterkit use the keyword 'kit'." << endl;
  cout << "Please specify script type: ";

// Prepare input variables
  string scriptType;
  bool correctInput = false;
  string option1 = "item";
  string option2 = "perk";
  string option3 = "kit";
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
      cout << "Item script selected.\n" << endl;
      correctInput = true;
    }
    else if (scriptType.compare(option2) == 0){
      // Perk script selected
      option = 2;
      cout << "Perk script selected.\n" << endl;
      correctInput = true;
    }
    else if (scriptType.compare(option3) == 0){
      // Starterkit script selected
      option = 3;
      cout << "Starterkit generator selected.\n" << endl;
      correctInput = true;
    }
    else{
      cout << "Input not recognized. Use the keywords 'item' or 'perk' without quotations." << endl;
      cout << "Please re-enter script type: ";
    }
  }

// Item script creation
if (option == 1){
  cout << "Please enter the IDs of the items you want and separate them by a comma (example a,b,c,d): ";
  string itemList;
  cin >> itemList;

  // Amount of items added config
  itemAmount = 1;

  // Create and open the file to write to
  ofstream myfile;
  myfile.open ("items.txt");

  // Add comment to file
  myfile << "! Created with FO4ConsoleHelper\n";

  // Code snippet written with the help of: http://stackoverflow.com/a/11719617
  // Break down the list and enter its contents in the file
  istringstream ss(itemList);
  string token;

  while(getline(ss, token, ',')) {
    myfile << "player.additem " << token << " " << itemAmount << "\n";
  }
  // Close the file since modifications are complete
  myfile.close();

  // Notify user
  cout << "\nScript created!\n" << endl;
  cout << "Move items.txt to Steam\\steamapps\\common\\Fallout 4" << endl;
  cout << "To run the script, open Fallout 4 and while playing press ~ on your keyboard." << endl;
  cout << "Then type: bat \"items.txt\" " << endl;

  }

  // Perk script creation
  else if (option == 2){
    cout << "Note: In order to obtain rank 4/4 in a perk, the previous ranks' IDs need to be added as well." << endl;
    cout << "Please enter the IDs of the perks you want and separate them by a comma (example a,b,c,d): ";
    string perkList;
    cin >> perkList;

    // Create and open the file to write to
    ofstream myfile;
    myfile.open ("perks.txt");

    // Add comment to file
    myfile << "! Created with FO4ConsoleHelper\n";

    // Break down the list and enter its contents in the file
    istringstream ss(perkList);
    string token;

    while(getline(ss, token, ',')) {
      myfile << "player.addperk " << token << "\n";
    }
    // Close the file since modifications are complete
    myfile.close();

    cout << "\nScript created!\n" << endl;
    cout << "Move perks.txt to Steam\\steamapps\\common\\Fallout 4" << endl;
    cout << "To run the script, open Fallout 4 and while playing press ~ on your keyboard." << endl;
    cout << "Then type: bat \"perks.txt\" " << endl;
  }

  if ((option == 1) || (option == 2)){
    cout << "Close the command console by pressing ~ again." << endl;
    cout << "Make sure your item IDs are correct if there are any problems." << endl;
  }

  // Kit generator
  // Consists of armor, health items, gun, ammunition, melee weapon, and utility
  if (option == 3){

  // read clothing IDs file
  string testID;
  testID = getRandomID("data/melee.txt");
  cout << testID << endl;
  }
  return 0;
}
