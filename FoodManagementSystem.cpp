/*Develop a small Food Management System for a cafeteria to store the calories of different food items.
Create class name as Food with int fid,string fname,int fcalories with constructor as well as setter getter.
Also create custome exception class, and nessary fucntions.
Use File handling to store data into file
Implement the functionalities:
    1---->Add Food Info:
    2---->View All Food Info:
    3---->Search Food By Food Name:
    4---->Update Food Calories By Food Name:
    5---->Highest And Lowest Calorie Food
    6---->Find Avarge Calories Of All Food:
    7---->Sort Food By Calories:
    8---->Sort Food By Name:
    9---->Show Food's Whose Calories Are Above The Average
    10--->Food Item's Have Calories In The Range 200 to 500 (Inclusive)
    11--->Show All Sweet Category Food
    12--->Show All Spice Category Food
    13--->Show Sweet Catergory Food With Lowest Calories
    14--->Delete Food By Id
    15--->.....EXIT.....

Constraints:
• Use an vector to store Food objects.
• Use proper OOP concepts (create an Food class with appropriate fields and constructor).
• Use a menu-driven approach in the main program.*/

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <exception>
#include <algorithm>
#include <thread>
#include <fstream>

using namespace std;
// Base Exception class(Exception Handling)
class FoodException : public exception
{
private:
  string message;

public:
  FoodException(string messages)
  {
    this->message = message;
  }
  const char *what()
  {
    return message.c_str();
  }
};
// Food Entity Class
class Food
{
private:
  int fid, fcalories;
  string fname, fcategory;

public:
  Food(int fid, string fname, int fcalories, string fcategory)
  {
    this->fid = fid;
    this->fname = fname;
    this->fcalories = fcalories;
    this->fcategory = fcategory;
  }
  void setFid(int fid)
  {
    this->fid = fid;
  }
  int getFid()
  {
    return fid;
  }
  void setFname(string fname)
  {
    this->fname = fname;
  }
  string getFname()
  {
    return fname;
  }
  void setFcalories(int fcalories)
  {
    this->fcalories = fcalories;
  }
  int getFcalories()
  {
    return fcalories;
  }
  void setFcategory(string fcategory)
  {
    this->fcategory = fcategory;
  }
  string getFcategory()
  {
    return fcategory;
  }
  void display()
  {
    cout << left << setw(10) << fid << setw(15) << fname << setw(15) << fcalories << setw(15) << fcategory << "\n";
  }
};

// Comparator Function for lower to higher calories CASE 7
bool sortFoodByCalories(Food &a, Food &b)
{
  return a.getFcalories() < b.getFcalories();
}

// Logic Controller Class
class FoodManger
{
private:
  vector<Food> fm;
  int fid, fcalories, len, again, choice;
  double avgcalories;
  string fname, fcategory;
  bool flag = false;
  const string FileName = "./FoodFile/foodInfo.txt";

public:
  // Add Food Info:
  void addFood()
  {
    cout << "\nHow many food do you want to add:\n";
    if (!(cin >> len))
    {
      throw invalid_argument("Please Enter Only Number:");
    }
    for (int i = 0; i < len; i++)
    {
      cout << "..... " << (i + 1) << "Food Info .....\n";
      cout << "Enter the food id\n";
      cin >> fid;
      cout << "Enter the food name\n";
      cin >> fname;
      cout << "Enter the food calories\n";
      if (!(cin >> fcalories))
      {
        throw invalid_argument("Critical: Input Must Be A Numeric Value.");
      }
      cout << "Enter the food Category (sweet Or spice)\n";
      cin >> fcategory;
      fm.emplace_back(Food(fid, fname, fcalories, fcategory));
    }
  }
  // View All Food Info:
  void showFoodInfo()
  {

    cout << left << setw(10) << "Food Id " << setw(10) << "Food Name " << setw(15) << "Food Calories" << setw(10) << "Food Category\n";
    for (auto &obj : fm)
    {
      obj.display();
    }
  }
  // Search Food By Name
  void searchFoodByName(string &fname)
  {
    flag = false;
    for (vector<Food>::iterator it = fm.begin(); it != fm.end(); it++)
    {
      if (it->getFname() == fname)
      {
        cout << "Food Found\n";
        it->display();
        flag = true;
      }
    }
    if (!flag)
      throw FoodException("Oop's Could Not Open foodFile.txt File.");
  }
  // Update Food Calories By Food Name:
  void updateFoodCalByName(string &fname)
  {
    flag = false;
    for (vector<Food>::iterator it = fm.begin(); it != fm.end(); it++)
    {
      if (it->getFname() == fname)
      {
        cout << "Food Found:\n";
        it->display();
        cout << "Enter the food calories for updatation\n";
        cin >> fcalories;
        it->setFcalories(fcalories);
        cout << "Food calorie updated succeffuly\n";
        flag = true;
      }
    }
  }
  // Highest And Lowest Calorie Food
  void higestAndLowsetCalFood()
  {
    if (fm.empty())
    {
      throw FoodException("Oop's Not Able To Find Highest And Lowest Calorie Food:\n");
    }
    // Creating pointer to store the address for min and max value
    auto maxIt = fm.begin();
    auto minIt = fm.begin();
    for (vector<Food>::iterator it = fm.begin(); it != fm.end(); it++)
    {
      // Finding highest
      if (it->getFcalories() > maxIt->getFcalories())
      {
        maxIt = it;
      }
      // Finding lowest
      if (it->getFcalories() < minIt->getFcalories())
      {
        minIt = it;
      }
    }
    cout << "\n.....Highest Calorie Food.....\n";
    maxIt->display();
    cout << "\n.....Lowest Calories Food.....\n";
    minIt->display();
  }
  // Calculating Avarge Food Carlories
  void findAvargeFoodCal()
  {
    double sum = 0;
    if (fm.empty())
    {
      throw FoodException("Oop's No Food Items Added Yet.\n");
    }
    for (vector<Food>::iterator it = fm.begin(); it != fm.end(); it++)
    {
      sum += it->getFcalories();
    }
    avgcalories = sum / fm.size();
    cout << "Avarge calorie of all food is: " << avgcalories << "\n";
  }
  // Comparator Function for lower to higher calories
  void sortingFoodByCalories()
  {
    // using sort function form algorithum header file
    sort(fm.begin(), fm.end(), sortFoodByCalories); // calling sort function
    cout << "Food sortting done by calories\n";
    for (auto &obj : fm)
    {
      obj.display();
    }
  }
  // Sort Food By Name
  void sortFoodByName()
  {
    for (int i = 0; i < fm.size(); i++)
    {
      for (int j = 0; j < fm.size(); j++)
      {
        if (fm[i].getFname() < fm[j].getFname())
        {
          Food temp = fm[i];
          fm[i] = fm[j];
          fm[j] = temp;
        }
      }
    }
    cout << "Food sortting done by food name\n";
    for (Food &obj : fm)
    {
      obj.display();
    }
  }
  // Show Food's Whose Calories Are Above The Average
  void showFoodAboveAverageCal()
  {
    flag = false;
    for (vector<Food>::iterator it = fm.begin(); it != fm.end(); it++)
    {
      if (it->getFcalories() > avgcalories)
      {
        it->display();
        flag = true;
      }
    }
    if (!flag)
      throw FoodException("Oop's  Food Not Found:\n");
  }
  // Food Item's Have Calories Between Range (Inclusive):
  void searchFoodByCalRange(int &startRange, int &endRange)
  {
    flag = false;
    cout << "List Of Food Item's Have Calories In The Range Between " << startRange << " to " << endRange << " (Inclusive) \n";
    for (vector<Food>::iterator it = fm.begin(); it != fm.end(); it++)
    {
      if (it->getFcalories() >= startRange && it->getFcalories() <= endRange)
      {
        it->display();
        flag = true;
      }
    }
    if (!flag)
      throw FoodException("Oop's No Food Between Giving Range:\n");
  }
  // Show All Sweet Category Food:
  void showAllSweetFood()
  {
    flag = false;
    for (vector<Food>::iterator it = fm.begin(); it != fm.end(); it++)
    {
      if (it->getFcategory() == "sweet")
      {
        it->display();
        flag = true;
      }
    }
    if (!flag)
      throw FoodException("Oop's  Food Not Found:\n");
  }
  // Show All Spice Category Food:
  void showAllSpiceFood()
  {
    flag = false;
    for (vector<Food>::iterator it = fm.begin(); it != fm.end(); it++)
    {
      if (it->getFcategory() == "spice")
      {
        it->display();
        flag = true;
      }
    }
    if (!flag)
      throw FoodException("Oop's  Food Not Found:\n");
  }
  // Show Sweet Catergory Food With Lowest Calories
  void lowestCalSweetFood()
  {
    sort(fm.begin(), fm.end(), sortFoodByCalories);
    flag = false;
    for (vector<Food>::iterator it = fm.begin(); it != fm.end(); it++)
    {
      if (it->getFcategory() == "sweet")
      {
        it->display();
        flag = true;
        break;
      }
    }
    if (!flag)
      throw FoodException("Oop's  Food Not Found:\n");
  }
  // Delete Food Info By Food Id
  void deleteFoodById()
  {
    flag = false;
    cout << "Enter the food Id for delating the food\n";
    cin >> fid;
    for (vector<Food>::iterator it = fm.begin(); it != fm.end(); it++)
    {
      if (it->getFid() == fid)
      {
        fm.erase(it);
        flag = true;
        break;
      }
    }
    if (!flag)
      throw FoodException("Oop's  Food Not Found:\n");
  }
  // Saving Data And Ending The Program
  void savingDataAndEnd()
  {
    cout << "Saving And Exiting...\nThank You....\nVist Again....\n";
    saveInFile(); // Saving Data Into File
  }
  // Storing All Food Info From Vector To File(File Handling)
  void saveInFile()
  {
    fstream foodFile;
    try
    {
      foodFile.open(FileName, ios::out | ios::trunc);
      if (foodFile.is_open())
      {
        for (auto &f : fm)
        {
          foodFile << f.getFid() << " " << f.getFname() << " " << f.getFcalories() << " " << f.getFcategory() << "\n";
          if (foodFile.fail())
            throw FoodException("Oop's Failed While Writing Data To File.");
        }
        cout << "Data Saved Successfully To File\n";
        foodFile.close();
      }
      else
      {
        throw FoodException("Oop's Could Not Open foodFile.txt File.");
      }
    }
    catch (FoodException &fe)
    {
      cout << "File Error: " << fe.what();
    }
  }
  // Loadding All Food Info From File To Vector(File Handling)
  void loadFromFile()
  {
    fstream foodFile;
    int fid, fcalories;
    string fname, fcategory;
    try
    {
      foodFile.open(FileName, ios::in);
      if (foodFile.is_open())
      {
        fm.clear(); // Clearing exsiting data for avoding duplicating data in vector
        while (foodFile >> fid >> fname >> fcalories >> fcategory)
        {
          fm.emplace_back(Food(fid, fname, fcalories, fcategory));
        }
        // Cheking if stop because of bad data
        if (!foodFile.eof() && foodFile.fail())
        {
          throw FoodException("Oop's Error Occurred While Reading Food Data (Corrupted File).");
        }
        foodFile.close();
        cout << "Data Loaded Successfully From File\n";
      }
      else
      {
        throw FoodException("Oop's Could Not Open foodFile.txt File.");
      }
    }
    catch (FoodException &fn)
    {
      cout << "File Error" << fn.what();
    }
  }
};

// main function
int main()
{
  int again, choice, startRange, endRange;
  string fname;

  FoodManger manger;

  // Loadding Data From File To Vector
  manger.loadFromFile();

  // View All Food Info From File To Vector:
  cout << "\n-----Present Data From File:-----\n";
  manger.showFoodInfo();
  try
  {
    do
    {
      this_thread::sleep_for(1500ms);

      cout << "\n\n====== Food Management System ======\n\n";
      cout << "1---->Add Food Info:\n";
      cout << "2---->View All Food Info:\n";
      cout << "3---->Search Food By Food Name:\n";
      cout << "4---->Update Food Calories By Food Name:\n";
      cout << "5---->Highest And Lowest Calorie Food:\n";
      cout << "6---->Find Avarge Calories Of All Food:\n";
      cout << "7---->Sort Food By Calories:\n";
      cout << "8---->Sort Food By Name:\n";
      cout << "9---->Show Food's Whose Calories Are Above The Average:\n";
      cout << "10--->Search Food By Calories Range (Inclusive):\n";
      cout << "11--->Show All Sweet Category Food:\n";
      cout << "12--->Show All Spice Category Food:\n";
      cout << "13--->Show Sweet Catergory Food With Lowest Calories\n";
      cout << "14--->Delete Food By Id:\n";
      cout << "15--->.....EXIT.....\n";
      cout << "Enter the choice:\n";
      if (!(cin >> choice))
      {
        throw invalid_argument("Invaild Menu Selection: Please Enter Number.");
      }
      switch (choice)
      {
      case 1:
      { // Add Food Info:
        manger.addFood();
        break;
      }
      case 2:
      { // View All Food Info:
        manger.showFoodInfo();
        break;
      }
      case 3:
      { // Search Food By Food Name:
        cout << "Enter the food for search\n";
        cin >> fname;
        manger.searchFoodByName(fname);
        break;
      }
      case 4:
      { // Update Food Calories By Food Name:
        cout << "Enter the food name for calories updatation\n";
        cin >> fname;
        manger.updateFoodCalByName(fname);
        break;
      }
      case 5:
      { // Highest And Lowest Calorie Food
        manger.higestAndLowsetCalFood();
        break;
      }
      case 6:
      { // Find Avarge Calories Of All Food:
        manger.findAvargeFoodCal();
        break;
      }
      case 7:
      { // Sort Food By Calories
        // using sort function form algorithum header file
        manger.sortingFoodByCalories();
        break;
      }
      case 8:
      { // Sort Food By Name
        manger.sortFoodByName();
        break;
      }
      case 9:
      { // Show Food's Whose Calories Are Above The Average
        manger.showFoodAboveAverageCal();
        break;
      }
      case 10:
      { // Food Item's Have Calories In The Range 200 to 500 (Inclusive):
        cout << "Enter The Starting Range Of Calroires\n";
        cin >> startRange;
        cout << "Ente The Ending Range Of Calroires\n";
        cin >> endRange;
        manger.searchFoodByCalRange(startRange, endRange);
        break;
      }
      case 11:
      { // Show All Sweet Category Food:
        manger.showAllSweetFood();
        break;
      }
      case 12:
      { // Show All Spice Category Food:
        manger.showAllSpiceFood();
        break;
      }
      case 13:
      { // Show Sweet Catergory Food With Lowest Calories
        manger.lowestCalSweetFood();
        break;
      }
      case 14:
      { // Delete Food Info By Food Id
        manger.deleteFoodById();
        break;
      }
      case 15:
      {
        // Saving Data And Ending Program
        manger.savingDataAndEnd();
        return 0;
      }
      default:
      {
        cout << "\nWrong Choice\n";
      }
      }
    } while (choice < 15);
  }
  // specific custome exception
  catch (FoodException &fe)
  {
    cout << "Application Error: " << fe.what() << "\n";
    cout << "\n\n-----Attempting Emergency Data Save-----\n";
    manger.saveInFile();
    return 1;
  }
  // library excprtion(bad_alloc,invalid_argument)
  catch (exception &e)
  {
    cout << "System Error: " << e.what() << "\n";
    cout << "\n\n-----Attempting Emergency Data Save-----\n";
    manger.saveInFile();
    return 1;
  }
}