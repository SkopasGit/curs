#ifndef CHATSERVER_H
#define CHATSERVER_H

#include "ChatBase.h"
#include <functional>
#include <thread>
// Derived class for server chat
class ChatServer : public ChatBase {
private:
std::vector<std::thread> clientThreads;

protected:

void ConfirmConctWithClient();
virtual void Chat(SOCKET ClientConn);

public:
    ChatServer(const char* ip, short port);
    void Run() override;
};
/// @brief /////////////////////////////////////////////////////////////
class ChoiseTask:public ChatServer
{
private:
vector<int> dataClientInt;
vector<char> dataClientChar;
vector<double> dataClientDoble; 


//task 1
std::vector<char> NameSurname(const std::vector<char>&,const std::vector<int>&,const std::vector<double>&);
//task2
std::vector<char> SumOfNambers(const std::vector<char>&,const std::vector<int>&,const std::vector<double>&);

//task3
std::vector<char> MultipyOfNambers(const std::vector<char>&,const std::vector<int>&,const std::vector<double>&);
//std::vector<char> SumOfNambers(const vector<double>& dataBuffer);
// task4
std::vector<char> MaxElementArray(const std::vector<char>&,const std::vector<int>&,const std::vector<double>&);
// task5
std::vector<char> MaxNubers(const std::vector<char>&,const std::vector<int>&,const std::vector<double>&);
std::vector<char> Poliander(const std::vector<char>&,const std::vector<int>&,const std::vector<double>&);
std::vector<char> SortArrayUp(const std::vector<char>&,const std::vector<int>&,const std::vector<double>&);
std::vector<char> CountLetterA(const std::vector<char> &dataChar, const std::vector<int> &dataInt, const std::vector<double> &dataDouble);
    std::vector<char> SendZeros(const std::vector<char> &dataChar, const std::vector<int> &dataInt, const std::vector<double> &dataDouble);
    std::vector<char> CheckDigits(const std::vector<char> &dataChar, const std::vector<int> &dataInt, const std::vector<double> &dataDouble);
    std::vector<char> AddName(const std::vector<char> &dataChar, const std::vector<int> &dataInt, const std::vector<double> &dataDouble);
    std::vector<char> SumThreeNumbers(const std::vector<char> &dataChar, const std::vector<int> &dataInt, const std::vector<double> &dataDouble);
    std::vector<char> ProductNegativeNumbers(const std::vector<char> &dataChar, const std::vector<int> &dataInt, const std::vector<double> &dataDouble);
    std::vector<char> MinMaxElements(const std::vector<char> &dataChar, const std::vector<int> &dataInt, const std::vector<double> &dataDouble);
    std::vector<char> AddAverageToNumbers(const std::vector<char> &dataChar, const std::vector<int> &dataInt, const std::vector<double> &dataDouble);
    std::vector<char> CheckPrime(const std::vector<char> &dataChar, const std::vector<int> &dataInt, const std::vector<double> &dataDouble);
    std::vector<char> SortArrayDescending(const std::vector<char> &dataChar, const std::vector<int> &dataInt, const std::vector<double> &dataDouble);
    std::vector<char> CountSpaces(const std::vector<char> &dataChar, const std::vector<int> &dataInt, const std::vector<double> &dataDouble);
    std::vector<char> SendXs(const std::vector<char> &dataChar, const std::vector<int> &dataInt, const std::vector<double> &dataDouble);
    std::vector<char> CheckSpaces(const std::vector<char> &dataChar, const std::vector<int> &dataInt, const std::vector<double> &dataDouble);
    std::vector<char> FactorizeNumber(const std::vector<char> &dataChar, const std::vector<int> &dataInt, const std::vector<double> &dataDouble);
    std::vector<char> CheckPerfectSquare(const std::vector<char> &dataChar, const std::vector<int> &dataInt, const std::vector<double> &dataDouble);
    std::vector<char> ReplaceNegativesWithZero(const std::vector<char> &dataChar, const std::vector<int> &dataInt, const std::vector<double> &dataDouble);
    std::vector<char> CountVowels(const std::vector<char> &dataChar, const std::vector<int> &dataInt, const std::vector<double> &dataDouble);
    std::vector<char> SendRandomNumbers(const std::vector<char> &dataChar, const std::vector<int> &dataInt, const std::vector<double> &dataDouble);
    std::vector<char> CheckPunctuation(const std::vector<char> &dataChar, const std::vector<int> &dataInt, const std::vector<double> &dataDouble);
    std::vector<char> FactorialOfNumber(const std::vector<char> &dataChar, const std::vector<int> &dataInt, const std::vector<double> &dataDouble);
    std::vector<char> ConvertUppercase(const std::vector<char> &dataChar, const std::vector<int> &dataInt, const std::vector<double> &dataDouble);
    std::vector<char> SumAndSend(const std::vector<char> &dataChar, const std::vector<int> &dataInt, const std::vector<double> &dataDouble);
void ParseUserData(const vector<char>& dataBufer);
protected:
void Chat(SOCKET ClientConn) override;

void BaseFunctionOptions(SOCKET ClientConn,string queeryClient,const std::function<vector<char> (const std::vector<char>&,const std::vector<int>&,const std::vector<double>&)>& func);


bool AnaliticAnswer(SOCKET ClientConn,vector<char>& dataBuffer);
    
public:
     ChoiseTask(const char* ip, short port);
   
};

#endif // CHATSERVER_H
