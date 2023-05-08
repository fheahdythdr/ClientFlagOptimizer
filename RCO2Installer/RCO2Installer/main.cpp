#include <iostream>
#include <filesystem>
#include <thread>
#include <curl/curl.h>
#include <windows.h>

int main(int argc, char* argv[]) {
	std::string userIn;
	std::cout << "Welcome to the RCO Installer/Updater!\nRCO is made, owned, and developed by Kaede and L8X\n\nType \"install\" and press enter to continue!\nType \"uninstall\" and press enter to uninstall :(\n\n";
	std::cin >> userIn;

    std::string rootDir("C:\\RCO2");

    if (std::filesystem::exists(rootDir) == false) {
        std::filesystem::create_directory(rootDir);
    }

    if (userIn == std::string("install")) { // Install
        FILE* file;
        if (fopen_s(&file, (rootDir + "\\RCO.exe").c_str(), "wb") != 0) {
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

        if (std::filesystem::exists(rootDir + "\\libcurl.dll") == false) {
            FILE* file2;
            if (fopen_s(&file2, (rootDir + "\\libcurl.dll").c_str(), "wb") != 0) {
                std::cout << "Could not open filepoint... | 0x3\n";
                std::cin.get();
                return 3;
            }
            CURL* req2 = curl_easy_init();
            CURLcode res2;
            curl_easy_setopt(req2, CURLOPT_URL, "https://raw.githubusercontent.com/fheahdythdr/rco-but-it-uses-different-fflags/main/libcurl.dll");
            curl_easy_setopt(req2, CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_2TLS);
            curl_easy_setopt(req2, CURLOPT_SSLVERSION, CURL_SSLVERSION_TLSv1_2);
            curl_easy_setopt(req2, CURLOPT_WRITEFUNCTION, NULL);
            curl_easy_setopt(req2, CURLOPT_WRITEDATA, file2);
            res2 = curl_easy_perform(req2);
            if (res2 != CURLE_OK) {
                std::cout << "NETWORK ERROR | PLEASE CHECK YOUR INTERNET CONNECTION | 0x4\n";
                std::cin.get();
                return 4;
            }
            curl_easy_cleanup(req2);

            fclose(file2);
        }

        if (std::filesystem::exists(rootDir + "\\zlib1.dll") == false) {
            FILE* file2;
            if (fopen_s(&file2, (rootDir + "\\zlib1.dll").c_str(), "wb") != 0) {
                std::cout << "Could not open filepoint... | 0x3\n";
                std::cin.get();
                return 3;
            }
            CURL* req2 = curl_easy_init();
            CURLcode res2;
            curl_easy_setopt(req2, CURLOPT_URL, "https://raw.githubusercontent.com/fheahdythdr/rco-but-it-uses-different-fflags/main/zlib1.dll");
            curl_easy_setopt(req2, CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_2TLS);
            curl_easy_setopt(req2, CURLOPT_SSLVERSION, CURL_SSLVERSION_TLSv1_2);
            curl_easy_setopt(req2, CURLOPT_WRITEFUNCTION, NULL);
            curl_easy_setopt(req2, CURLOPT_WRITEDATA, file2);
            res2 = curl_easy_perform(req2);
            if (res2 != CURLE_OK) {
                std::cout << "NETWORK ERROR | PLEASE CHECK YOUR INTERNET CONNECTION | 0x4\n";
                std::cin.get();
                return 4;
            }
            curl_easy_cleanup(req2);

            fclose(file2);
        }

        HKEY hKey;
        if (RegOpenKeyExA(HKEY_CURRENT_USER, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_ALL_ACCESS, &hKey) == ERROR_SUCCESS) {
            RegSetValueExA(hKey, "RCO2", 0, REG_SZ, (const BYTE*)(rootDir + "\\RCO.exe").c_str(),36);
            RegCloseKey(hKey);
        }
        else {
            std::cout << "Registry error, RCO not added to startup...\n";
        }

        //CreateProcess code from https://stackoverflow.com/a/15440094
        STARTUPINFOA si;
        PROCESS_INFORMATION pi;

        ZeroMemory(&si, sizeof(si));
        si.cb = sizeof(si);
        ZeroMemory(&pi, sizeof(pi));

        CreateProcessA((rootDir + "\\RCO.exe").c_str(), argv[1], NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);

        std::cout << "\nRCO has been successfully installed...\nClosing this installer in 5 seconds...\n\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(5000));
	}
    else if (userIn == std::string("uninstall")) { // Uninstall
        if (argv[0] == (rootDir+"\\RCO2Installer.exe").c_str() || argv[0] == "C:\\RCO2\\RCO2.exe") {
            std::cout << "To uninstall, please run the installer outside of this updater, you can redownload this installer on the github.\nClosing in 5 seconds.\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(5000));
            return 0;
        }

        if (std::filesystem::exists("C:\\RCO2") == true) {
            std::filesystem::remove_all("C:\\RCO2");
        }

        if (std::filesystem::exists(rootDir) == true) {
            std::filesystem::remove_all(rootDir);
        }

        HKEY hKey;
        if (RegOpenKeyExA(HKEY_CURRENT_USER, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_ALL_ACCESS, &hKey) == ERROR_SUCCESS) {
            RegDeleteValueA(hKey, "RCO2");
        }
        else {
            std::cout << "Registry error, RCO startup regkey not removed...\n";
        }
        std::cout << "\nRCO has been successfully uninstalled...\nClosing this installer in 5 seconds...\n\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(5000));
	}
    return 0;
}
