#include <iostream>
#include <string>
#include <cstring>
#include <chrono>
#include <thread>

#include "Windows.h"

const double TEBIBYTE_MULTIPLIER = 1024. * 1024. * 1024. * 1024.;
const double GIBIBYTE_MULTIPLIER = 1024. * 1024. * 1024.;
const double MEBIBYTE_MULTIPLIER = 1024. * 1024.;
const double KIBIBYTE_MULTIPLIER = 1024.;
const double BYTE_MULTIPLIER = 8;

std::string get_user_input(std::string message) noexcept
{
    std::cout << message;
    std::string _szInput;
    std::cin >> _szInput;
    return _szInput;
}

std::string output_from_dynamic_type(int iDynamic) noexcept
{
    switch (iDynamic)
    {
        case 1:
            return "Bit";
        case 2:
            return "Byte";
        case 3:
            return "Kibibyte";
        case 4:
            return "Mebibyte";
        case 5:
            return "Gibibyte";
        case 6:
            return "Tebibyte";
    }
    return "NONE";
}

double to_bit_from_dynamic(double dValue, int iDynamic)
{
    switch (iDynamic)
    {
        case 1:
            return dValue;
        case 2:
            return dValue * BYTE_MULTIPLIER * 8;
        case 3:
            return dValue * KIBIBYTE_MULTIPLIER * 8;
        case 4:
            return dValue * MEBIBYTE_MULTIPLIER * 8;
        case 5:
            return dValue * GIBIBYTE_MULTIPLIER * 8;
        case 6:
            return dValue * TEBIBYTE_MULTIPLIER * 8;
    }
    return 0;
}

double to_dynamic_output(double dValue, int iDynamic)
{
    switch (iDynamic)
    {
        case 1:
            return dValue;
        case 2:
            return dValue / BYTE_MULTIPLIER;
        case 3:
            return dValue / BYTE_MULTIPLIER / KIBIBYTE_MULTIPLIER;
        case 4:
            return dValue / BYTE_MULTIPLIER / MEBIBYTE_MULTIPLIER;
        case 5:
            return dValue / BYTE_MULTIPLIER / GIBIBYTE_MULTIPLIER;
        case 6:
            return dValue / BYTE_MULTIPLIER / TEBIBYTE_MULTIPLIER;
    }
    return 0;
}

bool convert_all(int iDynamic)
{
    std::cout << std::endl;
    double _dInputValue = 0;

    while (_dInputValue == 0)
    {
        try
        {
            _dInputValue = std::atof(get_user_input("Geben Sie einen Wert ein: ").c_str());

            if (_dInputValue == 0)
            {
                std::cout << "Die Eingabe muss groesser oder kleiner als 0 sein!" << std::endl;
                continue;
            }

            auto _dInputBits = to_bit_from_dynamic(_dInputValue, iDynamic);

            for (int i = 1; i <= 6; i++)
                std::cout << output_from_dynamic_type(i) << ": " << to_dynamic_output(_dInputBits, i) << std::endl;
        }
        catch (const std::exception& errorCode)
        {
            std::cout << "An error occurred somewhere during operation. Error Code:  " << errorCode.what() << std::endl << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(2500));
            return false;
        }
    }
    std::cout << std::endl;
    return true;
}


std::string display_menu_and_get_input() noexcept
{
    std::cout << std::fixed;
    std::cout << "1.) Eingabe in Bit." << std::endl;
    std::cout << "2.) Eingabe in Byte." << std::endl;
    std::cout << "3.) Eingabe in Kibibyte." << std::endl;
    std::cout << "4.) Eingabe in Mebibyte." << std::endl;
    std::cout << "5.) Eingabe in Gibibyte." << std::endl;
    std::cout << "6.) Eingabe in Tebibyte." << std::endl;
    std::cout << "0.) Beenden." << std::endl;
    std::cout << std::endl;
    return get_user_input("Ihre Eingabe: ");
}

void main_loop()
{
    while (true)
    {
        try
        {
            int _iDynamic = std::stoi(display_menu_and_get_input());

            if (_iDynamic == 0)
                break;
            if (_iDynamic < 0 || _iDynamic > 6)
            {
                std::cout << "Die Eingabe muss zwischen 0 und 6 liegen. Ihre Eingabe: " << _iDynamic << std::endl << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(2500));
                continue;
            }

            convert_all(_iDynamic);
        }
        catch (const std::exception& errorCode)
        {
            std::cout << "An error occurred somewhere during operation. Error Code:  " << errorCode.what() << std::endl << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(2500));
        }
    }
}

int main() noexcept
{
    SetConsoleTitleA("Kontrollstrukturen und Verzweigungen");
    main_loop();
    return 0;
}

