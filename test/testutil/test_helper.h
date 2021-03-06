#ifndef PFW_TEST_HELPER_H
#define PFW_TEST_HELPER_H

#include <cstdio>
#include <fstream>
#include <iostream>

#include <string>
#if defined(_WIN32)
#include <direct.h>
#include <windows.h>
#endif
#include <sys/types.h>
#include <sys/stat.h>
#include <cerrno>

class DummyDirectory {
    std::string path;

public:
    static bool createDirectory(const std::string &dir)
    {
        int nError = 0;
#if defined(_WIN32)
        nError = _mkdir(dir.c_str());
#else
        nError = mkdir(dir.c_str(), 0733);
#endif
        return nError == 0 || errno == EEXIST;
    }

    DummyDirectory(const std::string &path) : path(path) {
        createDirectory(path);
    }

    void rename(const std::string &newPath) {
        std::rename(path.c_str(), newPath.c_str());
        path = newPath;
    }

    ~DummyDirectory() { std::remove(path.c_str()); }
};

class DummyFile {
    std::string path;

public:
    DummyFile(const std::string &path) : path(path) {
        std::ofstream(path.c_str());
    }

    void rename(const std::string &newPath) {
        std::rename(path.c_str(), newPath.c_str());
        path = newPath;
    }

    void modify(const std::string &payload) {
        std::ofstream ofs(path.c_str());
        ofs << payload;
    }

    ~DummyFile() { std::remove(path.c_str()); }
};

#endif
