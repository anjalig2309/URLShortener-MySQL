📌 Project Overview
This project is a simple URL shortener built using C++ and MySQL. It allows users to convert long URLs into short codes and retrieve the original URLs using the short codes.


⚡ Features
✅ Shorten long URLs into 6-character unique codes
✅ Store short URLs in a MySQL database
✅ Retrieve original URLs using the short code
✅ Simple command-line interface


🛠️ Technologies Used

C++ for backend logic

MySQL for database storage

MySQL Connector for C++ for database interaction


📌 How It Works

Shorten a URL:

Enter a long URL

The system generates a random short code

Stores it in the database

Returns a shortened URL

Retrieve the Original URL:

Enter the short code

The system finds the original URL from the database

Displays the original link



⚙️ Setup & Installation
1️⃣ Prerequisites
Install MySQL Server

Install MySQL Connector for C++

Install MinGW (for compilation)


📌 Database Setup
Run the following SQL commands to create the database:

-- Create the database
CREATE DATABASE url_shortener;
USE url_shortener;

-- Create the table to store URLs
CREATE TABLE urls (
    id INT AUTO_INCREMENT PRIMARY KEY,
    short_code VARCHAR(6) UNIQUE NOT NULL,
    long_url TEXT NOT NULL,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);


⚙️ Compile & Run

Step 1: Open Command Prompt
Press Win + R, type cmd, and press Enter.

Step 2: Navigate to the Project Directory

cd /d D:\URL_Shortner

Step 3: Compile the C++ Program

g++ url_shortener.cpp -o url_shortener -I"D:\URL_Shortner\mysql-connector-c++-9.2.0-winx64\include" -L"D:\URL_Shortner\mysql-connector-c++-9.2.0-winx64\lib64" -lmysqlcppconn

Step 4: Run the Executable

url_shortener.exe

🔗 Contribute & Support
Feel free to contribute by reporting issues or suggesting improvements! 🚀
