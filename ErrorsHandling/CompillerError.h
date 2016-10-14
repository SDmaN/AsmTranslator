#ifndef COMPILLERERROR_H
#define COMPILLERERROR_H

// Коды ошибок
enum CompillerError
{
    NoError = 1,
    Unknown = 2,
    IncorrectSymbol = 4,
    CommandNotFound = 8,
    TooManyArguments = 16,
    TooFewArguments = 32,
    ArgumentIncorrect = 64,
    LabelNotFound = 128,
    LabelAlreadyDefined = 256,
    IpNotSet = 512
};

#endif //COMPILLERERROR_H
