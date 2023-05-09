#include <iostream>
#include <Windows.h>
#include <filesystem>
#include <fstream>
#include <thread>
#include <curl/curl.h>

using std::string;

string rootDir("C:\\RCO2Updater");
string rcdir("C:\\RCO2");

static auto WriteCallback(char* ptr, size_t size, size_t nmemb, void* userdata) -> size_t { //Thank you stackoverflow... (https://stackoverflow.com/a/60516083)
    static_cast<string*>(userdata)->append(ptr, size * nmemb);
    return size * nmemb;
}

string curl_get(string host) {
    string data;
    CURL* req3 = curl_easy_init();
    CURLcode res2;
    curl_easy_setopt(req3, CURLOPT_URL, host);
    curl_easy_setopt(req3, CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_2TLS); // add HTTP/2 support for speed gains
    curl_easy_setopt(req3, CURLOPT_SSLVERSION, CURL_SSLVERSION_TLSv1_2); // force TLSv1.2 support as HTTP/2 requires it
    curl_easy_setopt(req3, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(req3, CURLOPT_WRITEDATA, data);
    res2 = curl_easy_perform(req3);
    curl_easy_cleanup(req3);
    return data;
}

void write(string filepath, string content) {
    std::ofstream stream;
    stream.open(filepath);
    stream << content;
    stream.close();
}

int main(int argc, char** argv) {
    string programver = curl_get("https://raw.githubusercontent.com/fheahdythdr/rco-but-it-uses-different-fflags/main/programversion.rco");
    FILE* file;
    if (fopen_s(&file, (rcdir + "\\RCO.exe").c_str(), "wb") != 0) {
        std::cout << "Could not open filepoint... | 0x1\n";
        std::cin.get();
        return 1;
    }

    CURL* req = curl_easy_init();
    CURLcode res;
    curl_easy_setopt(req, CURLOPT_URL, "https://raw.githubusercontent.com/fheahdythdr/rco-but-it-uses-different-fflags/main/RCO.exe");
    curl_easy_setopt(req, CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_2TLS);
    curl_easy_setopt(req, CURLOPT_SSLVERSION, CURL_SSLVERSION_TLSv1_2);
    curl_easy_setopt(req, CURLOPT_WRITEFUNCTION, NULL);
    curl_easy_setopt(req, CURLOPT_WRITEDATA, file);
    res = curl_easy_perform(req);
    if (res != CURLE_OK) {
        std::cout << "NETWORK ERROR | PLEASE CHECK YOUR INTERNET CONNECTION | 0x2\n";
        std::cin.get();
        return 2;
    }
    curl_easy_cleanup(req);

    fclose(file);
    write(rcdir + "\\programversion.rco", programver);
    STARTUPINFOA si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));
    CreateProcessA((rootDir + "\\RCO.exe").c_str(), argv[1], NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
}
