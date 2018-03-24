#define _CRT_SECURE_NO_WARNINGS

#include "enigdialog.h"
#include <QApplication>

#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>

#include <ctime>


std::string abcd		= "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
std::string wheel1		= "EKMFLGDQVZNTOWYHXUSPAIBRCJ";
std::string wheel2		= "AJDKSIRUXBLHWTMCQGZNPYFVOE";
std::string wheel3		= "BDFHJLCPRTXVZNYEIWGAKMUSQO";
std::string reflector_B = "YRUHQSLDPXNGOKMIEBFZCWVJAT";


std::unordered_map<char, int>abc_to_number;
std::unordered_map<int, char>number_to_abc;


//std::unordered_map<char, char>ref_B_tran;

std::vector<int>rotor1_vec;
std::vector<int>rotor2_vec;
std::vector<int>rotor3_vec; // названия векторов соотвествуют названию колес которые в них помещаются


std::vector<int>ref_B_vec;
std::vector<int>abc_vec;




//Заполнение контейнеров

int main(int argc, char *argv[])
{
    int i = 0;

    for (auto p = abcd.begin(); p != abcd.end(); p++)
    {
        abc_to_number[*p] = i;
        number_to_abc[i] = *p;
        i++;
    }

    i = 0;


    for (auto x : wheel1) rotor1_vec.push_back(abc_to_number[x]);
    for (auto x : wheel2) rotor2_vec.push_back(abc_to_number[x]);
    for (auto x : wheel3) rotor3_vec.push_back(abc_to_number[x]);

    for (auto x : abcd) abc_vec.push_back(abc_to_number[x]);
    for (auto x : reflector_B)ref_B_vec.push_back(abc_to_number[x]);


    QApplication a(argc, argv);
    EnigDialog w;
    w.show();

    return a.exec();
}


