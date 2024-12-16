#include "ftpclient.h"
#include <iostream>
#include <sstream>

FTPClient::FTPClient(boost::asio::io_context& io_context, const std::string& host, const std::string& username, const std::string& password)
    : io_context_(io_context), control_socket_(io_context), data_socket_(io_context), host_(host), username_(username), password_(password) {}

bool FTPClient::connect() {
    boost::asio::ip::tcp::resolver resolver(io_context_);
    auto endpoints = resolver.resolve(host_, "21");
    boost::asio::connect(control_socket_, endpoints);

    std::string response;
    if (!sendCommand("USER " + username_, response) || response.substr(0, 3) != "331") return false;
    if (!sendCommand("PASS " + password_, response) || response.substr(0, 3) != "230") return false;
    return true;
}

bool FTPClient::uploadFile(const std::string& localPath, const std::string& remotePath) {
    std::ifstream file(localPath, std::ios::binary);
    if (!file) {
        std::cerr << "Failed to open file: " << localPath << std::endl;
        return false;
    }

    std::string ip;
    unsigned short port;
    if (!enterPassiveMode(ip, port)) return false;

    boost::asio::ip::tcp::endpoint data_endpoint(boost::asio::ip::address::from_string(ip), port);
    data_socket_.connect(data_endpoint);

    std::string response;
    if (!sendCommand("STOR " + remotePath, response) || response.substr(0, 3) != "150") return false;

    std::vector<char> buffer(1024);
    while (file.read(buffer.data(), buffer.size()) || file.gcount() > 0) {
        boost::asio::write(data_socket_, boost::asio::buffer(buffer.data(), file.gcount()));
    }

    data_socket_.close();
    if (!sendCommand("", response) || response.substr(0, 3) != "226") return false;
    return true;
}

bool FTPClient::downloadFile(const std::string& remotePath, const std::string& localPath) {
    std::ofstream file(localPath, std::ios::binary);
    if (!file) {
        std::cerr << "Failed to create file: " << localPath << std::endl;
        return false;
    }

    std::string ip;
    unsigned short port;
    if (!enterPassiveMode(ip, port)) return false;

    boost::asio::ip::tcp::endpoint data_endpoint(boost::asio::ip::address::from_string(ip), port);
    data_socket_.connect(data_endpoint);

    std::string response;
    if (!sendCommand("RETR " + remotePath, response) || response.substr(0, 3) != "150") return false;

    std::vector<char> buffer(1024);
    boost::system::error_code error;
    while (data_socket_.read_some(boost::asio::buffer(buffer), error)) {
        file.write(buffer.data(), buffer.size());
        if (error == boost::asio::error::eof) break;
        else if (error) return false;
    }

    data_socket_.close();
    if (!sendCommand("", response) || response.substr(0, 3) != "226") return false;
    return true;
}

bool FTPClient::sendCommand(const std::string& command, std::string& response) {
    if (!command.empty()) {
        boost::asio::write(control_socket_, boost::asio::buffer(command + "\r\n"));
    }

    response.clear();
    boost::asio::streambuf buffer;
    boost::asio::read_until(control_socket_, buffer, "\r\n");
    std::istream stream(&buffer);
    std::getline(stream, response);
    std::cout << "FTP Response: " << response << std::endl;
    return !response.empty();
}

bool FTPClient::enterPassiveMode(std::string& ip, unsigned short& port) {
    std::string response;
    if (!sendCommand("PASV", response) || response.substr(0, 3) != "227") return false;

    size_t start = response.find('(');
    size_t end = response.find(')', start);
    if (start == std::string::npos || end == std::string::npos) return false;

    std::istringstream iss(response.substr(start + 1, end - start - 1));
    int h1, h2, h3, h4, p1, p2;
    char delim;
    iss >> h1 >> delim >> h2 >> delim >> h3 >> delim >> h4 >> delim >> p1 >> delim >> p2;
    ip = std::to_string(h1) + "." + std::to_string(h2) + "." + std::to_string(h3) + "." + std::to_string(h4);
    port = (p1 << 8) | p2;
    return true;
}
