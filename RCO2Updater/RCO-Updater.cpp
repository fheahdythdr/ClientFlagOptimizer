#include <iostream>
#include <Windows.h>
#include <filesystem>
#include <fstream>
#include <thread>
#include <curl/curl.h>

// thanks stackoverflow https://stackoverflow.com/questions/216823/how-to-trim-an-stdstring

const char* ws = " \t\n\r\f\v";

// trim from end of string (right)
inline std::string& rtrim(std::string& s, const char* t = ws)
{
    s.erase(s.find_last_not_of(t) + 1);
    return s;
}

using std::string;

string rootDir("C:\\RCO2Updater");
string rcdir("C:\\RCO2");

static auto WriteCallback(char* ptr, size_t size, size_t nmemb, void* userdata) -> size_t { //Thank you stackoverflow... (https://stackoverflow.com/a/60516083)
    static_cast<string*>(userdata)->append(ptr, size * nmemb);
    return size * nmemb;
}

int main(int argc, char** argv) {
    string programver;
    CURL* req = curl_easy_init();
    CURLcode res;
    curl_easy_setopt(req, CURLOPT_URL, "https://raw.githubusercontent.com/fheahdythdr/rco-but-it-uses-different-fflags/main/programversion.rco");
    curl_easy_setopt(req, CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_2TLS);
    curl_easy_setopt(req, CURLOPT_SSLVERSION, CURL_SSLVERSION_TLSv1_2);
    curl_easy_setopt(req, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(req, CURLOPT_WRITEDATA, &programver);
    res = curl_easy_perform(req);
    if (res != CURLE_OK) {
        std::cout << "NETWORK ERROR | PLEASE CHECK YOUR INTERNET CONNECTION | 0x2\n";
        std::cin.get();
        curl_easy_cleanup(req);
        return 2;
    }
    curl_easy_cleanup(req);
    FILE* file;
    if (fopen_s(&file, (rcdir + "\\RCO.exe").c_str(), "wb") != 0) {
        std::cout << "Could not open filepoint... | 0x1\n";
        std::cin.get();
        return 2;
    }

    CURL* req2 = curl_easy_init();
    CURLcode res2;
    curl_easy_setopt(req2, CURLOPT_URL, "https://raw.githubusercontent.com/fheahdythdr/rco-but-it-uses-different-fflags/main/RCO.exe");
    curl_easy_setopt(req2, CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_2TLS);
    curl_easy_setopt(req2, CURLOPT_SSLVERSION, CURL_SSLVERSION_TLSv1_2);
    curl_easy_setopt(req2, CURLOPT_WRITEFUNCTION, NULL);
    curl_easy_setopt(req2, CURLOPT_WRITEDATA, file);
    res2 = curl_easy_perform(req2);
    if (res != CURLE_OK) {
        std::cout << "NETWORK ERROR | PLEASE CHECK YOUR INTERNET CONNECTION | 0x2\n";
        std::cin.get();
        return 2;
    }
    curl_easy_cleanup(req2);

    fclose(file);
    std::ofstream stream;
    stream.open(rcdir + "\\programversion.rco");
    stream << rtrim(programver);
    stream.close();
    std::this_thread::sleep_for(std::chrono::milliseconds(2000)); 
    STARTUPINFOA si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));
    CreateProcessA((rcdir + "\\RCO.exe").c_str(), argv[1] , NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    exit(0);
}
