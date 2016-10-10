#ifndef FILENOTFOUNDEXCEPTION_H
#define FILENOTFOUNDEXCEPTION_H

#include <string>
#include <exception>

// Исключение, выбрасываемое, если не найден файл
class FileNotFoundException : public std::exception
{
public:
    explicit FileNotFoundException(const std::string &message);
    virtual const char *what() const throw() override;

private:
    std::string m_message;
};

#endif //FILENOTFOUNDEXCEPTION_H
