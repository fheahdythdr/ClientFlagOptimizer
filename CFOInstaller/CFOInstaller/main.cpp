#include <iostream>
#include <filesystem>
#include <thread>
#include <curl/curl.h>
#include <windows.h>

int main(int argc, char* argv[]) {
	std::string userIn;
	std::cout << "Welcome to the CFO Installer/Updater!\nCFO was originally made by Kaede, now maintained by Tanki.\n\nType \"install\" and press enter to continue!\nType \"uninstall\" and press enter to uninstall :(\n\n";
	std::cin >> userIn;

    std::string rootDir("C:\\CFO");
    std::string updDir("C:\\CFOUpdater");

    if (std::filesystem::exists(updDir) == false) {
        std::filesystem::create_directory(updDir);
    }
    if (std::filesystem::exists(rootDir) == false) {
        std::filesystem::create_directory(rootDir);
    }

    if (userIn == std::string("install")) { // Install
        FILE* file;
        if (fopen_s(&file, (rootDir + "\\CFO.exe").c_str(), "wb") != 0) {
            std::cout << "Could not open filepoint... | 0x1\n";
            std::cin.get();
            return 1;
        }

        CURL* req = curl_easy_init();
        CURLcode res;
        curl_easy_setopt(req, CURLOPT_URL, "https://raw.githubusercontent.com/fheahdythdr/ClientFlagOptimizer/main/CFO.exe");
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

        if (std::filesystem::exists(rootDir + "\\libcurl.dll") == false) {
            FILE* file;
            if (fopen_s(&file, (rootDir + "\\libcurl.dll").c_str(), "wb") != 0) {
                std::cout << "Could not open filepoint... | 0x3\n";
                std::cin.get();
                return 1;
            }
            CURL* req = curl_easy_init();
            CURLcode res;
            curl_easy_setopt(req, CURLOPT_URL, "https://raw.githubusercontent.com/fheahdythdr/ClientFlagOptimizer/main/libcurl.dll");
            curl_easy_setopt(req, CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_2TLS);
            curl_easy_setopt(req, CURLOPT_SSLVERSION, CURL_SSLVERSION_TLSv1_2);
            curl_easy_setopt(req, CURLOPT_WRITEFUNCTION, NULL);
            curl_easy_setopt(req, CURLOPT_WRITEDATA, file);
            res = curl_easy_perform(req);
            if (res != CURLE_OK) {
                std::cout << "NETWORK ERROR | PLEASE CHECK YOUR INTERNET CONNECTION | 0x4\n";
                std::cin.get();
                return 2;
            }
            curl_easy_cleanup(req);

            fclose(file);
        }

        if (std::filesystem::exists(updDir + "\\libcurl.dll") == false) {
            FILE* file;
            if (fopen_s(&file, (updDir + "\\libcurl.dll").c_str(), "wb") != 0) {
                std::cout << "Could not open filepoint... | 0x3\n";
                std::cin.get();
                return 1;
            }
            CURL* req = curl_easy_init();
            CURLcode res;
            curl_easy_setopt(req, CURLOPT_URL, "https://raw.githubusercontent.com/fheahdythdr/ClientFlagOptimizer/main/CFOUpdater/libcurl.dll");
            curl_easy_setopt(req, CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_2TLS);
            curl_easy_setopt(req, CURLOPT_SSLVERSION, CURL_SSLVERSION_TLSv1_2);
            curl_easy_setopt(req, CURLOPT_WRITEFUNCTION, NULL);
            curl_easy_setopt(req, CURLOPT_WRITEDATA, file);
            res = curl_easy_perform(req);
            if (res != CURLE_OK) {
                std::cout << "NETWORK ERROR | PLEASE CHECK YOUR INTERNET CONNECTION | 0x4\n";
                std::cin.get();
                return 2;
            }
            curl_easy_cleanup(req);

            fclose(file);
        }

        if (std::filesystem::exists(updDir + "\\zlib1.dll") == false) {
            FILE* file;
            if (fopen_s(&file, (updDir + "\\zlib1.dll").c_str(), "wb") != 0) {
                std::cout << "Could not open filepoint... | 0x3\n";
                std::cin.get();
                return 1;
            }
            CURL* req = curl_easy_init();
            CURLcode res;
            curl_easy_setopt(req, CURLOPT_URL, "https://raw.githubusercontent.com/fheahdythdr/ClientFlagOptimizer/main/CFOUpdater/zlib1.dll");
            curl_easy_setopt(req, CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_2TLS);
            curl_easy_setopt(req, CURLOPT_SSLVERSION, CURL_SSLVERSION_TLSv1_2);
            curl_easy_setopt(req, CURLOPT_WRITEFUNCTION, NULL);
            curl_easy_setopt(req, CURLOPT_WRITEDATA, file);
            res = curl_easy_perform(req);
            if (res != CURLE_OK) {
                std::cout << "NETWORK ERROR | PLEASE CHECK YOUR INTERNET CONNECTION | 0x4\n";
                std::cin.get();
                return 2;
            }
            curl_easy_cleanup(req);

            fclose(file);
        }

        if (std::filesystem::exists(updDir + "\\CFO-Updater.exe") == false) {
            FILE* file;
            if (fopen_s(&file, (updDir + "\\CFO-Updater.exe").c_str(), "wb") != 0) {
                std::cout << "Could not open filepoint... | 0x3\n";
                std::cin.get();
                return 1;
            }
            CURL* req = curl_easy_init();
            CURLcode res;
            curl_easy_setopt(req, CURLOPT_URL, "https://raw.githubusercontent.com/fheahdythdr/ClientFlagOptimizer/main/CFOUpdater.exe");
            curl_easy_setopt(req, CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_2TLS);
            curl_easy_setopt(req, CURLOPT_SSLVERSION, CURL_SSLVERSION_TLSv1_2);
            curl_easy_setopt(req, CURLOPT_WRITEFUNCTION, NULL);
            curl_easy_setopt(req, CURLOPT_WRITEDATA, file);
            res = curl_easy_perform(req);
            if (res != CURLE_OK) {
                std::cout << "NETWORK ERROR | PLEASE CHECK YOUR INTERNET CONNECTION | 0x4\n";
                std::cin.get();
                return 2;
            }
            curl_easy_cleanup(req);

            fclose(file);
        }

        if (std::filesystem::exists(rootDir + "\\zlib1.dll") == false) {
            FILE* file;
            if (fopen_s(&file, (rootDir + "\\zlib1.dll").c_str(), "wb") != 0) {
                std::cout << "Could not open filepoint... | 0x3\n";
                std::cin.get();
                return 1;
            }
            CURL* req = curl_easy_init();
            CURLcode res;
            curl_easy_setopt(req, CURLOPT_URL, "https://raw.githubusercontent.com/fheahdythdr/ClientFlagOptimizer/main/zlib1.dll");
            curl_easy_setopt(req, CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_2TLS);
            curl_easy_setopt(req, CURLOPT_SSLVERSION, CURL_SSLVERSION_TLSv1_2);
            curl_easy_setopt(req, CURLOPT_WRITEFUNCTION, NULL);
            curl_easy_setopt(req, CURLOPT_WRITEDATA, file);
            res = curl_easy_perform(req);
            if (res != CURLE_OK) {
                std::cout << "NETWORK ERROR | PLEASE CHECK YOUR INTERNET CONNECTION | 0x4\n";
                std::cin.get();
                return 2;
            }
            curl_easy_cleanup(req);

            fclose(file);
        }

        HKEY hKey;
        if (RegOpenKeyExA(HKEY_CURRENT_USER, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_ALL_ACCESS, &hKey) == ERROR_SUCCESS) {
            RegSetValueExA(hKey, "CFO", 0, REG_SZ, (const BYTE*)(rootDir + "\\CFO.exe").c_str(),36);
            RegCloseKey(hKey);
        }
        else {
            std::cout << "Registry error, CFO not added to startup...\n";
        }

        //CreateProcess code from https://stackoverflow.com/a/15440094
        STARTUPINFOA si;
        PROCESS_INFORMATION pi;

        ZeroMemory(&si, sizeof(si));
        si.cb = sizeof(si);
        ZeroMemory(&pi, sizeof(pi));
        CreateProcessA((rootDir + "\\CFO.exe").c_str(), argv[1], NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
        exit(0);
	}
    else if (userIn == std::string("uninstall")) { // Uninstall
        if (argv[0] == (rootDir+"\\CFOInstaller.exe").c_str() || argv[0] == "C:\\CFO\\CFO.exe") {
            std::cout << "To uninstall, please run the installer outside of this updater, you can redownload this installer on the github.\nClosing in 5 seconds.\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(5000));
            return 0;
        }

        if (std::filesystem::exists("C:\\CFO") == true) {
            std::filesystem::remove_all("C:\\CFO");
        }

        if (std::filesystem::exists(rootDir) == true) {
            std::filesystem::remove_all(rootDir);
        }

        HKEY hKey;
        if (RegOpenKeyExA(HKEY_CURRENT_USER, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_ALL_ACCESS, &hKey) == ERROR_SUCCESS) {
            RegDeleteValueA(hKey, "CFO");
        }
        else {
            std::cout << "Registry error, CFO startup regkey not removed...\n";
        }
        exit(0);
	}
    exit(0);
}
