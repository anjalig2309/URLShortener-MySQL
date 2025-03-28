#include <iostream>
#include <mysql/mysql.h>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

const string CHARSET = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
const int SHORT_CODE_LENGTH = 6;

// Function to generate a random short URL
string generateShortCode(MYSQL *conn) {
    string shortCode;
    bool unique = false;
    srand(time(0));
    
    while (!unique) {
        shortCode = "";
        for (int i = 0; i < SHORT_CODE_LENGTH; i++) {
            shortCode += CHARSET[rand() % CHARSET.length()];
        }

        string query = "SELECT COUNT(*) FROM urls WHERE short_code='" + shortCode + "'";
        if (mysql_query(conn, query.c_str()) == 0) {
            MYSQL_RES *res = mysql_store_result(conn);
            MYSQL_ROW row = mysql_fetch_row(res);
            if (row && atoi(row[0]) == 0) {
                unique = true;
            }
            mysql_free_result(res);
        }
    }
    return shortCode;
}

// Function to insert URL into the database
void insertURL(MYSQL *conn, string longURL) {
    string shortCode = generateShortCode(conn);
    string query = "INSERT INTO urls (long_url, short_code) VALUES ('" + longURL + "', '" + shortCode + "')";
    
    if (mysql_query(conn, query.c_str()) == 0) {
        cout << "Shortened URL: http://short.ly/" << shortCode << endl;
    } else {
        cerr << "Failed to insert URL: " << mysql_error(conn) << endl;
    }
}

int main() {
    MYSQL *conn = mysql_init(NULL);
    if (!conn) {
        cerr << "MySQL initialization failed!" << endl;
        return 1;
    }

    if (!mysql_real_connect(conn, "localhost", "root", "", "mydb", 3306, NULL, 0)) {
        cerr << "Connection failed: " << mysql_error(conn) << endl;
        return 1;
    }

    string longURL;
    cout << "Enter URL to shorten: ";
    getline(cin, longURL);
    insertURL(conn, longURL);

    mysql_close(conn);
    return 0;
}
