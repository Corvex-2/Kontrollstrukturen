#include <iostream>
#include <string>
#include <cstring>
#include <chrono>
#include <thread>

#include "Windows.h"


/// <summary>
/// Deklarierung f�r konstante Variablen, zum Konvertieren von verschiedenen Ma�einheiten.
/// </summary>
const double TEBIBYTE_MULTIPLIER = 1024. * 1024. * 1024. * 1024.;
const double GIBIBYTE_MULTIPLIER = 1024. * 1024. * 1024.;
const double MEBIBYTE_MULTIPLIER = 1024. * 1024.;
const double KIBIBYTE_MULTIPLIER = 1024.;
const double BYTE_MULTIPLIER = 8;

/// <summary>
/// Gibt die angegebene Nachricht in der Konsole aus, greift den Input vom user ab und gibt diesen an den caller zur�ck.
/// </summary>
/// <param name="message">Die Nachricht die ausgegeben wird.</param>
/// <returns>Der Input den der User eingibt.</returns>
std::string get_user_input(std::string message) noexcept
{
    std::cout << message;
    std::string _szInput;
    std::cin >> _szInput;
    return _szInput;
}

/// <summary>
/// Gibt den Namen der Ma�einheit zur�ck, anhand eines angegebenen Integers, welcher f�r diese Ma�einheit im Men� festegelegt ist.
/// </summary>
/// <param name="InputType">Die Zahl die zur Identifizierung der Ma�einheit verwendet wird.</param>
/// <returns>Den Namen der Ma�einheit.</returns>
std::string get_type_name(int InputType) noexcept
{
    switch (InputType)
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

/// <summary>
/// Konvertiert den angegebenen Input anhand eines Integers, welcher die Ma�einheit identifiziert, in Bits und gibt den wert an den caller zur�ck.
/// </summary>
/// <param name="InputValue">Der Wert der in Bits konvertiert werden soll.</param>
/// <param name="InputType">Die Zahl die zur Identifizierung der Ma�einheit verwendet wird.</param>
/// <returns>Den zu konvertierenden Wert in Bits.</returns>
double convert_type_to_bits(double InputValue, int InputType)
{
    switch (InputType)
    {
        case 1:
            return InputValue;
        case 2:
            return InputValue * BYTE_MULTIPLIER * 8;
        case 3:
            return InputValue * KIBIBYTE_MULTIPLIER * 8;
        case 4:
            return InputValue * MEBIBYTE_MULTIPLIER * 8;
        case 5:
            return InputValue * GIBIBYTE_MULTIPLIER * 8;
        case 6:
            return InputValue * TEBIBYTE_MULTIPLIER * 8;
    }
    return 0;
}

/// <summary>
/// Konvertiert den angegebenen Input in Bits anhand eines Integers, welcher die Ma�einheit identifiziert, in die gew�nsche Ma�einheit und gibt den wert an den caller zur�ck.
/// </summary>
/// <param name="InputValue">Der Wert in Bits der konvertiert werden soll.</param>
/// <param name="InputType">Die Zahl die zur Identifizierung der Ma�einheit verwendet wird.</param>
/// <returns>Den zu konvertierenden Wert in der gew�nschten Ma�einheit.</returns>
double convert_bits_to_type(double InputValue, int InputType)
{
    switch (InputType)
    {
        case 1:
            return InputValue;
        case 2:
            return InputValue / BYTE_MULTIPLIER;
        case 3:
            return InputValue / BYTE_MULTIPLIER / KIBIBYTE_MULTIPLIER;
        case 4:
            return InputValue / BYTE_MULTIPLIER / MEBIBYTE_MULTIPLIER;
        case 5:
            return InputValue / BYTE_MULTIPLIER / GIBIBYTE_MULTIPLIER;
        case 6:
            return InputValue / BYTE_MULTIPLIER / TEBIBYTE_MULTIPLIER;
    }
    return 0;
}

/// <summary>
/// Greift den Input des Users ab und beginnt mit der Konvertierung in die verschiedenen Ma�einheiten.
/// </summary>
/// <param name="InputType">Ein Integer mit dem die Ma�einheit des Input identifiziert wird.</param>
/// <returns>Einen Boolean welcher identifiziert ob die funktion erfolgreich ausgef�hrt wird.</returns>
bool convert(int InputType)
{
    std::cout << std::endl;

    /// <summary>
    /// Deklarierung der Variable m_inputValue mit dem Wert 0.
    /// </summary>
    double m_inputValue = 0;

    /// <summary>
    /// F�hrt eine loop aus, welche nur unterbrochen wird, wenn der angegebene Input nicht gleich 0 ist.
    /// </summary>
    while (m_inputValue == 0)
    {
        /// <summary>
        /// Grefit alle Fehlermeldungen (Exceptions) ab und f�hrt ein catch durch um diese Fehlermeldungen zu verarbeiten, ohne dass die Applikation dabei abst�rtzt.
        /// </summary>
        try
        {
            /// <summary>
            /// Konvertiert den Input von std:string zum Datentyp Double und speichert ihn in der Variable m_inputValue.
            /// </summary>
            m_inputValue = std::atof(get_user_input("Geben Sie einen Wert ein: ").c_str());

            /// <summary>
            /// �berpr�ft ob der Input nicht gleich null ist, wenn ja wird eine Fehlermeldung ausgegeben und eine weitere Input abfrage durchgef�hrt.
            /// </summary>
            if (m_inputValue == 0)
            {
                std::cout << "Die Eingabe muss groesser oder kleiner als 0 sein!" << std::endl;
                continue;
            }

            /// <summary>
            /// Konvertiert den angegebenen Wert in Bits und speichert diesen in der Variable m_inputInBits.
            /// </summary>
            auto m_inputInBits = convert_type_to_bits(m_inputValue, InputType);

            /// <summary>
            /// F�hrt eine loop mit allen verf�gbaren Ma�einheit Identifikatoren aus 
            /// </summary>
            for (int i = 1; i <= 6; i++)
                std::cout << get_type_name(i) << ": " << convert_bits_to_type(m_inputInBits, i) << std::endl;
        }
        /// <summary>
        /// Alle Fehlermeldungen die im obrigen try scope vorkommen werden hier verarbeitet. Die std::exception ist hier ein Objekt welches Informationen �ber den vorgefallenen Fehler enth�lt,
        /// beispielsweise die Fehlermeldung.
        /// </summary>
        catch (const std::exception& errorCode)
        {
            /// <summary>
            /// Sollte ein Fehler aufgetaucht sein, wird hier eine Fehlermeldung in der Konsole ausgegeben. Der User kann sich dann mit dieser Fehlermeldung, sofern n�tig, ggf. an die Developer
            /// der Applikation wenden.
            /// </summary>
            std::cout << "An error occurred somewhere during operation. Error Code:  " << errorCode.what() << std::endl << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(2500));
            /// <summary>
            /// Gibt den Wert false zur�ck, da die Konvertierung nicht ohne Fehler durchgef�hrt werden konnte.
            /// </summary>
            return false;
        }
    }
    /// <summary>
    /// Gibt den Wert true zur�ck, da die Konvertierung ohne Fehler durchgef�hrt wurde.
    /// </summary>
    std::cout << std::endl;
    return true;
}

/// <summary>
/// Zeigt die verscheidenen Auswahlm�glichkeiten in der Konsole an.
/// </summary>
void display_menu() noexcept
{
    std::cout << "1.) Eingabe in Bit." << std::endl;
    std::cout << "2.) Eingabe in Byte." << std::endl;
    std::cout << "3.) Eingabe in Kibibyte." << std::endl;
    std::cout << "4.) Eingabe in Mebibyte." << std::endl;
    std::cout << "5.) Eingabe in Gibibyte." << std::endl;
    std::cout << "6.) Eingabe in Tebibyte." << std::endl;
    std::cout << "0.) Beenden." << std::endl;
    std::cout << std::endl;
}

/// <summary>
/// Die Hauptloop der Applikation. Hier wird das Men� angezeigt und die Ma�einheit der eingabe Festgelegt.
/// </summary>
void main_loop()
{
    /// <summary>
    /// Setzt die Konsole in den fixed notation Modus, damit die cout funktion Zahlen ohne exponenten ausgibt. (bsp. 1,1e+12 wird 1,100,000,000,000)
    /// </summary>
    std::cout << std::fixed;

    /// <summary>
    /// Eine Endlosschleife die l�uft bis der User den Input f�r das beenden gibt.
    /// </summary>
    while (true)
    {
        /// <summary>
        /// Grefit alle Fehlermeldungen (Exceptions) ab und f�hrt ein catch durch um diese Fehlermeldungen zu verarbeiten, ohne dass die Applikation dabei abst�rtzt.
        /// </summary>
        try
        {
            /// <summary>
            /// Zeigt das Men� in der Konsole an.
            /// </summary>
            display_menu();

            /// <summary>
            /// Greift den Input des Benutzers ab und konvertiert diesen in einen Integer.
            /// </summary>
            int m_inputType = std::stoi(get_user_input("Ihre Eingabe: "));

            /// <summary>
            /// �berpr�ft ob der Wert von der Variable m_inputType gleich 0 ist, wenn ja wird die loop unterbrochen.
            /// </summary>
            if (m_inputType == 0)
                break;
            /// <summary>
            /// �berpr�ft ob der Wert von der Variable m_inputType kleiner als 0 oder gr��er als 6 ist, wenn ja wird eine Fehlermeldung ausgegeben.
            /// </summary>
            if (m_inputType < 0 || m_inputType > 6)
            {
                std::cout << "Die Eingabe muss zwischen 0 und 6 liegen. Ihre Eingabe: " << m_inputType << std::endl << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(2500));
                continue;
            }

            /// <summary>
            /// Beginnt mit dem konvertierung Prozess.
            /// </summary>
            convert(m_inputType);
        }
        /// <summary>
        /// Alle Fehlermeldungen die im obrigen try scope vorkommen werden hier verarbeitet. Die std::exception ist hier ein Objekt welches Informationen �ber den vorgefallenen Fehler enth�lt,
        /// beispielsweise die Fehlermeldung.
        /// </summary>
        catch (const std::exception& errorCode)
        {
            std::cout << "An error occurred somewhere during operation. Error Code:  " << errorCode.what() << std::endl << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(2500));
        }
    }
}

/// <summary>
/// Der EntryPoint der Applikation.
/// </summary>
/// <returns>Einen Wert, welcher angibt, ob das Programm erfolgreich ausgef�rt wurde. (0 = SUCCESS)</returns>
int main() noexcept
{
    /// <summary>
    /// Setzt den Titel der Konsole.
    /// </summary>
    SetConsoleTitleA("Kontrollstrukturen und Verzweigungen");
    
    /// <summary>
    /// F�hrt die main_loop aus.
    /// </summary>
    main_loop();
    
    /// <summary>
    /// Gibt den Wert 0 zur�ck und beendet die Applikation.
    /// </summary>
    return 0;
}

