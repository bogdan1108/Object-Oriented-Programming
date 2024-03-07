#ifndef SONG_EXCEPTION_H
#define SONG_EXCEPTION_H
#pragma once
#include <exception>
#include <string>


class song_exception
{
public:
    explicit song_exception(const std::string& description);

    const char* what() const noexcept;
private:
    std::string errorDescription;
};

#endif // SONG_EXCEPTION_H
