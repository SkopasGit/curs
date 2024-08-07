#include "ChatServer.h"
#include <sstream>
#include <cctype>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <cstdlib>

ChatServer::ChatServer(const char *ip, short port) : ChatBase(ip, port)
{
    InitializeSocket();
    BindAndListen();
}
bool ChatServer::ConfirmConctWithClient()
{
    sockaddr_in clientInfo;
    ZeroMemory(&clientInfo, sizeof(clientInfo));
    int clientInfo_size = sizeof(clientInfo);

    ClientConn = accept(sock, (sockaddr *)&clientInfo, &clientInfo_size);
    if (ClientConn == INVALID_SOCKET)
    {
        throw runtime_error("Client detected, but failed to connect to client. Error #" + to_string(WSAGetLastError()));
        return false;
    }
    cout << "Connection with client successfully established" << endl;

    char clientIP[22];
    inet_ntop(AF_INET, &clientInfo.sin_addr, clientIP, INET_ADDRSTRLEN);
    cout << "Client connected with IP address " << clientIP << endl;
    return true;
}

void ChatServer::Chat()
{
    while (true)
    {
        int packetSize = ReceiveData(ClientConn, buffer);
        buffer[packetSize] = '\0'; // Null-terminate the string
        cout << "Client message: " << buffer.data() << endl;

        cout << "Your (host) message: ";
        fgets(buffer.data(), buffer.size(), stdin);

        if (buffer[0] == 'x' && buffer[1] == 'x' && buffer[2] == 'x')
        {
            shutdown(ClientConn, SD_BOTH);
            closesocket(ClientConn);
            return;
        }

        SendData(ClientConn, buffer);
    }
}
void ChatServer::Run()
{

    ConfirmConctWithClient();
    Chat();
}
/////////////////////////////////////
ChoiseTask::ChoiseTask(const char *ip, short port) : ChatServer(ip, port) {

                                                     };
void ChoiseTask::ParseUserData(const std::vector<char> &dataBufer)
{
    std::string data(dataBufer.begin(), dataBufer.end());

    // Створити строковий потік
    std::istringstream stream(data);
    std::string token;
    dataClientInt.clear();
    dataClientDoble.clear();
    dataClientChar.clear();

    while (stream >> token)
    {
        // Визначення, чи це число або символ
        bool isNegative = false;
        bool hasDecimalPoint = false;
        bool isNumber = true;

        // Перевірка знаку
        if (!token.empty() && token[0] == '-')
        {
            isNegative = true;
            token = token.substr(1); // Видалити знак мінус
        }

        // Перевірка на наявність крапки та цифр
        for (char ch : token)
        {
            if (ch == '.')
            {
                if (hasDecimalPoint)
                {
                    isNumber = false; // Друга крапка не є допустимою
                    break;
                }
                hasDecimalPoint = true;
            }
            else if (!std::isdigit(ch))
            {
                isNumber = false; // Не є числом
                break;
            }
        }

        // Якщо рядок є числом
        if (isNumber)
        {
            try
            {
                if (hasDecimalPoint)
                {
                    // Конвертувати рядок в double
                    double number = std::stod(token);
                    if (isNegative)
                    {
                        number = -number;
                    }
                    dataClientDoble.push_back(number);
                }
                else
                {
                    // Конвертувати рядок в int
                    int number = std::stoi(token);
                    if (isNegative)
                    {
                        number = -number;
                    }
                    dataClientInt.push_back(number);
                }
            }
            catch (const std::invalid_argument &e)
            {
                //   std::cerr << "Conversion error: " << e.what() << std::endl;
            }
        }
        else if (std::isalpha(token[0]))
        {
            // Перевірка на символ
           // dataClientChar.assign(token.begin(), token.end());
           //  dataClientChar.push_back(token);
           dataClientChar=dataBufer;
        }
        else
        {
            // std::cerr << "Unknown data type: " << token << std::endl;
        }
    }
    if (!dataClientDoble.empty())
    {
        // Перетворення всіх int в double і додавання до dataClientDoble
        for (int number : dataClientInt)
        {
            dataClientDoble.push_back(static_cast<double>(number));
        }
        // Очищення dataClientInt, оскільки всі значення перенесені в dataClientDoble
        dataClientInt.clear();
    }
}
bool ChoiseTask::AnaliticAnswer(vector<char> &dataBuffer)
{
    ParseUserData(dataBuffer);

    std::string response;

    if (dataClientInt.empty())
        return false;

    switch (dataClientInt[0])
    {
    case 1:
        BaseFunctionOptions("Enter your Name", std::bind(&ChoiseTask::NameSurname, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
        return true;
        break;
    case 2:
        BaseFunctionOptions("Enter two nubers for sum", std::bind(&ChoiseTask::SumOfNambers, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
        return true;
        break;
    case 3:
        BaseFunctionOptions("Enter two nubers for mulitply", std::bind(&ChoiseTask::MultipyOfNambers, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
        return true;
        break;
    case 4:
        BaseFunctionOptions("Enter array of numbers", std::bind(&ChoiseTask::MaxElementArray, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
        return true;
        break;
    case 5:
        BaseFunctionOptions("Enter Number chek for poliadnder", std::bind(&ChoiseTask::MaxNubers, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
        return true;
        break;
    case 6:
        BaseFunctionOptions("Enter Number chek for poliadnder", std::bind(&ChoiseTask::Poliander, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
        return true;
        break;
    case 7:
        BaseFunctionOptions("Enter array of numbers", std::bind(&ChoiseTask::SortArrayUp, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
        return true;
        break;

    case 8:
        BaseFunctionOptions("Enter a string to count occurrences of 'a'", std::bind(&ChoiseTask::CountLetterA, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
        return true;
        break;
    case 9:
        BaseFunctionOptions("Enter the length of the array to fill with zeros", std::bind(&ChoiseTask::SendZeros, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
        return true;
        break;
    case 10:
        BaseFunctionOptions("Enter a string to check for digits", std::bind(&ChoiseTask::CheckDigits, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
        return true;
        break;
    case 11:
        BaseFunctionOptions("Enter a name to append to the given surname", std::bind(&ChoiseTask::AddName, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
        return true;
        break;
    case 12:
        BaseFunctionOptions("Enter numbers to calculate their sum", std::bind(&ChoiseTask::SumThreeNumbers, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
        return true;
        break;
    case 13:
        BaseFunctionOptions("Enter numbers to calculate the product of negative numbers", std::bind(&ChoiseTask::ProductNegativeNumbers, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
        return true;
        break;
    case 14:
        BaseFunctionOptions("Enter an array of numbers to find min and max values", std::bind(&ChoiseTask::MinMaxElements, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
        return true;
        break;
    case 15:
        BaseFunctionOptions("Enter an array of numbers to add their average to each element", std::bind(&ChoiseTask::AddAverageToNumbers, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
        return true;
        break;
    case 16:
        BaseFunctionOptions("Enter a number to check if it's prime", std::bind(&ChoiseTask::CheckPrime, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
        return true;
        break;
    case 17:
        BaseFunctionOptions("Enter an array of numbers to sort in descending order", std::bind(&ChoiseTask::SortArrayDescending, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
        return true;
        break;
    case 18:
        BaseFunctionOptions("Enter a string to count spaces", std::bind(&ChoiseTask::CountSpaces, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
        return true;
        break;
    case 19://///error
        BaseFunctionOptions("Enter a string to check for spaces", std::bind(&ChoiseTask::SendXs, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
        return true;
        break;
    case 20:
        BaseFunctionOptions("Enter a number to factorize", std::bind(&ChoiseTask::CheckSpaces, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
        return true;
        break;
    case 21:
        BaseFunctionOptions("Enter a number to check if it's a perfect square", std::bind(&ChoiseTask::FactorizeNumber, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
        return true;
        break;
    case 22:
        BaseFunctionOptions("Enter numbers to replace negative values with zero", std::bind(&ChoiseTask::CheckPerfectSquare, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
        return true;
        break;
    case 23:
        BaseFunctionOptions("Enter a string to count vowels", std::bind(&ChoiseTask::ReplaceNegativesWithZero, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
        return true;
        break;
    case 24:
        BaseFunctionOptions("Enter the length of the array to fill with random numbers", std::bind(&ChoiseTask::CountVowels, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
        return true;
        break;
    case 25:
        BaseFunctionOptions("Enter a string to check for punctuation", std::bind(&ChoiseTask::SendRandomNumbers, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
        return true;
        break;
    case 26:
        BaseFunctionOptions("Enter a number to calculate its factorial", std::bind(&ChoiseTask::CheckPunctuation, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
        return true;
        break;
    case 27:
        BaseFunctionOptions("Enter a string to convert to uppercase", std::bind(&ChoiseTask::FactorialOfNumber, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
        return true;
        break;
    case 28:
        BaseFunctionOptions("Enter numbers to sum and send the result", std::bind(&ChoiseTask::ConvertUppercase, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
        return true;
        break;
    case 29:
        BaseFunctionOptions("Enter array of numbers", std::bind(&ChoiseTask::SumAndSend, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
        return true;
        break;

    default:
        response = "Choise operation 1-30";
        dataBuffer.assign(response.begin(), response.end());
        dataBuffer.resize(ChatBase::BUFF_SIZE, '\0');
        return false;
    }
}
void ChoiseTask::Chat()
{
    while (true)
    {
        std::fill(buffer.begin(), buffer.end(), '\0');
        int packetSize = ReceiveData(ClientConn, buffer);
        buffer[packetSize] = '\0'; // Null-terminate the string

        cout << "Client message: " << buffer.data() << endl;
        cout << "Your (host) message: ";

        if (AnaliticAnswer(buffer))
            continue;

        if (buffer.empty())
            buffer.push_back('\0'); // Ensure buffer is not empty

        SendData(ClientConn, buffer);

        if (buffer[0] == 'x' && buffer[1] == 'x' && buffer[2] == 'x')
        {
            shutdown(ClientConn, SD_BOTH);
            closesocket(ClientConn);
            return;
        }
    }
}
std::vector<char> ChoiseTask::NameSurname(const std::vector<char> &dataChar, const std::vector<int> &dataInt, const std::vector<double> &dataDouble)
{
    std::string response;
    vector<char> tmpbuffer(ChatBase::BUFF_SIZE);
    std::fill(tmpbuffer.begin(), tmpbuffer.end(), '\0');
    auto it = std::find(dataChar.begin(), dataChar.end(), '\0');

    // Перевірити, чи нульовий термінатор знайдено
    if (it != dataChar.begin())
    {

        // Перетворити частину вектора до нульового термінатора в рядок
        std::string clientName(dataChar.begin(), it);
        clientName.erase(std::remove(clientName.begin(), clientName.end(), '\n'), clientName.end());

        // Додати прізвище до імені

        response = clientName + " Skopas";
        cout << response << endl;
        tmpbuffer.assign(response.begin(), response.end());
        tmpbuffer.resize(ChatBase::BUFF_SIZE, '\0');
    }
    return tmpbuffer;
}
std::vector<char> ChoiseTask::SumOfNambers(const std::vector<char> &dataChar, const std::vector<int> &dataInt, const std::vector<double> &dataDouble)
{
    double tpmSumOfD = 0;
    std::string tmpstr;

    if (dataDouble.empty())
    {
        if (dataInt.size() >= 2)
        {
            int tpmSumOfI = dataInt[0] + dataInt[1];
            tmpstr = std::to_string(tpmSumOfI);
        }
    }
    else
    {
        if (dataDouble.size() >= 2)
        {
            tpmSumOfD = dataDouble[0] + dataDouble[1];
            tmpstr = std::to_string(tpmSumOfD);
        }
    }

    std::vector<char> result(tmpstr.begin(), tmpstr.end());
    return result;
}

std::vector<char> ChoiseTask::MultipyOfNambers(const std::vector<char> &dataChar, const std::vector<int> &dataInt, const std::vector<double> &dataDouble)
{
    double tpmSumOfD = 0;
    std::string tmpstr;

    if (dataDouble.empty())
    {
        if (dataInt.size() >= 2)
        {
            int tpmSumOfI = dataInt[0] * dataInt[1];
            tmpstr = std::to_string(tpmSumOfI);
        }
    }
    else
    {
        if (dataDouble.size() >= 2)
        {
            tpmSumOfD = dataDouble[0] * dataDouble[1];
            tmpstr = std::to_string(tpmSumOfD);
        }
    }

    std::vector<char> result(tmpstr.begin(), tmpstr.end());
    return result;
}
std::vector<char> ChoiseTask::MaxElementArray(const std::vector<char> &dataChar, const std::vector<int> &dataInt, const std::vector<double> &dataDouble)
{
    std::string tmpstr;

    if (dataDouble.empty())
    {
        // Для int
        if (!dataInt.empty())
        {
            auto tmpMaxI = std::max_element(dataInt.begin(), dataInt.end());
            tmpstr = std::to_string(*tmpMaxI); // Розіменовуємо ітератор
        }
        else
        {
            // Обробка у випадку, якщо dataInt порожній
            tmpstr = "No int data";
        }
    }
    else
    {
        // Для double
        if (!dataDouble.empty())
        {
            auto tmpMaxD = std::max_element(dataDouble.begin(), dataDouble.end());
            tmpstr = std::to_string(*tmpMaxD); // Розіменовуємо ітератор
        }
        else
        {
            // Обробка у випадку, якщо dataDouble порожній
            tmpstr = "No double data";
        }
    }

    // Перетворюємо рядок у вектор символів
    std::vector<char> result(tmpstr.begin(), tmpstr.end());
    return result;
}
std::vector<char> ChoiseTask::MaxNubers(const std::vector<char> &dataChar, const std::vector<int> &dataInt, const std::vector<double> &dataDouble)
{
    const double serverNumber = 23;
    string tmpstr;
    if (dataDouble.empty())
    {
        // Для int
        if (!dataInt.empty())
        {
            if (serverNumber > dataInt[0])
                tmpstr = std::to_string(serverNumber);
            else
                tmpstr = std::to_string(dataInt[0]);
        }
        else
        {
            // Обробка у випадку, якщо dataInt порожній
            tmpstr = "No int data";
        }
    }
    else
    {
        // Для double
        if (!dataDouble.empty())
        {
            if (serverNumber > dataDouble[0])
                tmpstr = std::to_string(serverNumber);
            else
                tmpstr = std::to_string(dataDouble[0]);
        }
        else
        {
            // Обробка у випадку, якщо dataDouble порожній
            tmpstr = "No double data";
        }
    }
    std::vector<char> result(tmpstr.begin(), tmpstr.end());
    return result;
}
std::vector<char> ChoiseTask::Poliander(const std::vector<char> &dataChar, const std::vector<int> &dataInt, const std::vector<double> &dataDouble)
{
    std::string tmpstr;
    bool isPalindrome = true;

    // Вибір числа для перевірки
    std::string numberStr;
    if (!dataInt.empty())
    {
        numberStr = std::to_string(dataInt[0]); // Перетворюємо перше число в рядок
    }
    else
    {
        tmpstr = "No";
        std::vector<char> result(tmpstr.begin(), tmpstr.end());
        return result;
    }

    // Перевірка паліндрому
    std::string reversedStr = numberStr;
    std::reverse(reversedStr.begin(), reversedStr.end()); // Перевертаємо рядок

    if (numberStr == reversedStr)
    {
        tmpstr = "Yes";
    }
    else
    {
        tmpstr = "No";
    }

    std::vector<char> result(tmpstr.begin(), tmpstr.end());
    return result;
}
std::vector<char> ChoiseTask::SortArrayUp(const std::vector<char> &dataChar, const std::vector<int> &dataInt, const std::vector<double> &dataDouble)
{
    std::string tmpstr;

    vector<int> tmpbufferInt;
    vector<double> tmpbufferDouble;
    if (!dataInt.empty())
    {
        tmpbufferInt = dataInt;
        sort(tmpbufferInt.begin(), tmpbufferInt.end());
        for (int num : tmpbufferInt)
        {
            tmpstr += to_string(num) + " ";
        }
    }
    else
    {
        tmpbufferDouble = dataDouble;
        sort(tmpbufferDouble.begin(), tmpbufferDouble.end());
        for (double num : tmpbufferDouble)
        {
            tmpstr += to_string(num) + " ";
        }
    }
    std::vector<char> result(tmpstr.begin(), tmpstr.end());
    return result;
    return result;
}
std::vector<char> ChoiseTask::CountLetterA(const std::vector<char> &dataChar, const std::vector<int> &dataInt, const std::vector<double> &dataDouble)
{
    int count = std::count(dataChar.begin(), dataChar.end(), 'a');
    std::string result = std::to_string(count);
    return std::vector<char>(result.begin(), result.end());
}
//9?
std::vector<char> ChoiseTask::SendZeros(const std::vector<char> &dataChar, const std::vector<int> &dataInt, const std::vector<double> &dataDouble)
{
    auto it = std::find(dataChar.begin(),dataChar.end(), '\0');
    if (it != dataChar.end()) {
       int length = std::distance(dataChar.begin(), it);
    }
    // Якщо '\0' не знайдено, повертаємо розмір вектора як позицію
   int length= dataChar.size();
    
    return std::vector<char>(length, '0');
}

std::vector<char> ChoiseTask::CheckDigits(const std::vector<char> &dataChar, const std::vector<int> &dataInt, const std::vector<double> &dataDouble)
{
    bool hasDigits = std::any_of(dataChar.begin(), dataChar.end(), ::isdigit);
    if (!dataInt.empty() || !dataDouble.empty())
        hasDigits = true;
    std::string result = hasDigits ? "Yes" : "No";
    return std::vector<char>(result.begin(), result.end());
}
// перевірити
std::vector<char> ChoiseTask::AddName(const std::vector<char> &dataChar, const std::vector<int> &dataInt, const std::vector<double> &dataDouble)
{
    auto it = std::find(dataChar.begin(),dataChar.end(), '\0');
    if (it != dataChar.end()) {
       int length = std::distance(dataChar.begin(), it);
    }
    // Якщо '\0' не знайдено, повертаємо розмір вектора як позицію
   int length= dataChar.size();
    std::string surname(dataChar.begin(), it);
    std::string fullName = surname + " Mykola";
    return std::vector<char>(fullName.begin(), fullName.end());
}

std::vector<char> ChoiseTask::SumThreeNumbers(const std::vector<char> &dataChar, const std::vector<int> &dataInt, const std::vector<double> &dataDouble)
{
    std::string result;
    if (!dataInt.empty() && (dataInt.size() == 3))
    {
        int sum = std::accumulate(dataInt.begin(), dataInt.end(), 0.0);
        result = std::to_string(sum);
    }
    else if (!dataDouble.empty() && (dataDouble.size() == 3))
    {
        double sum = std::accumulate(dataDouble.begin(), dataDouble.end(), 0.0);
        result = std::to_string(sum);
    }
    else
        result = "This is not number";

    return std::vector<char>(result.begin(), result.end());
}

std::vector<char> ChoiseTask::ProductNegativeNumbers(const std::vector<char> &dataChar, const std::vector<int> &dataInt, const std::vector<double> &dataDouble)
{
    std::string result;
    if (!dataDouble.empty() && dataDouble.size() == 3)
    {
        double product = 1.0;
        for (double num : dataDouble)
        {
            if (num < 0)
                product *= num;
        }
        result = std::to_string(product);
    }
    if (!dataInt.empty() && dataInt.size() == 3)
    {
        int product = 1.0;
        for (int num : dataInt)
        {
            if (num < 0)
                product *= num;
        }
        result = std::to_string(product);
    }

    return std::vector<char>(result.begin(), result.end());
}

std::vector<char> ChoiseTask::MinMaxElements(const std::vector<char> &dataChar, const std::vector<int> &dataInt, const std::vector<double> &dataDouble)
{
    std::string result;
    if (!dataDouble.empty())
    {
        double min = *std::min_element(dataDouble.begin(), dataDouble.end());
        double max = *std::max_element(dataDouble.begin(), dataDouble.end());
        result = "Min: " + std::to_string(min) + ", Max: " + std::to_string(max);
    }
    if (!dataInt.empty())
    {
        int min = *std::min_element(dataInt.begin(), dataInt.end());
        int max = *std::max_element(dataInt.begin(), dataInt.end());
        result = "Min: " + std::to_string(min) + ", Max: " + std::to_string(max);
    }

    return std::vector<char>(result.begin(), result.end());
}

std::vector<char> ChoiseTask::AddAverageToNumbers(const std::vector<char> &dataChar, const std::vector<int> &dataInt, const std::vector<double> &dataDouble)
{
    std::vector<double> tmpDouble;
      std::string resultStr ;
    if (!dataInt.empty() && dataInt.size() == 4)
    {
        tmpDouble.resize(dataInt.size(), 0);

        std::transform(dataInt.begin(), dataInt.end(), tmpDouble.begin(),
                       [](int value)
                       { return static_cast<double>(value); });
    }
    if (!dataDouble.empty() && dataDouble.size() == 4)
    {
        tmpDouble = dataDouble;
    }
    if (!tmpDouble.empty())
    {
        double sum = std::accumulate(tmpDouble.begin(), tmpDouble.end(), 0.0);
        double avg = sum / tmpDouble.size();
        std::vector<double> result(tmpDouble.size());
        std::transform(tmpDouble.begin(), tmpDouble.end(), result.begin(), [avg](double x)
                       { return x + avg; });
        resultStr;
        for (double num : result)
        {
            resultStr += std::to_string(num) + " ";
        }
        return std::vector<char>(resultStr.begin(), resultStr.end());
    }
    else
    {
       resultStr = "No data";
        return std::vector<char>(resultStr.begin(), resultStr.end());
    }
}

std::vector<char> ChoiseTask::CheckPrime(const std::vector<char> &dataChar, const std::vector<int> &dataInt, const std::vector<double> &dataDouble)
{
    std::string result;
    if(!dataInt.empty())
        result=false;
    int num = dataInt[0];
    bool isPrime = true;
    if (num <= 1)
        isPrime = false;
    for (int i = 2; i <= std::sqrt(num); i++)
    {
        if (num % i == 0)
        {
            isPrime = false;
            break;
        }
    }
    result = isPrime ? "Yes" : "No";
    return std::vector<char>(result.begin(), result.end());
}
//17?
std::vector<char> ChoiseTask::SortArrayDescending(const std::vector<char> &dataChar, const std::vector<int> &dataInt, const std::vector<double> &dataDouble)
{
    std::vector<int> sortedData = dataInt;
    std::sort(sortedData.rbegin(), sortedData.rend());
    std::string result;
    for (int num : sortedData)
    {
        result += std::to_string(num) + " ";
    }
    return std::vector<char>(result.begin(), result.end());
}

std::vector<char> ChoiseTask::CountSpaces(const std::vector<char> &dataChar, const std::vector<int> &dataInt, const std::vector<double> &dataDouble)
{
    int count = std::count(dataChar.begin(), dataChar.end(), ' ');
    std::string result = std::to_string(count);
    return std::vector<char>(result.begin(), result.end());
}
// 19
std::vector<char> ChoiseTask::SendXs(const std::vector<char> &dataChar, const std::vector<int> &dataInt, const std::vector<double> &dataDouble)
{
    int length = dataChar.size();
    return std::vector<char>(length, 'X');
}

std::vector<char> ChoiseTask::CheckSpaces(const std::vector<char> &dataChar, const std::vector<int> &dataInt, const std::vector<double> &dataDouble)
{
    bool hasSpaces = std::any_of(dataChar.begin(), dataChar.end(), ::isspace);
    std::string result = hasSpaces ? "Yes" : "No";
    return std::vector<char>(result.begin(), result.end());
}

std::vector<char> ChoiseTask::FactorizeNumber(const std::vector<char> &dataChar, const std::vector<int> &dataInt, const std::vector<double> &dataDouble)
{
    int num = dataInt[0];
    std::vector<int> factors;
    for (int i = 2; i <= num; i++)
    {
        while (num % i == 0)
        {
            factors.push_back(i);
            num /= i;
        }
    }
    std::string result;
    for (int factor : factors)
    {
        result += std::to_string(factor) + " ";
    }
    return std::vector<char>(result.begin(), result.end());
}

std::vector<char> ChoiseTask::CheckPerfectSquare(const std::vector<char> &dataChar, const std::vector<int> &dataInt, const std::vector<double> &dataDouble)
{
    int num = dataInt[0];
    int root = static_cast<int>(std::sqrt(num));
    std::string result = (root * root == num) ? "Yes" : "No";
    return std::vector<char>(result.begin(), result.end());
}

std::vector<char> ChoiseTask::ReplaceNegativesWithZero(const std::vector<char> &dataChar, const std::vector<int> &dataInt, const std::vector<double> &dataDouble)
{
    std::vector<int> modifiedData = dataInt;
    std::replace_if(modifiedData.begin(), modifiedData.end(), [](int x)
                    { return x < 0; }, 0);
    std::string result;
    for (int num : modifiedData)
    {
        result += std::to_string(num) + " ";
    }
    return std::vector<char>(result.begin(), result.end());
}

std::vector<char> ChoiseTask::CountVowels(const std::vector<char> &dataChar, const std::vector<int> &dataInt, const std::vector<double> &dataDouble)
{
    int count = std::count_if(dataChar.begin(), dataChar.end(), [](char c)
                              { return std::string("aeiouAEIOU").find(c) != std::string::npos; });
    std::string result = std::to_string(count);
    return std::vector<char>(result.begin(), result.end());
}

std::vector<char> ChoiseTask::SendRandomNumbers(const std::vector<char> &dataChar, const std::vector<int> &dataInt, const std::vector<double> &dataDouble)
{
    int length = dataChar.size();
    std::vector<char> randomNumbers;
    for (int i = 0; i < length; ++i)
    {
        randomNumbers.push_back('0' + rand() % 10);
    }
    return randomNumbers;
}

std::vector<char> ChoiseTask::CheckPunctuation(const std::vector<char> &dataChar, const std::vector<int> &dataInt, const std::vector<double> &dataDouble)
{
    bool hasPunctuation = std::any_of(dataChar.begin(), dataChar.end(), ::ispunct);
    std::string result = hasPunctuation ? "Yes" : "No";
    return std::vector<char>(result.begin(), result.end());
}

std::vector<char> ChoiseTask::FactorialOfNumber(const std::vector<char> &dataChar, const std::vector<int> &dataInt, const std::vector<double> &dataDouble)
{
    int num = dataInt[0];
    int factorial = 1;
    for (int i = 2; i <= num; ++i)
    {
        factorial *= i;
    }
    std::string result = std::to_string(factorial);
    return std::vector<char>(result.begin(), result.end());
}

std::vector<char> ChoiseTask::ConvertUppercase(const std::vector<char> &dataChar, const std::vector<int> &dataInt, const std::vector<double> &dataDouble)
{
    std::vector<char> uppercaseData = dataChar;
    std::transform(uppercaseData.begin(), uppercaseData.end(), uppercaseData.begin(), ::toupper);
    return uppercaseData;
}

std::vector<char> ChoiseTask::SumAndSend(const std::vector<char> &dataChar, const std::vector<int> &dataInt, const std::vector<double> &dataDouble)
{
    double sum = std::accumulate(dataDouble.begin(), dataDouble.end(), 0.0);
    std::string result = std::to_string(sum);
    return std::vector<char>(result.begin(), result.end());
}

/*std::vector<char>ChoiseTask::SumOfNambers(const vector<double>& dataBuffer){
    int tpmSumOfA=0;
    tpmSumOfA=dataBuffer[0]+dataBuffer[1];
    string tmpstr;
    tmpstr=to_string(tpmSumOfA);
    vector<char> result(tmpstr.begin(), tmpstr.end());
    return result;
}*/

void ChoiseTask::BaseFunctionOptions(string queeryClient, const std::function<vector<char>(const std::vector<char> &, const std::vector<int> &, const std::vector<double> &)> &func)
{
    std::string response;
    vector<char> tmpbuffer(ChatBase::BUFF_SIZE);

    response = queeryClient;

    tmpbuffer.assign(response.begin(), response.end());

    tmpbuffer.resize(ChatBase::BUFF_SIZE, '\0');

    SendData(ClientConn, tmpbuffer);

    response.clear();

    std::fill(tmpbuffer.begin(), tmpbuffer.end(), '\0');

    int packetSize = ReceiveData(ClientConn, tmpbuffer);
    ParseUserData(tmpbuffer);
    tmpbuffer = func(dataClientChar, dataClientInt, dataClientDoble);
    tmpbuffer.resize(ChatBase::BUFF_SIZE, '\0');
    SendData(ClientConn, tmpbuffer);
}
