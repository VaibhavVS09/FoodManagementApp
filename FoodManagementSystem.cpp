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
    Adding more as per requriment....

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
// Gobal Variable
string currentUser;

// Base Exception class(Exception Handling)
class FoodException : public exception
{
private:
  string message;

public:
  FoodException(string message)
  {
    this->message = message;
  }
  const char *what()
  {
    return message.c_str();
  }
};

// Food Entity Class Base Class
class Food
{
private:
  int fid, fcalories, quantity, price;
  string fname;

public:
  Food(int fid, string fname, int fcalories, int quantity, int price)
  {
    this->fid = fid;
    this->fname = fname;
    this->fcalories = fcalories;
    this->quantity = quantity;
    this->price = price;
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
  void setFquantity(int quantity)
  {
    this->quantity = quantity;
  }
  int getFquantity()
  {
    return quantity;
  }
  void setFprice(int price)
  {
    this->price = price;
  }
  int getPrice()
  {
    return price;
  }

  virtual string getFcategory()
  {
    return "General";
  }
  virtual void display()
  {
    cout << left << setw(10) << fid << setw(15) << fname << setw(15) << fcalories << setw(15) << quantity << setw(15) << price;
  }
};
// sweet Food Derived Class
class SweetFood : public Food
{
public:
  SweetFood(int fid, string fname, int fcalories, int quantity, int price) : Food(fid, fname, fcalories, quantity, price) {}
  string getFcategory()
  {
    return "sweet";
  }
  void display()
  {
    Food::display();
    cout << setw(15) << "sweet" << "\n";
  }
};
// spice Food Derived Class
class SpiceFood : public Food
{
public:
  SpiceFood(int fid, string fname, int fcalories, int quantity, int price) : Food(fid, fname, fcalories, quantity, price) {}
  string getFcategory()
  {
    return "spice";
  }
  void display()
  {
    Food::display();
    cout << setw(15) << "spcie" << "\n";
  }
};

// Comparator Function for lower to higher calories CASE 7
bool sortFoodByCalories(Food *a, Food *b)
{
  return a->getFcalories() < b->getFcalories();
}

// Logic Controller Class
class FoodManger
{
private:
  vector<Food *> fm;
  int fid, fcalories, len, again, choice, quantity, price;
  double avgcalories;
  string fname, fcategory;
  bool flag = false;
  const string FileName = "./FoodFile/foodInfo.txt";
  const string walletFile = "./FoodFile/wallet.txt";

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
      cout << "..... " << (i + 1) << " Food Info .....\n";
      cout << "Enter The Food Id\n";
      cin >> fid;
      cout << "Enter The Food Name\n";
      cin >> fname;
      cout << "Enter The Food Calories\n";
      if (!(cin >> fcalories))
      {
        throw invalid_argument("Critical: Input Must Be A Numeric Value.");
      }
      cout << "Enter Food Price:\n";
      cin >> price;
      cout << "Enter The Food Quantity\n";
      cin >> quantity;
      cout << "Enter The Food Category (sweet Or spice)\n";
      cin >> fcategory;
      if (fcategory == "sweet")
      {
        fm.push_back(new SweetFood(fid, fname, fcalories, quantity, price));
      }
      else if (fcategory == "spice")
      {
        fm.push_back(new SpiceFood(fid, fname, fcalories, quantity, price));
      }
    }
  }

  // View All Food Info:
  void showFoodInfo()
  {
    flag = false;
    cout << left << setw(10) << "Food Id " << setw(10) << "Food Name " << setw(15) << "Food Calories" << setw(15) << "Food Quantity" << setw(15) << "Food Price" << setw(15) << "Food Category\n";

    for (Food *food : fm)
    {
      food->display();
      flag = true;
    }
    if (!flag)
      cout << "No Food Data Present In File...\n";
  }

  // Search Food By Name
  void searchFoodByName(string &fname)
  {
    flag = false;
    for (Food *food : fm)
    {
      if (food->getFname() == fname)
      {
        cout << "Food Found\n";
        food->display();
        flag = true;
        break;
      }
    }
    if (!flag)
      throw FoodException("Oop's Could Not Open foodFile.txt File.");
  }

  // Update Food Calories By Food Name:
  void updateFoodCalByName(string &fname)
  {
    flag = false;
    // old C++ Version
    /*for (vector<Food *>::iterator it = fm.begin(); it != fm.end(); it++)
    {
      if ((*it)->getFname() == fname)
      {
        cout << "Food Found:\n";
        (*it)->display();
        cout << "Enter the food calories for updatation\n";
        cin >> fcalories;
        (*it)->setFcalories(fcalories);
        cout << "Food calorie updated succeffuly\n";
        flag = true;
      }
    }*/
    // Modern C++ Version
    for (Food *food : fm)
    {
      if (food->getFname() == fname)
      {
        food->display();
        cout << "Enter the food calories for updatation\n";
        cin >> fcalories;
        food->setFcalories(fcalories);
        cout << "Food calorie updated succeffuly\n";
        flag = true;
        break;
      }
    }
    if (!flag)
      throw FoodException("Oop's Food Not Found:\n");
  }

  // Highest And Lowest Calorie Food
  void higestAndLowsetCalFood()
  {
    if (fm.empty())
    {
      throw FoodException("Oop's Not Able To Find Highest And Lowest Calorie Food:\n");
    }
    // Creating pointer to store the address for min and max value
    auto maxFood = fm[0];
    auto minFood = fm[0];
    for (Food *food : fm)
    {
      // Finding highest
      if (food->getFcalories() > maxFood->getFcalories())
      {
        maxFood = food;
      }
      // Finding lowest
      if (food->getFcalories() < minFood->getFcalories())
      {
        minFood = food;
      }
    }
    cout << "\n.....Highest Calorie Food.....\n";
    maxFood->display();
    cout << "\n.....Lowest Calories Food.....\n";
    minFood->display();
  }

  // Calculating Avarge Food Carlories
  void findAvargeFoodCal()
  {
    double sum = 0;
    if (fm.empty())
    {
      throw FoodException("Oop's No Food Items Added Yet.\n");
    }
    for (Food *food : fm)
    {
      sum += food->getFcalories();
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
      obj->display();
    }
  }

  // Sort Food By Name
  void sortFoodByName()
  {
    for (int i = 0; i < fm.size(); i++)
    {
      for (int j = 0; j < fm.size(); j++)
      {
        if (fm[i]->getFname() < fm[j]->getFname())
        {
          Food *temp = fm[i];
          fm[i] = fm[j];
          fm[j] = temp;
        }
      }
    }
    cout << "Food sortting done by food name\n";
    for (auto &obj : fm)
    {
      obj->display();
    }
  }

  // Show Food's Whose Calories Are Above The Average
  void showFoodAboveAverageCal()
  {
    flag = false;
    for (Food *food : fm)
    {
      if (food->getFcalories() > avgcalories)
      {
        food->display();
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
    for (Food *food : fm)
    {
      if (food->getFcalories() >= startRange && food->getFcalories() <= endRange)
      {
        food->display();
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
    for (Food *food : fm)
    {
      if (food->getFcategory() == "sweet")
      {
        food->display();
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
    for (Food *food : fm)
    {
      if (food->getFcategory() == "spice")
      {
        food->display();
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
    for (Food *food : fm)
    {
      if (food->getFcategory() == "sweet")
      {
        food->display();
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
    for (vector<Food *>::iterator it = fm.begin(); it != fm.end(); it++)
    {
      if ((*it)->getFid() == fid)
      {
        delete *it;
        fm.erase(it);
        flag = true;
        break;
      }
    }
    if (!flag)
      throw FoodException("Oop's  Food Not Found:");
  }

  // Count Food By Category
  void countFoodByCategory()
  {
    int sweet = 0, spice = 0;
    for (Food *food : fm)
    {
      if (food->getFcategory() == "sweet")
      {
        sweet++;
      }
      else if (food->getFcategory() == "spice")
      {
        spice++;
      }
    }
    cout << "Total Sweet Food Are: " << sweet << "\n";
    cout << "Total Spice Food Are: " << spice << "\n";
  }

  // Find Food With Exact Calories
  void searchFoodByCalories(int cal)
  {
    flag = false;
    for (Food *food : fm)
    {
      if (food->getFcalories() == cal)
      {
        cout << "Food Found\n";
        food->display();
        flag = true;
      }
    }
    if (!flag)
      throw FoodException("Oop's Food Not Found With Giving Calories");
  }

  // Total Calories of All Foods
  void totalCaloriesOfFood()
  {
    int totalCal = 0;
    for (Food *food : fm)
    {
      totalCal += food->getFcalories();
    }
    cout << "Total Calories Of All Food's Are: " << totalCal << "\n";
  }

  // Read User Wallet
  int getUserWallet(string username)
  {
    string user;
    int amount;
    fstream wallet;
    wallet.open(walletFile, ios::in);
    while (wallet >> user >> amount)
    {
      if (user == username)
      {
        return amount;
      }
    }
    wallet.close();
    return amount;
  }

  // Update Wallet After Purchase
  void updateUserWallet(string username, int price)
  {
    string user;
    int amount;
    fstream wallet;
    fstream temp;
    wallet.open(walletFile, ios::in);
    temp.open("./FoodFile/temp.txt", ios::out);
    while (wallet >> user >> amount)
    {
      if (user == username)
      {
        amount -= price;
      }
      temp << user << " " << amount << "\n";
    }
    wallet.close();
    temp.close();
    remove("./FoodFile/wallet.txt");
    rename("./FoodFile/temp.txt", "./FoodFile/wallet.txt");
  }

  // Save Purchase History
  void savePurchaseHistory(string username, Food *food, int quantity, int totalPrice)
  {
    fstream history;
    history.open("./FoodFile/purchesHistory.txt", ios::app);
    if (history.is_open())
    {
      history << username << " "
              << food->getFid() << " "
              << food->getFname() << " "
              << food->getFcategory() << " "
              << food->getPrice() << " "
              << quantity << " "
              << totalPrice << "\n";
    }
    else
    {
      throw FoodException("Oop's Could Not Open purchesHistory.txt File.");
    }
    history.close();
  }

  // View Purchase History
  void viewPurchaseHistory(string username)
  {
    string fname, category, user;
    int id, price, quantity, totalprice;
    fstream history;
    flag = false;
    history.open("./FoodFile/purchesHistory.txt", ios::in);

    cout << left << setw(10) << "Food Id " << setw(10) << "Food Name " << setw(15) << "Food Category" << setw(15) << "Food Price" << setw(15) << "Food Quantity" << setw(15) << "Total Amount\n";

    while (history >> user >> id >> fname >> category >> price >> quantity >> totalprice)
    {
      if (user == username)
      {
        cout << left
             << setw(10) << id
             << setw(10) << fname
             << setw(15) << category
             << setw(15) << price
             << setw(15) << quantity
             << setw(15) << totalprice << "\n";
        flag = true;
      }
    }
    if (flag)
      cout << username << " Your Total Purchase History\n";
    else
      cout << username << " No Purchase History Avaible\n";
  }

  // Buy Food With Stock With Payment
  void buyFood(string username)
  {
    int id, price, wallet, quantity, totalPrice;
    flag = false;
    cout << "Enter The Food ID: \n";
    cin >> id;
    for (Food *food : fm)
    {
      if (food->getFid() == id)
      {
        if (food->getFquantity() <= 0)
        {
          cout << "Food Is Out Of Stock\n";
          return;
        }
        price = food->getPrice();
        wallet = getUserWallet(username);
        if (wallet < price)
        {
          cout << "Insufficient Wallet Balance\n";
          return;
        }
        cout << "Enter The Quantity Of Food\n";
        cin >> quantity;
        food->setFquantity(food->getFquantity() - quantity);
        totalPrice = quantity * price;
        // Calling Function
        updateUserWallet(username, totalPrice);
        savePurchaseHistory(username, food, quantity, totalPrice);
        cout << "Food Purchased Successfully\n";
        flag = true;
        break;
      }
    }
    if (!flag)
      cout << "Food Not Found\n";
  }
  // Daily Sales Report
  void dailySaleReport()
  {
    string name, category, username;
    int totalSale = 0, totalIteam = 0, id, calories, quantity, totalprice;
    fstream history;
    history.open("./FoodFile/purchesHistory.txt", ios::in);
    while (history >> username >> id >> name >> category >> calories >> quantity >> totalprice)
    {
      totalSale += totalprice;
      totalIteam += quantity;
    }
    cout << "\n===== DAILY SALES REPORT =====\n";
    cout << "Total Items Sold: " << totalIteam << "\n";
    cout << "Total Revenue: " << totalSale << "\n";
  }

  // Wallet Blanace Info
  void getWalletBalance(string user)
  {
    string userName;
    int amount;
    flag = false;
    fstream wallet;
    if (currentUser == user)
    {
      wallet.open(walletFile, ios::in);
      while (wallet >> userName >> amount)
      {
        if (userName == user)
        {
          cout << user << " Your Current Wallet Balance Is: " << amount << "\n";
          break;
        }
      }
      flag = true;
    }
    if (!flag)
      cout << user << " You'r Not Authorized To See Another User Wallet Balance\n";
  }

  // Add Amount Into Wallet
  void addAmountIntoWallet(string username)
  {
    string user;
    int amount, addAmt;
    fstream wallet;
    fstream temp;
    wallet.open(walletFile, ios::in);
    temp.open("./FoodFile/temp.txt", ios::out);
    while (wallet >> user >> amount)
    {
      if (user == username)
      {
        cout << user << " Your Current Wallet Balance Is: " << amount << "\n";
        cout << "How Much Amount Do You Want To Add In Your Wallet\n";
        cin >> addAmt;
        amount += addAmt;
        cout << "Amount Added Successfully\n";
        cout << "New Wallet Balance: " << amount << "\n";
      }
      temp << user << " " << amount << "\n";
    }
    wallet.close();
    temp.close();
    remove("./FoodFile/wallet.txt");
    rename("./FoodFile/temp.txt", "./FoodFile/wallet.txt");
  }

  //====================================
  // File Handling Logic
  //
  //  Saving Data And Ending The Program
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
          foodFile << f->getFid() << " " << f->getFname() << " " << f->getFcalories() << " " << f->getFquantity() << " " << f->getPrice() << " " << f->getFcategory() << "\n";
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
    int fid, fcalories, quantity, price;
    string fname, fcategory;
    try
    {
      foodFile.open(FileName, ios::in);
      if (foodFile.is_open())
      {
        fm.clear(); // Clearing exsiting data for avoding duplicating data in vector
        while (foodFile >> fid >> fname >> fcalories >> quantity >> price >> fcategory)
        {
          if (fcategory == "sweet")
          {
            fm.emplace_back(new SweetFood(fid, fname, fcalories, quantity, price));
          }
          else if (fcategory == "spice")
          {
            fm.emplace_back(new SpiceFood(fid, fname, fcalories, quantity, price));
          }
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
  ~FoodManger() {}
};

// Admin Login Logic
bool adminLogin()
{
  string username, password;
  string filerUser, filePass;
  const string AdminFile = "./FoodFile/admin.txt";
  cout << "\n\n===== ADMIN LOGIN =====\n\n";
  cout << "Enter UserName: \n";
  cin >> username;
  cout << "Enter Password:\n";
  cin >> password;
  // File Checking
  fstream login;
  login.open(AdminFile, ios::in);
  if (!login)
  {
    cout << "Admin File Not Found\n";
    return false;
  }
  while (login >> filerUser >> filePass)
  {
    if (username == filerUser && password == filePass)
    {
      cout << "Admin Login Successful\n";
      return true;
    }
  }
  cout << "Invalid Admin Credentail's\n";
  return false;
}

// User Login Logic
bool userLogin()
{
  string username, password;
  string filerUser, filePass;
  const string UserFile = "./FoodFile/users.txt";
  cout << "\n\n===== USER LOGIN =====\n\n";
  cout << "Enter UserName: \n";
  cin >> username;
  cout << "Enter Password:\n";
  cin >> password;
  // File checking
  fstream login;
  login.open(UserFile, ios::in);
  if (!login)
  {
    cout << "User File Not Found\n";
    return false;
  }
  while (login >> filerUser >> filePass)
  {
    if (username == filerUser && password == filePass)
    {
      cout << "User Login Successful\n";
      currentUser = username;
      return true;
    }
  }
  cout << "Invalid Usre Credentail's\n";
  return false;
}

// main function
int main()
{
  int again, choice, startRange, endRange, calories, logChoice, addAmount;
  string fname;

  // Logic Control App
  FoodManger manger;
  // Login Logic
  cout << "\n\n\033[32m===== LOGIN MENU =====\033[0m\n\n";
  cout << "1---->Admin Login\n";
  cout << "2---->User Login\n";
  cout << "3......EXIT......\n";
  cout << "Enter Choice:\n";
  cin >> logChoice;
  if (logChoice == 1)
  {
    if (adminLogin())
      logChoice = 1;
    else
      return 0;
  }
  else if (logChoice == 2)
  {
    if (userLogin())
      logChoice = 2;
    else
      return 0;
  }
  else
  {
    return 0;
  }
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
      cout << "\n\n\033[36m====== Food Management System ======\033[0m\n\n";
      if (logChoice == 1)
      {
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
        cout << "15--->Count Food Category\n";
        cout << "16--->Find Food With Exact Calories\n";
        cout << "17-->Show Total Calories of All Foods\n";
        cout << "18--->Buy Food\n";
        cout << "19--->View Purchase History\n";
        cout << "20--->Daily Sales Report\n";
        cout << "21--->Show Wallet Balance\n";
        cout << "22--->Add Amount Into Wallet\n";
        cout << "23--->.....EXIT.....\n";
      }
      else if (logChoice == 2)
      {
        cout << "2---->View All Food Info:\n";
        cout << "3---->Search Food By Food Name:\n";
        cout << "5---->Highest And Lowest Calorie Food:\n";
        cout << "6---->Find Avarge Calories Of All Food:\n";
        cout << "7---->Sort Food By Calories:\n";
        cout << "8---->Sort Food By Name:\n";
        cout << "9---->Show Food's Whose Calories Are Above The Average:\n";
        cout << "10--->Search Food By Calories Range (Inclusive):\n";
        cout << "11--->Show All Sweet Category Food:\n";
        cout << "12--->Show All Spice Category Food:\n";
        cout << "13--->Show Sweet Catergory Food With Lowest Calories\n";
        cout << "15--->Count Food Category\n";
        cout << "16-->Find Food With Exact Calories\n";
        cout << "17-->Show Total Calories of All Foods\n";
        cout << "18--->Buy Food\n";
        cout << "19--->View Purchase History\n";
        cout << "21--->Show Wallet Balance\n";
        cout << "22--->Add Amount Into Wallet\n";
        cout << "23--->.....EXIT.....\n";
      }

      cout << "Enter the choice:\n";
      if (!(cin >> choice))
      {
        throw invalid_argument("Invaild Menu Selection: Please Enter Number.");
      }

      if ((logChoice == 2) && (choice == 1 || choice == 4 || choice == 14 || choice == 20))
      {
        cout << "Access Denied:\n Only Admin Feature\n";
        continue;
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
      { // Find Avarge Calories Of All Food:
        manger.findAvargeFoodCal();
        // Show Food's Whose Calories Are Above The Average
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
      { // Count Food Category
        manger.countFoodByCategory();
        break;
      }
      case 16:
      { // Find Food With Exact Calories
        cout << "Enter The Calories To Find Food:\n";
        cin >> calories;
        manger.searchFoodByCalories(calories);
        break;
      }
      case 17:
      { // Show Total Calories of All Foods
        manger.totalCaloriesOfFood();
        break;
      }
      case 18:
      { // View All Food Info:
        manger.showFoodInfo();
        // Buy Food
        manger.buyFood(currentUser);
        break;
      }
      case 19:
      { // View Purchase History
        manger.viewPurchaseHistory(currentUser);
        break;
      }
      case 20:
      { // Daily Sales Report
        manger.dailySaleReport();
        break;
      }
      case 21:
      { // Show User Wallet Balance
        manger.getWalletBalance(currentUser);
        break;
      }
      case 22:
      { // Add Amount Into Wallet

        manger.addAmountIntoWallet(currentUser);
        break;
      }
      case 23:
      { // Saving Data And Ending Program
        manger.savingDataAndEnd();
        return 0;
      }
      default:
      {
        cout << "\nWrong Choice\n";
      }
      }
    } while (choice < 24);
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