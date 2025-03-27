#include <iostream>
#include <mysql/mysql.h>
#include <cstdlib>
#include <ctime>

using namespace std;

#define HOST "localhost"
#define USER "root"
#define PASSWORD ""
#define DATABASE "mydb"

string generateShortCode(MYSQL *conn) {
    string chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    string shortCode;
    MYSQL_RES *res;
    MYSQL_ROW row;
    
    do {
        shortCode.clear();
        for (int i = 0; i < 6; i++) {
            shortCode += chars[rand() % chars.length()];
        }
        
        string query = "SELECT COUNT(*) FROM urls WHERE short_code = '" + shortCode + "'";
        if (mysql_query(conn, query.c_str())) {
            cerr << "Query execution failed: " << mysql_error(conn) << endl;
            return "";
        }
        
        res = mysql_store_result(conn);
        row = mysql_fetch_row(res);
    } while (atoi(row[0]) > 0);
    
    mysql_free_result(res);
    return shortCode;
}

void saveURL(MYSQL *conn, string longURL) {
    string shortCode = generateShortCode(conn);
    if (shortCode.empty()) return;
    
    char* escapedURL = new char[2 * longURL.length() + 1];
    mysql_real_escape_string(conn, escapedURL, longURL.c_str(), longURL.length());
    
    string query = "INSERT INTO urls (short_code, long_url) VALUES ('" + shortCode + "', '" + escapedURL + "')";
    
    if (mysql_query(conn, query.c_str())) {
        cerr << "Error inserting data: " << mysql_error(conn) << endl;
    } else {
        cout << "Short URL generated: " << shortCode << endl;
    }
    
    delete[] escapedURL;
}

int main() {
    srand(time(0));
    
    MYSQL *conn;
    conn = mysql_init(NULL);
    
    if (!conn) {
        cerr << "MySQL initialization failed!" << endl;
        return 1;
    }
    
    if (!mysql_real_connect(conn, HOST, USER, PASSWORD, DATABASE, 0, NULL, 0)) {
        cerr << "Database connection failed: " << mysql_error(conn) << endl;
        return 1;
    }
    
    string longURL;
    cout << "Enter long URL: ";
    cin >> longURL;
    
    saveURL(conn, longURL);
    
    mysql_close(conn);
    return 0;
}
