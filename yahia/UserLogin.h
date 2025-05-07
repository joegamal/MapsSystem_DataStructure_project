#ifndef USERLOGIN_H
#define USERLOGIN_H

#include <string>
#include <unordered_map>
#include <stdexcept>
#include <regex>  // Add this include

using namespace std;

class UserLogin {
public:
static bool validateMobileNumber(const std::string& mobileNumber) ;


    struct User {
        string firstName;
        string lastName;
        string phone;
        string password;
    };

    bool login(const string& phone, const string& password);
   void signUp(const string& firstName, const string& lastName, 
            const string& phone, const string& password);
    bool userExists(const string& phone) const;
    const User& getCurrentUser() const;
    bool isLoggedIn() const;
    void logout();

private:
    unordered_map<string, User> usersDatabase;
    User* currentUser = nullptr;
    
    bool isValidPhone(const string& phone) const;
    bool isValidPassword(const string& password) const;
    string hashPassword(const string& password) const;
    string getValidPhoneFromUser() const;
};

#endif