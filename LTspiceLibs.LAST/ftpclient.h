#pragma once
#include <boost/asio.hpp>
#include <fstream>
#include <string>

class FTPClient {
public:
    FTPClient(boost::asio::io_context& io_context, const std::string& host, const std::string& username, const std::string& password);
    bool connect();
    bool uploadFile(const std::string& localPath, const std::string& remotePath);
    bool downloadFile(const std::string& remotePath, const std::string& localPath);

private:
    bool sendCommand(const std::string& command, std::string& response);
    bool enterPassiveMode(std::string& ip, unsigned short& port);

    boost::asio::io_context& io_context_;
    boost::asio::ip::tcp::socket control_socket_;
    boost::asio::ip::tcp::socket data_socket_;
    std::string host_;
    std::string username_;
    std::string password_;
};
