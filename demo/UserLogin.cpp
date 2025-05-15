
#include "UserLogin.h"
#include <iostream>
#include <regex>



bool UserLogin::validateMobileNumber(const std::string& mobileNumber){
    static const regex pattern("^\\+[1-9]\\d{7,14}$");
    return regex_match(mobileNumber, pattern);

}
bool UserLogin::login(const string& phone, const string& password) {
    if (isLoggedIn()) {
        cout << "Already logged in. Please logout first.\n";
        return false;
    }

    if (!validateMobileNumber(phone)) {
        cout << "Invalid phone number format.\n";
        return false;
    }

    auto it = usersDatabase.find(phone);
    if (it != usersDatabase.end() && it->second.password == hashPassword(password)) {
        currentUser = &(it->second);
        cout << "Login successful! Welcome " << currentUser->firstName << ".\n";
        return true;
    }
    cout << "Invalid phone number or password.\n";
    return false;
}

void UserLogin::signUp(const string& firstName, const string& lastName,
    const string& phone, const string& password) {
    if (userExists(phone)) {
        throw runtime_error("Phone number already registered");
    }

    if (!isValidPhone(phone)) {
        throw runtime_error("Invalid phone number format");
    }

    if (!isValidPassword(password)) {
        throw runtime_error("Password must be at least 8 characters");
    }

    User newUser{firstName, lastName, phone, hashPassword(password)};
    usersDatabase[phone] = newUser;
    cout << "Registration successful! Welcome " << firstName << ".\n";
}

bool UserLogin::userExists(const string& phone) const {
    return usersDatabase.find(phone) != usersDatabase.end();
}

const UserLogin::User& UserLogin::getCurrentUser() const {
    if (!currentUser) {
        throw runtime_error("No user logged in");
    }
    return *currentUser;
}

bool UserLogin::isLoggedIn() const {
    return currentUser != nullptr;
}

void UserLogin::logout() {
    if (currentUser) {
        cout << "Goodbye, " << currentUser->firstName << "!\n";
        currentUser = nullptr;
    }
}

bool UserLogin::isValidPhone(const string& phone) const {
    return validateMobileNumber(phone);
}

bool UserLogin::isValidPassword(const string& password) const {
    return password.length() >= 8;
}

string UserLogin::hashPassword(const string& password) const {
    // In production, use proper hashing like bcrypt
    // This is just a placeholder implementation
    return password; // Never do this in production!
}

string UserLogin::getValidPhoneFromUser() const {
    string phone;
    while (true) {
        cout << "Enter phone number (international format, e.g., +201234567890): ";
        cin >> phone;
        
        if (validateMobileNumber(phone)) {
            return phone;
        }
        
        cout << "Invalid format! Examples:\n"
             << "- Egypt: +201234567890\n"
             << "- USA: +12025551234\n"
             << "- UK: +447912345678\n"
             << "Please try again.\n";
    }
}
