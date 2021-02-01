#include "CorsikaConfig.h"

#include <string>
#include <cstring>
#include <stdexcept>


CorsikaConfig::CorsikaConfig()
    : mFilename(std::string())
    , mThinning(CorsikaOption::UNKNOWN)
    , mCurved(CorsikaOption::UNKNOWN)
    , mSlant(CorsikaOption::UNKNOWN)
    , mStackinput(CorsikaOption::UNKNOWN)
    , mPreshower(CorsikaOption::UNKNOWN)
{
    // nothing
}


CorsikaConfig::CorsikaConfig(
        const char * filename, const int strlen, const bool thinning,
        const bool curved, const bool slant, const bool stackinput,
        const bool preshower) {
    setFilename(filename, strlen);
    setThinning(thinning);
    setCurved(curved);
    setSlant(slant);
    setStackinput(stackinput);
    setPreshower(preshower);
}


void CorsikaConfig::setFilename(const char * filename) {
    setFilename(filename, std::strlen(filename));
}

void CorsikaConfig::setFilename(const char * filename, const int strlen) {
    if (filename == nullptr) {
        throw std::runtime_error("CORSIKA filename is nullptr");
    }

    if (strlen <= 0) {
        throw std::runtime_error("CORSIKA filename length is invalid");
    }

    // copy string and remove trailing whitespace
    char * temp = new char[strlen+1];
    std::memset(temp, 0, strlen+1);
    std::memcpy(temp, filename, strlen);
    char * end = temp + (strlen-1);
    while(std::isspace(*end)) {
        *end = (char) 0;

        if (end == temp) {
            throw std::runtime_error("CORSIKA filename invalid");
        }

        --end;
    }

    mFilename = std::string(temp);
    delete[] temp;
}


CorsikaConfig::CorsikaOption CorsikaConfig::boolToCorsikaOption(
        const bool val) const {
    CorsikaOption option = CorsikaOption::UNKNOWN;
    if (val) {
        option = CorsikaOption::TRUE;
    }
    else {
        option = CorsikaOption::FALSE;
    }

    return option;
}


void CorsikaConfig::setThinning(const bool val) {
    mThinning = boolToCorsikaOption(val);
}

void CorsikaConfig::setCurved(const bool val) {
    mCurved = boolToCorsikaOption(val);
}

void CorsikaConfig::setSlant(const bool val) {
    mSlant = boolToCorsikaOption(val);
}

void CorsikaConfig::setStackinput(const bool val) {
    mStackinput = boolToCorsikaOption(val);
}

void CorsikaConfig::setPreshower(const bool val) {
    mPreshower = boolToCorsikaOption(val);
}


std::string CorsikaConfig::getFilename() const {
    return mFilename;
}

CorsikaConfig::CorsikaOption CorsikaConfig::getThinning() const {
    return mThinning;
}

CorsikaConfig::CorsikaOption CorsikaConfig::getCurved() const {
    return mCurved;
}

CorsikaConfig::CorsikaOption CorsikaConfig::getSlant() const {
    return mSlant;
}

CorsikaConfig::CorsikaOption CorsikaConfig::getStackinput() const {
    return mStackinput;
}

CorsikaConfig::CorsikaOption CorsikaConfig::getPreshower() const {
    return mPreshower;
}

