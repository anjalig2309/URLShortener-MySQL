#include <iostream>
#include <mysql/mysql.h>
#include <ctime>
#include <cstdlib>

using namespace std;

const char *HOST = "localhost";
const char *USER = "root";
const char *PASSWORD = "";
const char *DATABASE = "url_shortener";

string generateShortCode() {
    string chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    string shortCode = "";
    srand(time(0));
    for (int i = 0; i < 6; i++) {
        shortCode += chars[rand() % chars.length()];
    }
    return shortCode;
}

void insertURL(string longURL) {
    MYSQL *conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, HOST, USER, PASSWORD, DATABASE, 0, NULL, 0)) {
        cout << "Database connection failed!" << endl;
        return;
    }
    
    string shortCode = generateShortCode();
    string query = "INSERT INTO urls (short_code, long_url) VALUES ('" + shortCode + "', '" + longURL + "')";
    if (mysql_query(conn, query.c_str()) == 0) {
        cout << "Shortened URL: http://localhost/" << shortCode << endl;
    } else {
        cout << "Failed to insert URL." << endl;
    }
    mysql_close(conn);
}

void getLongURL(string shortCode) {
    MYSQL *conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, HOST, USER, PASSWORD, DATABASE, 0, NULL, 0)) {
        cout << "Database connection failed!" << endl;
        return;
    }
    
    string query = "SELECT long_url FROM urls WHERE short_code = '" + shortCode + "'";
    if (mysql_query(conn, query.c_str()) == 0) {
        MYSQL_RES *res = mysql_store_result(conn);
        MYSQL_ROW row;
        if ((row = mysql_fetch_row(res))) {
            cout << "Redirect to: " << row[0] << endl;
        } else {
            cout << "Short URL not found." << endl;
        }
        mysql_free_result(res);
    } else {
        cout << "Query failed." << endl;
    }
    mysql_close(conn);
}

int main() {
    int choice;
    string url, code;
    
    cout << "1. Shorten URL\n2. Retrieve Original URL\nEnter choice: ";
    cin >> choice;
    cin.ignore();
    
    if (choice == 1) {
        cout << "Enter long URL: ";
        getline(cin, url);
        insertURL(url);
    } else if (choice == 2) {
        cout << "Enter short code: ";
        cin >> code;
        getLongURL(code);
    } else {
        cout << "Invalid choice!" << endl;
    }
    
    return 0;
}
