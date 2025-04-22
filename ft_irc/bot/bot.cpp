#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <curl/curl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
    size_t totalSize = size * nmemb;
    output->append((char*)contents, totalSize);
    return totalSize;
}

std::string call_hf_api(const std::string& prompt) {
    CURL* curl = curl_easy_init();
    if (!curl) return "Erreur curl";

    std::string response;
    std::string api_token = "[REDACTED]"; //clé api
    std::string post_fields = "{\"inputs\":\"" + prompt + "\"}";

    struct curl_slist* headers = nullptr;
    headers = curl_slist_append(headers, "Content-Type: application/json");
    headers = curl_slist_append(headers, ("Authorization: Bearer " + api_token).c_str());

    curl_easy_setopt(curl, CURLOPT_URL, "https://api-inference.huggingface.co/models/google/flan-t5-small"); //model que l'on veut utilsier
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_fields.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    CURLcode res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    curl_slist_free_all(headers);

    if (res != CURLE_OK) return "Erreur appel API";
    if (response.empty() || (response[0] != '{' && response[0] != '[')) {
        return "Erreur API : réponse non-JSON reçue";
    }
    try {
        auto j = json::parse(response);
        if (j.is_array() && !j.empty() && j[0].contains("generated_text")) {
            return j[0]["generated_text"].get<std::string>();
        } else if (j.contains("error")) {
            return "Erreur API : " + j["error"].get<std::string>();
        } else {
            return "Erreur API : format JSON inattendu";
        }
    } catch (const std::exception& e) {
        return std::string("Erreur parsing JSON : ") + e.what();
    }
}

std::string clean_response(const std::string& input) {
    std::string output = input;
    std::replace(output.begin(), output.end(), '\n', ' ');
    std::replace(output.begin(), output.end(), '\r', ' ');
    if (output.size() > 400) {
        output = output.substr(0, 397) + "...";
    }
    return output;
}

void send_cmd(int sockfd, const std::string &cmd) {
    send(sockfd, cmd.c_str(), cmd.size(), 0);
}

int main() {
    const char* server = "127.0.0.1";
    const int port = 8080;
    const char* pass = "a";
    const char* nick = "John";
    const char* user = "John Scott 0 * :john scott IRC";
    const char* channel = "#chatbot";

    int sockfd;
    struct sockaddr_in serv_addr;
    struct hostent* server_host;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    server_host = gethostbyname(server);
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    memcpy(&serv_addr.sin_addr.s_addr, server_host->h_addr, server_host->h_length);
    serv_addr.sin_port = htons(port);
    connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

    send_cmd(sockfd, "PASS " + std::string(pass) + "\r\n");
    send_cmd(sockfd, "NICK " + std::string(nick) + "\r\n");
    send_cmd(sockfd, "USER " + std::string(user) + "\r\n");

    char buffer[1024];
    std::string recv_buffer = "";
    bool joined = false;

    while (true) {
        memset(buffer, 0, sizeof(buffer));
        int len = recv(sockfd, buffer, sizeof(buffer) - 1, 0);
        if (len <= 0) break;

        recv_buffer += std::string(buffer, len);

        size_t pos;
        while ((pos = recv_buffer.find("\r\n")) != std::string::npos) {
            std::string line = recv_buffer.substr(0, pos);
            recv_buffer.erase(0, pos + 2);
            //std::cout << ">> " << line << std::endl;

            if (line.substr(0,4) == "PING") {
                send_cmd(sockfd, "PONG " + line.substr(5) + "\r\n");
            }

            if (!joined && line.find(" 001 ") != std::string::npos) {
                send_cmd(sockfd, "JOIN " + std::string(channel) + "\r\n");
                joined = true;
            }

            size_t ask_pos = line.find("!ask");
            if (ask_pos != std::string::npos) {
                std::string question = line.substr(ask_pos + 5);
                question.erase(question.find_last_not_of("\r\n") + 1);

                std::string response = call_hf_api(question);
                response = clean_response(response);
                send_cmd(sockfd, "PRIVMSG " + std::string(channel) + " :" + response + "\r\n");
            }
        }
    }
    close(sockfd);
    return 0;
}