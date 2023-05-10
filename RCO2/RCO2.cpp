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

bool isConsoleHidden = false;
bool isRcoEnabled = false;

std::string rootDir("C:\\RCO2");
string updDir("C:\\RCO2Updater");
string robloxVersionFolder;
string localRobloxVersionFolder;

// original: https://roblox-client-optimizer.simulhost.com/ClientAppSettings.json
std::string host = "https://raw.githubusercontent.com/fheahdythdr/rco-but-it-uses-different-fflags/main/ClientAppSettings.json";
std::string oldhost;

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

char* buf = nullptr;
size_t sz = 0;

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
HWND consoleWindow = GetConsoleWindow();

//Tray icon code from stackoverflow and various other internet sources, I was unsure on how it worked.
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
LPCWSTR lpszClass = L"__hidden__";

int traySystem() {
    HINSTANCE hInstance = GetModuleHandle(nullptr);

    WNDCLASS wc;
    HWND hWnd;
    MSG msg;

    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hbrBackground = nullptr;
    wc.hCursor = nullptr;
    wc.hIcon = nullptr;
    wc.hInstance = hInstance;
    wc.lpfnWndProc = WndProc;
    wc.lpszClassName = lpszClass;
    wc.lpszMenuName = nullptr;
    wc.style = 0;
    RegisterClass(&wc);

    hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, nullptr, nullptr, hInstance, nullptr);

    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return static_cast<int>(msg.wParam);
}

void SetHost() {
    std::ifstream ifs(rootDir + "\\custom_url.txt");;
    if (ifs) {
        std::string contents((std::istreambuf_iterator<char>(ifs)),
            (std::istreambuf_iterator<char>()));
        if (contents != host) {
            oldhost = host;
            host = contents;
        }
    }
};

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {
    static NOTIFYICONDATA nid;
    std::ofstream isHiddenFile;

    switch (iMsg) {
    case WM_CREATE:
        std::memset(&nid, 0, sizeof(nid));
        nid.cbSize = sizeof(nid);
        nid.hWnd = hWnd;
        nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP | NIF_INFO;
        nid.uCallbackMessage = WM_APP + 1;
        nid.hIcon = (HICON)LoadImageA(NULL, (rootDir + "\\animegirl.ico").c_str(), IMAGE_ICON, 0, 0, LR_LOADFROMFILE | LR_SHARED);
        memcpy_s(nid.szTip, sizeof(nid.szTip), L"RCO <3\nClick to toggle console", sizeof(wchar_t[31]));
        Shell_NotifyIcon(NIM_ADD, &nid);
        return 0;
    case WM_APP + 1:
        switch (lParam) {
        case WM_LBUTTONDBLCLK:
            if (isConsoleHidden) {
                ShowWindow(consoleWindow, SW_SHOW);
                isConsoleHidden = false;
                isHiddenFile.open(rootDir + "\\isHidden.rco");
                isHiddenFile << "f";
                isHiddenFile.close();
            }
            else {
                ShowWindow(consoleWindow, SW_HIDE);
                isConsoleHidden = true;
                isHiddenFile.open(rootDir + "\\isHidden.rco");
                isHiddenFile << "t";
                isHiddenFile.close();
            }
            break;
        case WM_LBUTTONDOWN:
            if (isConsoleHidden) {
                ShowWindow(consoleWindow, SW_SHOW);
                isConsoleHidden = false;
                isHiddenFile.open(rootDir + "\\isHidden.rco");
                isHiddenFile << "f";
                isHiddenFile.close();
            }
            else {
                ShowWindow(consoleWindow, SW_HIDE);
                isConsoleHidden = true;
                isHiddenFile.open(rootDir + "\\isHidden.rco");
                isHiddenFile << "t";
                isHiddenFile.close();
            }
            break;
        }
        break;
    case WM_DESTROY:
        Shell_NotifyIcon(NIM_DELETE, &nid);
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hWnd, iMsg, wParam, lParam);
}

void printMainText() {
    system("cls");
    std::cout << "Roblox Client Optimizer coded by Kaede | FFlag list maintained by L8X | Modified by Tanki\n\nRCO is currently: ";
    if (isRcoEnabled) {
        SetConsoleTextAttribute(hConsole, 10);
        std::cout << "Enabled";
        SetConsoleTextAttribute(hConsole, 7);
        std::cout << "\nPress enter to ";
        SetConsoleTextAttribute(hConsole, 12);
        std::cout << "Disable";
        SetConsoleTextAttribute(hConsole, 7);
        std::cout << " RCO.\n\n";
    }
    else {
        SetConsoleTextAttribute(hConsole, 12);
        std::cout << "Disabled";
        SetConsoleTextAttribute(hConsole, 7);
        std::cout << "\nPress enter to ";
        SetConsoleTextAttribute(hConsole, 10);
        std::cout << "Enable";
        SetConsoleTextAttribute(hConsole, 7);
        std::cout << " RCO.\n\n";
    }

    SetConsoleTextAttribute(hConsole, 6);
    std::cout << "This window can be hidden via the RCO tray icon!\nYou can ";
    SetConsoleTextAttribute(hConsole, 12);
    std::cout << "close";
    SetConsoleTextAttribute(hConsole, 6);
    std::cout << " RCO with ALT+F4 or any other similar method.\n";
    SetConsoleTextAttribute(hConsole, 7);
}

void SetURLThread() {
    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        SetHost();
        std::string robloxVersionStr;
        CURL* req = curl_easy_init();
        CURLcode res;
        curl_easy_setopt(req, CURLOPT_URL, "https://setup.rbxcdn.com/version"); // an actually secure version endpoint...
        curl_easy_setopt(req, CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_2TLS); // add HTTP/2 support for speed gains
        curl_easy_setopt(req, CURLOPT_SSLVERSION, CURL_SSLVERSION_TLSv1_2); // force TLSv1.2 support as HTTP/2 requires it
        curl_easy_setopt(req, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(req, CURLOPT_WRITEDATA, &robloxVersionStr);
        res = curl_easy_perform(req);
        if (res != CURLE_OK) {
            std::cout << "\nNETWORK ERROR | PLEASE CHECK YOUR INTERNET CONNECTION | TRYING AGAIN IN 30 SECONDS. | 0x5\n";
            curl_easy_cleanup(req);
            std::this_thread::sleep_for(std::chrono::milliseconds(30000));
            printMainText();
            continue;
        }
        curl_easy_cleanup(req);
        if (std::filesystem::exists(robloxVersionFolder + "\\" + robloxVersionStr) == false) {
            for (const auto& e : std::filesystem::directory_iterator(robloxVersionFolder)) {
                if (e.is_directory()) {
                    for (const auto& e2 : std::filesystem::directory_iterator(e)) {
                        if (e2.path().string().ends_with("COPYRIGHT.txt")) {
                            robloxVersionStr = e.path().string().erase(0, robloxVersionFolder.length() + 1);
                            goto exitNest;
                        }
                    }
                }
            }
        }
        exitNest:
        if (oldhost != host) { //We need to do an update!!!!
            if (std::filesystem::exists(robloxVersionFolder + "\\" + robloxVersionStr + "\\ClientSettings") == false) {
                std::filesystem::create_directory(robloxVersionFolder + "\\" + robloxVersionStr + "\\ClientSettings");
            }

            std::string latestFflagList;
            CURL* req3 = curl_easy_init();
            CURLcode res2;
            curl_easy_setopt(req3, CURLOPT_URL, host);
            curl_easy_setopt(req3, CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_2TLS); // add HTTP/2 support for speed gains
            curl_easy_setopt(req3, CURLOPT_SSLVERSION, CURL_SSLVERSION_TLSv1_2); // force TLSv1.2 support as HTTP/2 requires it
            curl_easy_setopt(req3, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(req3, CURLOPT_WRITEDATA, &latestFflagList);
            res2 = curl_easy_perform(req3);
            if (res2 != CURLE_OK) {
                std::cout << "\nNETWORK ERROR | PLEASE CHECK YOUR INTERNET CONNECTION | TRYING AGAIN IN 30 SECONDS. | 0x8\n";
                curl_easy_cleanup(req3);
                std::this_thread::sleep_for(std::chrono::milliseconds(30000));
                printMainText();
                continue;
            }
            curl_easy_cleanup(req3);

            std::ofstream fflagList;
            fflagList.open(robloxVersionFolder + "\\" + robloxVersionStr + "\\ClientSettings\\ClientAppSettings.json");
            fflagList << latestFflagList;
            fflagList.close();
        }
    }
}

void mainThread() {
    while (true) {
        while (!isRcoEnabled) {
            std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        }
        //Bit of error checking
        std::string robloxVersionStr;
        CURL* req = curl_easy_init();
        CURLcode res;
        curl_easy_setopt(req, CURLOPT_URL, "https://setup.rbxcdn.com/version"); // an actually secure version endpoint...
        curl_easy_setopt(req, CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_2TLS); // add HTTP/2 support for speed gains
        curl_easy_setopt(req, CURLOPT_SSLVERSION, CURL_SSLVERSION_TLSv1_2); // force TLSv1.2 support as HTTP/2 requires it
        curl_easy_setopt(req, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(req, CURLOPT_WRITEDATA, &robloxVersionStr);
        res = curl_easy_perform(req);
        if (res != CURLE_OK) {
            std::cout << "\nNETWORK ERROR | PLEASE CHECK YOUR INTERNET CONNECTION | TRYING AGAIN IN 30 SECONDS. | 0x5\n";
            curl_easy_cleanup(req);
            std::this_thread::sleep_for(std::chrono::milliseconds(30000));
            printMainText();
            continue;
        }
        curl_easy_cleanup(req);
        if (std::filesystem::exists(robloxVersionFolder + "\\" + robloxVersionStr) == false) {
            for (const auto& e : std::filesystem::directory_iterator(robloxVersionFolder)) {
                if (e.is_directory()) {
                    for (const auto& e2 : std::filesystem::directory_iterator(e)) {
                        if (e2.path().string().ends_with("COPYRIGHT.txt")) {
                            robloxVersionStr = e.path().string().erase(0,robloxVersionFolder.length()+1);
                            goto exitNest;
                        }
                    }
                }
            }
        }
        exitNest:
        //Okay! Lets see if the flag list needs to be updated...
        string storedFflagVersion;

        std::ifstream flagVersionFile(rootDir + "\\flagversion.rco");
        flagVersionFile.seekg(0, std::ios::end);
        size_t size = flagVersionFile.tellg();
        string buffer(size, ' ');
        flagVersionFile.seekg(0);
        flagVersionFile.read(&buffer[0], size);
        storedFflagVersion = buffer;
        flagVersionFile.close();

        std::string latestFflagVersion;
        CURL* req2 = curl_easy_init();
        CURLcode res2;
        curl_easy_setopt(req2, CURLOPT_URL, "https://raw.githubusercontent.com/fheahdythdr/rco-but-it-uses-different-fflags/main/flagversion.rco");
        curl_easy_setopt(req2, CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_2TLS); // add HTTP/2 support for speed gains
        curl_easy_setopt(req2, CURLOPT_SSLVERSION, CURL_SSLVERSION_TLSv1_2); // force TLSv1.2 support as HTTP/2 requires it
        curl_easy_setopt(req2, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(req2, CURLOPT_WRITEDATA, &latestFflagVersion);
        res2 = curl_easy_perform(req2);
        if (res2 != CURLE_OK) {
            std::cout << "\nNETWORK ERROR | PLEASE CHECK YOUR INTERNET CONNECTION | TRYING AGAIN IN 30 SECONDS. | 0x7\n";
            curl_easy_cleanup(req2);
            std::this_thread::sleep_for(std::chrono::milliseconds(30000));
            printMainText();
            continue;
        }
        curl_easy_cleanup(req2);

        if (storedFflagVersion != (latestFflagVersion + ' ') || std::filesystem::exists(robloxVersionFolder + "\\" + robloxVersionStr + "\\ClientSettings\\ClientAppSettings.json") == false || oldhost != host) { //We need to do an update!!!!
            if (std::filesystem::exists(robloxVersionFolder + "\\" + robloxVersionStr + "\\ClientSettings") == false) {
                std::filesystem::create_directory(robloxVersionFolder + "\\" + robloxVersionStr + "\\ClientSettings");
            }

            std::string latestFflagList;
            CURL* req3 = curl_easy_init();
            CURLcode res2;
            curl_easy_setopt(req3, CURLOPT_URL, host);
            curl_easy_setopt(req3, CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_2TLS); // add HTTP/2 support for speed gains
            curl_easy_setopt(req3, CURLOPT_SSLVERSION, CURL_SSLVERSION_TLSv1_2); // force TLSv1.2 support as HTTP/2 requires it
            curl_easy_setopt(req3, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(req3, CURLOPT_WRITEDATA, &latestFflagList);
            res2 = curl_easy_perform(req3);
            if (res2 != CURLE_OK) {
                std::cout << "\nNETWORK ERROR | PLEASE CHECK YOUR INTERNET CONNECTION | TRYING AGAIN IN 30 SECONDS. | 0x8\n";
                curl_easy_cleanup(req3);
                std::this_thread::sleep_for(std::chrono::milliseconds(30000));
                printMainText();
                continue;
            }
            curl_easy_cleanup(req3);

            std::ofstream fflagList;
            fflagList.open(robloxVersionFolder + "\\" + robloxVersionStr + "\\ClientSettings\\ClientAppSettings.json");
            fflagList << latestFflagList;
            fflagList.close();

            //Update the flag version file since we just updated the flags!
            std::ofstream flagversion;
            flagversion.open(rootDir + "\\flagversion.rco");
            flagversion << latestFflagVersion;
            flagversion.close();
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(30000)); //We check for fflag updates every 30 seconds.
    }
}

int main(int argc, char** argv) {
    SetHost();
    //Preinit
    SetConsoleTitle(L"Roblox Client Optimizer");

    if (!(_dupenv_s(&buf, &sz, "localappdata") == 0 && buf != nullptr)) {
        std::cout << "Error finding LocalAppData folder | 0xB\n";
        std::cin.get();
        return 11;
    }

    localRobloxVersionFolder = buf + string("\\Roblox\\Versions");
    robloxVersionFolder = string("C:\\Program Files (x86)\\Roblox\\Versions");
    free(buf);

    if (std::filesystem::exists(rootDir) == false) {
        std::cout << "Could not find proper RCO files, please reinstall RCO | 0x1\n";
        std::cin.get();
        return 1;
    }

    const string rcoVersionConstant = "2.0.8";

    std::ofstream rcoVerFile;
    rcoVerFile.open(rootDir + "\\programversion.rco");
    rcoVerFile << rcoVersionConstant;
    rcoVerFile.close();

    if (std::filesystem::exists(rootDir + "\\animegirl.ico") == false) {
        FILE* file;
        if (fopen_s(&file, (rootDir + "\\animegirl.ico").c_str(), "wb") != 0) {
            std::cout << "Could not open filepoint... | 0x2\n";
            std::cin.get();
            return 2;
        }

        CURL* req = curl_easy_init();
        CURLcode res;
        curl_easy_setopt(req, CURLOPT_URL, "https://raw.githubusercontent.com/fheahdythdr/rco-but-it-uses-different-fflags/main/animegirl.ico");
        curl_easy_setopt(req, CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_2TLS); // add HTTP/2 support for speed gains
        curl_easy_setopt(req, CURLOPT_SSLVERSION, CURL_SSLVERSION_TLSv1_2); // force TLSv1.2 support as HTTP/2 requires it
        curl_easy_setopt(req, CURLOPT_WRITEFUNCTION, NULL);
        curl_easy_setopt(req, CURLOPT_WRITEDATA, file);
        res = curl_easy_perform(req);
        if (res != CURLE_OK) {
            std::cout << "NETWORK ERROR | PLEASE CHECK YOUR INTERNET CONNECTION | 0x4 | ERROR DOWNLOADING ICON\n";
            std::cin.get();
            return 4;
        }
        curl_easy_cleanup(req);

        fclose(file);
    }

    if (std::filesystem::exists(rootDir + "\\flagversion.rco") == false) {
        std::ofstream flagversion;
        flagversion.open(rootDir + "\\flagversion.rco");
        flagversion << "0";
        flagversion.close();
    }

    if (std::filesystem::exists(rootDir + "\\isHidden.rco") == false) {
        std::ofstream isHiddenFile;
        isHiddenFile.open(rootDir + "\\isHidden.rco");
        isHiddenFile << "f";
        isHiddenFile.close();
    }

    if (std::filesystem::exists(rootDir + "\\isEnabled.rco") == false) {
        std::ofstream isEnabledFile;
        isEnabledFile.open(rootDir + "\\isEnabled.rco");
        isEnabledFile << "f";
        isEnabledFile.close();
    }

    //Check for program updates
    string storedRcoVersion;

    std::ifstream rcoVersionFile(rootDir + "\\programversion.rco");
    rcoVersionFile.seekg(0, std::ios::end);
    size_t size = rcoVersionFile.tellg();
    string buffer(size, ' ');
    rcoVersionFile.seekg(0);
    rcoVersionFile.read(&buffer[0], size);
    storedRcoVersion = buffer;
    rcoVersionFile.close();

    std::string rcoVersionStr;
    string curver = rcoVersionConstant;
    CURL* reqUpd = curl_easy_init();
    CURLcode resUpd;
    curl_easy_setopt(reqUpd, CURLOPT_URL, "https://raw.githubusercontent.com/fheahdythdr/rco-but-it-uses-different-fflags/main/programversion.rco");
    curl_easy_setopt(reqUpd, CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_2TLS); // add HTTP/2 support for speed gains
    curl_easy_setopt(reqUpd, CURLOPT_SSLVERSION, CURL_SSLVERSION_TLSv1_2); // force TLSv1.2 support as HTTP/2 requires it
    curl_easy_setopt(reqUpd, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(reqUpd, CURLOPT_WRITEDATA, &rcoVersionStr);
    resUpd = curl_easy_perform(reqUpd);
    if (resUpd != CURLE_OK) {
        curl_easy_cleanup(reqUpd);
        std::cout << "\nNETWORK ERROR | FAILED TO CHECK FOR PROGRAM UPDATES | 0xC | RCO can still continue, but you may encounter issues, press enter to continue anyways...\n";
        std::cin.get();
        goto skipUpdate;
    }
    curl_easy_cleanup(reqUpd);
    
    if (rtrim(rcoVersionStr) != rtrim(curver)) {
        std::cout << rtrim(rcoVersionStr) + " " + rtrim(curver);
        STARTUPINFOA si;
        PROCESS_INFORMATION pi;

        ZeroMemory(&si, sizeof(si));
        si.cb = sizeof(si);
        ZeroMemory(&pi, sizeof(pi));
        CreateProcessA((updDir + "\\RCO-Updater.exe").c_str(), argv[1], NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
        exit(0);
    }
    skipUpdate:

    if (std::filesystem::exists(robloxVersionFolder) == true && std::filesystem::exists(localRobloxVersionFolder) == true) {
        std::cout << "Detected two Roblox installs at once, please delete either " + robloxVersionFolder + " or " + localRobloxVersionFolder;
        std::cin.get();
        return 30;
    }

    if (std::filesystem::exists(robloxVersionFolder) == false && std::filesystem::exists(localRobloxVersionFolder) == false) {
        std::cout << "Roblox not found. Please reinstall Roblox | 0x3\n";
        std::cin.get();
        return 3;
    }

    if (std::filesystem::exists(robloxVersionFolder) == false) {
        robloxVersionFolder = localRobloxVersionFolder;
    }


    //Initialize the tray icon system
    std::thread t1(traySystem);

    //Set Hidden and Enabled based on saved file
    std::ifstream hiddenFile(rootDir + "\\isHidden.rco");
    hiddenFile.seekg(0, std::ios::end);
    size = hiddenFile.tellg();
    buffer = string(size, ' ');
    hiddenFile.seekg(0);
    hiddenFile.read(&buffer[0], size);
    if (buffer == "t") {
        isConsoleHidden = true;
    }
    hiddenFile.close();

    std::ifstream enabledFile(rootDir + "\\isEnabled.rco");
    enabledFile.seekg(0, std::ios::end);
    size = enabledFile.tellg();
    buffer = string(size, ' ');
    enabledFile.seekg(0);
    enabledFile.read(&buffer[0], size);
    if (buffer == "t") {
        isRcoEnabled = true;
    }
    enabledFile.close();

    //Handle Hidden Value
    if (isConsoleHidden) {
        ShowWindow(consoleWindow, SW_HIDE);
    }
    else {
        ShowWindow(consoleWindow, SW_SHOW);
    }

    SetWindowLong(consoleWindow, GWL_STYLE, GetWindowLong(consoleWindow, GWL_STYLE) & ~WS_MINIMIZEBOX);
    SetWindowLong(consoleWindow, GWL_STYLE, GetWindowLong(consoleWindow, GWL_STYLE) & ~WS_MAXIMIZEBOX);
    EnableMenuItem(GetSystemMenu(consoleWindow, FALSE), SC_CLOSE, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);

    //Call the main fflag updating thread
    std::thread t2(mainThread);

    // Call the host updating thread
    std::thread t3(SetURLThread);

    //Input loop
    while (true) {
        printMainText();
        string t; //Throwaway
        std::getline(std::cin, t);

        isRcoEnabled = !isRcoEnabled;
        std::ofstream isEnabledFile;
        isEnabledFile.open(rootDir + "\\isEnabled.rco");
        if (isRcoEnabled) {
            isEnabledFile << "t";
        }
        else {
            isEnabledFile << "f";
            std::string robloxVersionStr;
            CURL* req = curl_easy_init();
            CURLcode res;
            curl_easy_setopt(req, CURLOPT_URL, "https://setup.rbxcdn.com/version"); // an actually secure version endpoint...
            curl_easy_setopt(req, CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_2TLS); // add HTTP/2 support for speed gains
            curl_easy_setopt(req, CURLOPT_SSLVERSION, CURL_SSLVERSION_TLSv1_2); // force TLSv1.2 support as HTTP/2 requires it
            curl_easy_setopt(req, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(req, CURLOPT_WRITEDATA, &robloxVersionStr);
            res = curl_easy_perform(req);
            if (res != CURLE_OK) {
                if (std::filesystem::exists(robloxVersionFolder) == true)
                    std::cout << "\nNETWORK ERROR | FAILED TO REMOVE FFLAG LIST, DELETE MANUALLY AT " + robloxVersionFolder + "\\current-roblox-version\\ClientSettings\\ClientAppSettings.json | 0x9\n";
            }
            curl_easy_cleanup(req);
            if (std::filesystem::exists(robloxVersionFolder + "\\" + robloxVersionStr + "\\ClientSettings\\ClientAppSettings.json") == true) {
                remove((robloxVersionFolder + "\\" + robloxVersionStr + "\\ClientSettings\\ClientAppSettings.json").c_str());
            }
        }
        isEnabledFile.close();
    }
}
