
#include "enigdialog.h"
#include "ui_enigdialog.h"

#include <string>
#include <unordered_map>
#include <map>
#include <vector>
#include <algorithm>

#include <QString>
#include <QChar>
#include <QMap>
#include <QVector>

namespace rotor //диски врещние бабин шифрования
{
    int rotor1 = 0; // fast
    int rotor2 = 0; // middle
    int rotor3 = 0; // slow
    int rot_diff;

}

extern std::string abcd;
extern std::string wheel1;
extern std::string wheel2;
extern std::string wheel3;
extern std::string reflector_B ;


extern std::vector<int>rotor1_vec;
extern std::vector<int>rotor2_vec;
extern std::vector<int>rotor3_vec; // названия векторов соотвествуют названию колес которые в них помещаются


extern std::vector<int>ref_B_vec;
extern std::vector<int>abc_vec;

extern std::unordered_map<char, int>abc_to_number;
extern std::unordered_map<int, char>number_to_abc;




// Функции шифрования и дешифрования поределены здесь
// так как нельзя поместить еще одно определение роторов

char encryption(char input)
{
    if (!isalpha(input)) //даже ротор вращать не будем
        return input;
    else
    {
        rotor::rotor1++; // соответстсвует ситуации, что буква была введена и значит ротор провернулся

                         //----------------------------------------Вращательная состовляющая машины

        if (rotor::rotor1 == 17) // средний ротор поворачивается когда быстрый ротор достигает 'R'
        {
            rotor::rotor2++;

            if(rotor::rotor2 == 6)rotor::rotor3++;
        }

        if (rotor::rotor1 >= 26)
            rotor::rotor1 = 0;

        if (rotor::rotor2 >= 26)
            rotor::rotor2 = 0;

        if (rotor::rotor3 >= 26)
            rotor::rotor3 = 0;
        //----------------------------------------Вращательная состовляющая машины


        //-------------Пошло шифрование

        int input_int = abc_to_number[input];
        char input_char;

        input_int = (abc_vec[rotor::rotor1] + input_int) % 26;

        input_int = rotor1_vec[input_int];			// находим на роторе
                                                    //-------------------------ПРОШЛИ ПЕРВЫЙ РОТОР

        rotor::rot_diff = rotor::rotor2 - rotor::rotor1; //считаем разницу между следующим ротором и предыдущим

        if (rotor::rot_diff < 0)
            rotor::rot_diff += 26; //26 символов в колесе здесь не до конца уверен


        input_int = (input_int + rotor::rot_diff % 26) % 26;
        input_int = rotor2_vec[input_int];			// находим на роторе

                                                    //-------------------------ПРОШЛИ ВТОРОЙ РОТОР


        rotor::rot_diff = rotor::rotor3 - rotor::rotor2; // нашли разницу между следующим ротором и предыдущим


        if (rotor::rot_diff < 0)
            rotor::rot_diff += 26; //26 символов в колесе

        input_int = (input_int + rotor::rot_diff % 26) % 26; // 26 индексов
        input_int = rotor3_vec[input_int];			// находим на роторе

                                                    //---------------------------------ПРОШЛИ ТЕРТИЙ РОТОР идем на РЕФЛЕКТОР Б



        rotor::rot_diff = (input_int - rotor::rotor3) % 26;

        if (rotor::rot_diff < 0)
            rotor::rot_diff += 26;

        input_int = rotor::rot_diff % 26;

        auto iter = std::find(ref_B_vec.begin(), ref_B_vec.end(), input_int);

        input_int = iter - ref_B_vec.begin();
        input_char = number_to_abc[input_int];
        //std::cout << input_char << std::endl;

        //шифровка в обратном направлении

        rotor::rot_diff = rotor::rotor3;

        input_int = (input_int + rotor::rot_diff%26)%26;
        //std::cout << number_to_abc[input_int] << std::endl;

        iter = std::find(rotor3_vec.begin(), rotor3_vec.end(), input_int);

        input_int = iter - rotor3_vec.begin(); //перешли на друю сторону ротора3
        //std::cout << number_to_abc[input_int] << std::endl;

        rotor::rot_diff = rotor::rotor3 - rotor::rotor2;

        if (rotor::rot_diff < 0)
            rotor::rot_diff += 26;

        input_int = input_int - rotor::rot_diff % 26;

        if (input_int < 0)
            input_int += 26;


        // прошли третий ротор
        //std::cout << number_to_abc[input_int] << std::endl;

        iter = std::find(rotor2_vec.begin(), rotor2_vec.end(), input_int);//<---

        input_int = iter - rotor2_vec.begin();//<--
        // В отмеченных стрелочкой строчках, мы находим позицию найденного символа
        // input_int на бобине ротора2 и зачем работаем с этой позицией

        rotor::rot_diff = rotor::rotor2 - rotor::rotor1;

        if (rotor::rot_diff < 0)
            rotor::rot_diff += 26;

        input_int = input_int - rotor::rot_diff % 26;

        if (input_int < 0)
            input_int += 26;

        //std::cout << number_to_abc[input_int] << std::endl;

        //Прошли второй ротор-----------------------------------

        iter = std::find(rotor1_vec.begin(), rotor1_vec.end(), input_int);//<---

        input_int = iter - rotor1_vec.begin();//<--
                                              // В отмеченных стрелочкой строчках, мы находим позицию найденного символа

        if (input_int < 0)
            input_int += 26;                                      // input_int на бобине ротора2 и зачем работаем с этой позицией

        rotor::rot_diff = rotor::rotor1;

        if (rotor::rot_diff < 0)
            rotor::rot_diff += 26;

        input_int = input_int - rotor::rot_diff % 26;

        if (input_int < 0)
            input_int += 26;

        //std::cout << number_to_abc[input_int] << std::endl;

        //rotor1 = Q
        //rotor2 = U
        //rotor3 = C
        // encryption('A') = W





        char output = number_to_abc[input_int];
        //std::cout << "result of encrypting : " << output << std::endl;

        return output;
    }
}



char decryption(char input)
{
    if (!isalpha(input)) //даже ротор вращать не будем 	//return input;
        return input;
    else
    {
        rotor::rotor1++; // соответстсвует ситуации, что буква была введена и значит ротор провернулся

                         //----------------------------------------Вращательная состовляющая машины


        if (rotor::rotor1 == 17) // средний ротор поворачивается когда быстрый ротор достигает 'R'
        {
            rotor::rotor2++;

            if(rotor::rotor2 == 6)rotor::rotor3++;
        }


        if (rotor::rotor1 >= 26)
            rotor::rotor1 = 0;

        if (rotor::rotor2 >= 26)
            rotor::rotor2 = 0;

        if (rotor::rotor3 >= 26)
            rotor::rotor3 = 0;
        //----------------------------------------Вращательная состовляющая машины

        rotor::rot_diff = rotor::rotor3 - rotor::rotor2;

        //if (rotor::rot_diff < 0)
        //	rotor::rot_diff += 26; //26 символов в колесе

        //if (input_int < 0)
        //	input_int += 26;


        char input_char;
        int input_int = abc_to_number[input];

        //std::cout << number_to_abc[input_int] << std::endl;

        rotor::rot_diff = rotor::rotor1;

        if (rotor::rot_diff < 0)
            rotor::rot_diff += 26;

        input_int = (input_int + rotor::rot_diff % 26)%26;

        //std::cout << number_to_abc[input_int] << std::endl;

        auto iter = std::find(rotor1_vec.begin(), rotor1_vec.end(), input_int);

        input_int = iter - rotor1_vec.begin();

        //std::cout << number_to_abc[input_int] << std::endl;

        input_int = rotor1_vec[input_int];

        input_char = number_to_abc[rotor1_vec[input_int]]; //временное значение
        // ищем переменную на роторе
        input_int = abc_to_number[input_char];

        //std::cout << number_to_abc[input_int] << std::endl;
        //Прошли первый ротор


        rotor::rot_diff = rotor::rotor2 - rotor::rotor1;

        if (rotor::rot_diff < 0)
            rotor::rot_diff += 26;

        input_int = (input_int + rotor::rot_diff % 26)%26;

        input_char = number_to_abc[rotor2_vec[input_int]];
        input_int = abc_to_number[input_char];

        //std::cout << number_to_abc[input_int] << std::endl;

        // ПРошли второй ротор


        rotor::rot_diff = rotor::rotor3 - rotor::rotor2;

        if (rotor::rot_diff < 0)
            rotor::rot_diff += 26;

        input_int = (input_int + rotor::rot_diff % 26) % 26;

        input_char = number_to_abc[rotor3_vec[input_int]];
        input_int = abc_to_number[input_char];

        //std::cout << number_to_abc[input_int] << std::endl;


        //Прошли третий ротор

        rotor::rot_diff = rotor::rotor3;

        if (rotor::rot_diff < 0)
            rotor::rot_diff += 26;


        input_int = (input_int - rotor::rot_diff % 26) % 26;

        if (input_int < 0)
            input_int += 26;

        //std::cout << number_to_abc[input_int] << std::endl;

        input_char = number_to_abc[ref_B_vec[input_int]];
        input_int = abc_to_number[input_char];

        //std::cout << input_int << std::endl;

        //Прошли первый круг------------------------

        rotor::rot_diff = rotor::rotor3;

        if (rotor::rot_diff < 0)
            rotor::rot_diff += 26;

        input_int = (input_int + rotor::rot_diff%26)%26;

        //std::cout << number_to_abc[input_int] << std::endl;

        iter = std::find(rotor3_vec.begin(), rotor3_vec.end(), input_int);

        input_int = iter - rotor3_vec.begin();

        //std::cout << number_to_abc[input_int] << std::endl;

        // прошли третитий ротор

        rotor::rot_diff = rotor::rotor3 - rotor::rotor2;

        if (rotor::rot_diff < 0)
            rotor::rot_diff += 26;

        input_int = (input_int - rotor::rot_diff) % 26;

        if (input_int < 0)
            input_int += 26;

        //std::cout << number_to_abc[input_int] << std::endl;

        iter = std::find(rotor2_vec.begin(), rotor2_vec.end(), input_int);

        input_int = iter - rotor2_vec.begin();

        //std::cout << number_to_abc[input_int] << std::endl;

        //Прошли второй ротор

        rotor::rot_diff = rotor::rotor2 - rotor::rotor1;

        if (rotor::rot_diff < 0)
            rotor::rot_diff += 26;

        input_int = (input_int - rotor::rot_diff) % 26;

        if (input_int < 0)
            input_int += 26;

        //std::cout << number_to_abc[input_int] << std::endl;

        iter = std::find(rotor1_vec.begin(), rotor1_vec.end(), input_int);

        input_int = iter - rotor1_vec.begin();

        //std::cout << number_to_abc[input_int] << std::endl;
        // Прошли первый ротор


        input_int = input_int - rotor::rotor1;

        if (input_int < 0)
            input_int += 26;


        char output = number_to_abc[input_int];

        return output;

    }//else
}



// Функции шифрования и дешифрования поределены здесь
// так как нельзя поместить еще одно определение роторов



EnigDialog::EnigDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EnigDialog)
{
    ui->setupUi(this);

    QRegExp exp("[A-Z]{1}");
    ui->slow_rotor_letter->setValidator(new QRegExpValidator(exp,this));
    ui->middle_rotor_letter->setValidator(new QRegExpValidator(exp,this));
    ui->fast_rotor_letter->setValidator(new QRegExpValidator(exp,this));
}

EnigDialog::~EnigDialog()
{
    delete ui;
}


std::vector<char>input;

QString plug_key;

std::map<char,char>plug_board;

bool begin = true; // bool для удобства отображения plug

std::vector<bool>is_up; // show uppercase letter or lower case letter was entered


std::vector<bool>on_off(26,true); //indicates what letters were entered on plugboard


// functions indicate rotor rotating

void EnigDialog::on_slow_rotor_button_plus_pressed()
{
    rotor::rotor3++;

    if(rotor::rotor3 == 26)
        rotor::rotor3 = 0;

    QChar test1 (number_to_abc[rotor::rotor3]);

   ui->slow_rotor_letter->setText(QString(test1));
}

void EnigDialog::on_slow_rotor_button_minus_pressed()
{
    rotor::rotor3--;

    if(rotor::rotor3 == -1)
        rotor::rotor3 = 25;

    QChar test2 (number_to_abc[rotor::rotor3]);

   ui->slow_rotor_letter->setText(QString(test2));
}

void EnigDialog::on_middle_rotor_button_plus_pressed()
{
    rotor::rotor2++;

    if(rotor::rotor2 == 26)
        rotor::rotor2 = 0;

    QChar test2 (number_to_abc[rotor::rotor2]);

   ui->middle_rotor_letter->setText(QString(test2));
}

void EnigDialog::on_middle_rotor_button_minus_pressed()
{
    rotor::rotor2--;

    if(rotor::rotor2 == -1)
        rotor::rotor2 = 25;

    QChar test2 (number_to_abc[rotor::rotor2]);

   ui->middle_rotor_letter->setText(QString(test2));
}

void EnigDialog::on_fast_rotor_button_plus_pressed()
{
    rotor::rotor1++;

    if(rotor::rotor1 == 26)
        rotor::rotor1 = 0;

    QChar test1 (number_to_abc[rotor::rotor1]);



   ui->fast_rotor_letter->setText(QString(test1));
}

void EnigDialog::on_fast_rotor_button_minus_pressed()
{
    rotor::rotor1--;

    if(rotor::rotor1 == -1)
        rotor::rotor1 = 25;

    QChar test2 (number_to_abc[rotor::rotor1]);

   ui->fast_rotor_letter->setText(QString(test2));
}

void EnigDialog::on_Encrypt_Button_pressed()
{
    //Заполняем контейнеры с использованием коммутационной панели

    is_up.clear(); //очистили контейнер показывающий, в каком положении
    // была записана буква

    if(input.size()%2 != 0 && input.size() != 0 )
        input.pop_back();

    for (int i = 0; i < input.size(); i += 2) //pair A-B and B-A is equal
    {
         plug_board[input[i + 1]] = input[i];
         plug_board[input[i]] = input[i + 1];
    }

    QString str=ui->input_text->toPlainText();

    std::string input_text = str.toStdString();

    std::string result_enc = "";


    for(int i = 0;i<input_text.size();i++)
    {
        if(isupper(input_text[i]))
            is_up.push_back(true);
        else
            is_up.push_back(false);



        input_text[i] = toupper(input_text[i]);

        if (plug_board.find(input_text[i]) != plug_board.end())
        {
            input_text[i]= plug_board[input_text[i]];
            // Здесь ищем среди введенных на плуге
            //а дальше буква идет в шифратор encryption(char)
        }

        result_enc += encryption(input_text[i]);
    }
    str = QString::fromUtf8(result_enc.c_str());


   QChar test3 (number_to_abc[rotor::rotor3]);
     ui->slow_rotor_letter->setText(QString(test3));

   QChar test2 (number_to_abc[rotor::rotor2]);
     ui->middle_rotor_letter->setText(QString(test2));


   QChar test1 (number_to_abc[rotor::rotor1]);
     ui->fast_rotor_letter->setText(QString(test1));

    ui->output_text->setText(str);
}

void EnigDialog::on_Dencrypt_Button_pressed()
{
    //Заполняем контейнеры с использованием коммутационной панели

     if(input.size()%2 != 0 && input.size() != 0 )
        input.pop_back();

    for (int i = 0; i < input.size(); i += 2)
    {
         plug_board[input[i + 1]] = input[i];
         plug_board[input[i]] = input[i + 1];
    }


    QString str=ui->input_text->toPlainText();

    std::string input_text = str.toStdString();

    std::string result_dec = "";



    for(int i = 0;i<input_text.size();i++)
    {

        input_text[i] = toupper(input_text[i]);

        input_text[i] = decryption(input_text[i]);

        if (plug_board.find(input_text[i]) != plug_board.end())
        {
            input_text[i] = plug_board[input_text[i]];
            // Здесь ищем среди введенных на плуге
            //а дальше буква идет в шифратор encryption(char)
        }

        if(!is_up[i])
            input_text[i] = tolower(input_text[i]);

        result_dec += input_text[i] ;
    }

   str = QString::fromUtf8(result_dec.c_str());


   QChar test3 (number_to_abc[rotor::rotor3]);

   ui->slow_rotor_letter->setText(QString(test3));


   QChar test2 (number_to_abc[rotor::rotor2]);
     ui->middle_rotor_letter->setText(QString(test2));


   QChar test1 (number_to_abc[rotor::rotor1]);
     ui->fast_rotor_letter->setText(QString(test1));

    ui->output_text->setText(str);
}


// Функции заполнения роторов

void EnigDialog::on_slow_rotor_letter_textEdited(const QString &arg1)
{
    std::string temp = arg1.toStdString();
    rotor::rotor3 = abc_to_number[temp[0]];
    ui->slow_rotor_letter->setText(QString::fromStdString(temp));
}

void EnigDialog::on_slow_rotor_letter_textChanged(const QString &arg1)
{

    std::string temp = arg1.toStdString();
    rotor::rotor3 = abc_to_number[temp[0]];
     ui->slow_rotor_letter->setText(QString::fromStdString(temp));
}

void EnigDialog::on_middle_rotor_letter_textEdited(const QString &arg1)
{
    std::string temp = arg1.toStdString();
    rotor::rotor2 = abc_to_number[temp[0]];
    ui->middle_rotor_letter->setText(QString::fromStdString(temp));
}

void EnigDialog::on_middle_rotor_letter_textChanged(const QString &arg1)
{
    std::string temp = arg1.toStdString();
    rotor::rotor2 = abc_to_number[temp[0]];
    ui->middle_rotor_letter->setText(QString::fromStdString(temp));

}

void EnigDialog::on_fast_rotor_letter_textEdited(const QString &arg1)
{
    std::string temp = arg1.toStdString();
    rotor::rotor1 = abc_to_number[temp[0]];
    ui->fast_rotor_letter->setText(QString::fromStdString(temp));
}

void EnigDialog::on_fast_rotor_letter_textChanged(const QString &arg1)
{
    std::string temp = arg1.toStdString();
    rotor::rotor1 = abc_to_number[temp[0]];
    ui->fast_rotor_letter->setText(QString::fromStdString(temp));

}






void EnigDialog::on_Q_Button_pressed()
{
    if(input.size()<=20)
    {
        input.push_back('Q');

        if(begin)
        {
          plug_key+=QString("Q");// начало пары
          begin = false;
        }
          else if( !begin)
        {
            plug_key+= QString("-Q ");
            begin = true;
        }


        ui->Plug_board_monitor->setText(plug_key);

         on_off[abc_to_number['Q']] = false;
        ui->Q_Button->setEnabled(on_off[abc_to_number['Q']]);
    }

}

void EnigDialog::on_W_Button_pressed()
{
     if(input.size()<=20)
     {
         input.push_back('W');



         if(begin)
         {
           plug_key+=QString("W");// начало пары
           begin = false;
         }
           else if( !begin)
         {
             plug_key+= QString("-W ");
             begin = true;
         }

         ui->Plug_board_monitor->setText(plug_key);

          on_off[abc_to_number['W']] = false;
         ui->W_Button->setEnabled(on_off[abc_to_number['W']]);
     }



}

void EnigDialog::on_E_Button_pressed()
{
     if(input.size()<=20)
     {
         input.push_back('E');

         if(begin)
         {
           plug_key+=QString("E");// начало пары
           begin = false;
         }
           else if( !begin)
         {
             plug_key+= QString("-E ");
             begin = true;
         }

         ui->Plug_board_monitor->setText(plug_key);

         on_off[abc_to_number['E']] = false;
         ui->E_Button->setEnabled(on_off[abc_to_number['E']]);
     }




} //std::vector<bool>last_entered_button

void EnigDialog::on_R_Button_pressed()
{
         if(input.size()<=20)
         {
             input.push_back('R');

             if(begin)
             {
               plug_key+=QString("R");// начало пары
               begin = false;
             }
               else if( !begin)
             {
                 plug_key+= QString("-R ");
                 begin = true;
             }
             // A-B C-D R-Q
               ui->Plug_board_monitor->setText(plug_key);

                on_off[abc_to_number['R']] = false;
               ui->R_Button->setEnabled(on_off[abc_to_number['R']]);
         }



}

void EnigDialog::on_Delete_button_pressed() //в самый низ
{
    if(input.size() != 0)
    {
        char q  = input[input.size()-1];

        input.pop_back();

        on_off[abc_to_number[q]] = true;

        if(begin == true)
        {
            plug_key.resize(plug_key.size() - 3);
            begin = false; //потенциальная ошибка из за размера
        }
        else if(begin == false)
        {
            plug_key.resize(plug_key.size() - 1);
            begin = true;
        }
    }
    else if(plug_key.size() <=1)
    {
        plug_key.clear();
        input.clear();
        plug_board.clear();
        for(auto &x : on_off) x = true;

    }
   ui->Plug_board_monitor->setText(plug_key);
  // Список обновления всех кнопок
   ui->Q_Button->setEnabled(on_off[abc_to_number['Q']]);
   ui->W_Button->setEnabled(on_off[abc_to_number['W']]);
   ui->E_Button->setEnabled(on_off[abc_to_number['E']]);
   ui->R_Button->setEnabled(on_off[abc_to_number['R']]);
   ui->T_Button->setEnabled(on_off[abc_to_number['T']]);
   ui->Z_Button->setEnabled(on_off[abc_to_number['Z']]);
   ui->U_Button->setEnabled(on_off[abc_to_number['U']]);
   ui->I_Button->setEnabled(on_off[abc_to_number['I']]);
   ui->O_Button->setEnabled(on_off[abc_to_number['O']]);
   //----------------------------------------------------
   ui->A_Button->setEnabled(on_off[abc_to_number['A']]);
   ui->S_Button->setEnabled(on_off[abc_to_number['S']]);
   ui->D_Button->setEnabled(on_off[abc_to_number['D']]);
   ui->F_Button->setEnabled(on_off[abc_to_number['F']]);
   ui->G_Button->setEnabled(on_off[abc_to_number['G']]);
   ui->H_Button->setEnabled(on_off[abc_to_number['H']]);
   ui->J_Button->setEnabled(on_off[abc_to_number['J']]);
   ui->K_Button->setEnabled(on_off[abc_to_number['K']]);

  //----------------------------------------------------
   ui->P_Button->setEnabled(on_off[abc_to_number['P']]);
   ui->Y_Button->setEnabled(on_off[abc_to_number['Y']]);
   ui->X_Button->setEnabled(on_off[abc_to_number['X']]);
   ui->C_Button->setEnabled(on_off[abc_to_number['C']]);
   ui->V_Button->setEnabled(on_off[abc_to_number['V']]);
   ui->B_Button->setEnabled(on_off[abc_to_number['B']]);
   ui->N_Button->setEnabled(on_off[abc_to_number['N']]);
   ui->M_Button->setEnabled(on_off[abc_to_number['M']]);
   ui->L_Button->setEnabled(on_off[abc_to_number['L']]);

}

void EnigDialog::on_T_Button_pressed()
{
      if(input.size()<=20)
      {
          input.push_back('T');

          if(begin)
          {
            plug_key+=QString("T");// начало пары
            begin = false;
          }
            else if( !begin)
          {
              plug_key+= QString("-T ");
              begin = true;
          }
          // A-B C-D R-Q
            ui->Plug_board_monitor->setText(plug_key);

             on_off[abc_to_number['T']] = false;
            ui->T_Button->setEnabled(on_off[abc_to_number['T']]);
      }


}

void EnigDialog::on_Z_Button_pressed()
{
      if(input.size()<=20)
      {
          input.push_back('Z');

          if(begin)
          {
            plug_key+=QString("Z");// начало пары
            begin = false;
          }
            else if( !begin)
          {
              plug_key+= QString("-Z ");
              begin = true;
          }
          // A-B C-D R-Q
            ui->Plug_board_monitor->setText(plug_key);

            on_off[abc_to_number['Z']] = false;
            ui->Z_Button->setEnabled(on_off[abc_to_number['Z']]);
      }

}

void EnigDialog::on_U_Button_pressed()
{
     if(input.size()<=20)
     {
         input.push_back('U');

         if(begin)
         {
           plug_key+=QString("U");// начало пары
           begin = false;
         }
           else if( !begin)
         {
             plug_key+= QString("-U ");
             begin = true;
         }
         // A-B C-D R-Q
           ui->Plug_board_monitor->setText(plug_key);

            on_off[abc_to_number['U']] = false;
           ui->U_Button->setEnabled(on_off[abc_to_number['U']]);
     }

}

void EnigDialog::on_I_Button_pressed()
{
     if(input.size()<=20)
     {
         input.push_back('I');

         if(begin)
         {
           plug_key+=QString("I");// начало пары
           begin = false;
         }
           else if( !begin)
         {
             plug_key+= QString("-I ");
             begin = true;
         }
         // A-B C-D R-Q
           ui->Plug_board_monitor->setText(plug_key);

            on_off[abc_to_number['I']] = false;
           ui->I_Button->setEnabled(on_off[abc_to_number['I']]);
     }

}

void EnigDialog::on_O_Button_pressed()
{
     if(input.size()<=20)
     {
         input.push_back('O');

         if(begin)
         {
           plug_key+=QString("O");// начало пары
           begin = false;
         }
           else if( !begin)
         {
             plug_key+= QString("-O ");
             begin = true;
         }
         // A-B C-D R-Q
           ui->Plug_board_monitor->setText(plug_key);

            on_off[abc_to_number['O']] = false;
           ui->O_Button->setEnabled(on_off[abc_to_number['O']]);
     }

}

void EnigDialog::on_A_Button_pressed()
{
    if(input.size()<=20)
    {
        input.push_back('A');

        if(begin)
        {
          plug_key+=QString("A");// начало пары
          begin = false;
        }
          else if( !begin)
        {
            plug_key+= QString("-A ");
            begin = true;
        }
        // A-B C-D R-Q
          ui->Plug_board_monitor->setText(plug_key);

           on_off[abc_to_number['A']] = false;
          ui->A_Button->setEnabled(on_off[abc_to_number['A']]);
    }

}

void EnigDialog::on_S_Button_pressed()
{
    if(input.size()<=20)
    {
        input.push_back('S');

        if(begin)
        {
          plug_key+=QString("S");// начало пары
          begin = false;
        }
          else if( !begin)
        {
            plug_key+= QString("-S ");
            begin = true;
        }
        // A-B C-D R-Q
          ui->Plug_board_monitor->setText(plug_key);

           on_off[abc_to_number['S']] = false;
          ui->S_Button->setEnabled(on_off[abc_to_number['S']]);
    }

}

void EnigDialog::on_D_Button_pressed()
{
    if(input.size()<=20)
    {
        input.push_back('D');

        if(begin)
        {
          plug_key+=QString("D");// начало пары
          begin = false;
        }
          else if( !begin)
        {
            plug_key+= QString("-D ");
            begin = true;
        }
        // A-B C-D R-Q
          ui->Plug_board_monitor->setText(plug_key);

           on_off[abc_to_number['D']] = false;
          ui->D_Button->setEnabled(on_off[abc_to_number['D']]);
    }
}

void EnigDialog::on_F_Button_pressed()
{
    if(input.size()<=20)
    {
        input.push_back('F');

        if(begin)
        {
          plug_key+=QString("F");// начало пары
          begin = false;
        }
          else if( !begin)
        {
            plug_key+= QString("-F ");
            begin = true;
        }
        // A-B C-D R-Q
          ui->Plug_board_monitor->setText(plug_key);

           on_off[abc_to_number['F']] = false;
          ui->F_Button->setEnabled(on_off[abc_to_number['F']]);
    }
}

void EnigDialog::on_G_Button_pressed()
{
    if(input.size()<=20)
    {
        input.push_back('G');

        if(begin)
        {
          plug_key+=QString("G");// начало пары
          begin = false;
        }
          else if( !begin)
        {
            plug_key+= QString("-G ");
            begin = true;
        }
        // A-B C-D R-Q
          ui->Plug_board_monitor->setText(plug_key);

           on_off[abc_to_number['G']] = false;
          ui->G_Button->setEnabled(on_off[abc_to_number['G']]);
    }
}

void EnigDialog::on_H_Button_pressed()
{
    if(input.size()<=20)
    {
        input.push_back('H');

        if(begin)
        {
          plug_key+=QString("H");// начало пары
          begin = false;
        }
          else if( !begin)
        {
            plug_key+= QString("-H ");
            begin = true;
        }
        // A-B C-D R-Q
          ui->Plug_board_monitor->setText(plug_key);

           on_off[abc_to_number['H']] = false;
          ui->H_Button->setEnabled(on_off[abc_to_number['H']]);
    }
}

void EnigDialog::on_J_Button_pressed()
{
    if(input.size()<=20)
    {
        input.push_back('J');

        if(begin)
        {
          plug_key+=QString("J");// начало пары
          begin = false;
        }
          else if( !begin)
        {
            plug_key+= QString("-J ");
            begin = true;
        }
        // A-B C-D R-Q
          ui->Plug_board_monitor->setText(plug_key);

           on_off[abc_to_number['J']] = false;
          ui->J_Button->setEnabled(on_off[abc_to_number['J']]);
    }
}

void EnigDialog::on_K_Button_pressed()
{
    if(input.size()<=20)
    {
        input.push_back('K');

        if(begin)
        {
          plug_key+=QString("K");// начало пары
          begin = false;
        }
          else if( !begin)
        {
            plug_key+= QString("-K ");
            begin = true;
        }
        // A-B C-D R-Q
          ui->Plug_board_monitor->setText(plug_key);

           on_off[abc_to_number['K']] = false;
          ui->K_Button->setEnabled(on_off[abc_to_number['K']]);
    }
}


//---------------------------------------



void EnigDialog::on_P_Button_pressed()
{
    if(input.size()<=20)
    {
        input.push_back('P');

        if(begin)
        {
          plug_key+=QString("P");// начало пары
          begin = false;
        }
          else if( !begin)
        {
            plug_key+= QString("-P ");
            begin = true;
        }
        // A-B C-D R-Q
          ui->Plug_board_monitor->setText(plug_key);

           on_off[abc_to_number['P']] = false;
          ui->P_Button->setEnabled(on_off[abc_to_number['P']]);
    }
}

void EnigDialog::on_Y_Button_pressed()
{
    if(input.size()<=20)
    {
        input.push_back('Y');

        if(begin)
        {
          plug_key+=QString("Y");// начало пары
          begin = false;
        }
          else if( !begin)
        {
            plug_key+= QString("-Y ");
            begin = true;
        }
        // A-B C-D R-Q
          ui->Plug_board_monitor->setText(plug_key);

           on_off[abc_to_number['Y']] = false;
          ui->Y_Button->setEnabled(on_off[abc_to_number['Y']]);
    }
}

void EnigDialog::on_X_Button_pressed()
{
    if(input.size()<=20)
    {
        input.push_back('X');

        if(begin)
        {
          plug_key+=QString("X");// начало пары
          begin = false;
        }
          else if( !begin)
        {
            plug_key+= QString("-X ");
            begin = true;
        }
        // A-B C-D R-Q
          ui->Plug_board_monitor->setText(plug_key);

           on_off[abc_to_number['X']] = false;
          ui->X_Button->setEnabled(on_off[abc_to_number['X']]);
    }
}

void EnigDialog::on_C_Button_pressed()
{
    if(input.size()<=20)
    {
        input.push_back('C');

        if(begin)
        {
          plug_key+=QString("C");// начало пары
          begin = false;
        }
          else if( !begin)
        {
            plug_key+= QString("-C ");
            begin = true;
        }
        // A-B C-D R-Q
          ui->Plug_board_monitor->setText(plug_key);

           on_off[abc_to_number['C']] = false;
          ui->C_Button->setEnabled(on_off[abc_to_number['C']]);
    }
}

void EnigDialog::on_V_Button_pressed()
{
    if(input.size()<=20)
    {
        input.push_back('V');

        if(begin)
        {
          plug_key+=QString("V");// начало пары
          begin = false;
        }
          else if( !begin)
        {
            plug_key+= QString("-V ");
            begin = true;
        }
        // A-B C-D R-Q
          ui->Plug_board_monitor->setText(plug_key);

           on_off[abc_to_number['V']] = false;
          ui->V_Button->setEnabled(on_off[abc_to_number['V']]);
    }
}

void EnigDialog::on_B_Button_pressed()
{
    if(input.size()<=20)
    {
        input.push_back('B');

        if(begin)
        {
          plug_key+=QString("B");// начало пары
          begin = false;
        }
          else if( !begin)
        {
            plug_key+= QString("-B ");
            begin = true;
        }
        // A-B C-D R-Q
          ui->Plug_board_monitor->setText(plug_key);

           on_off[abc_to_number['B']] = false;
          ui->B_Button->setEnabled(on_off[abc_to_number['B']]);
    }
}

void EnigDialog::on_N_Button_pressed()
{
    if(input.size()<=20)
    {
        input.push_back('N');

        if(begin)
        {
          plug_key+=QString("N");// начало пары
          begin = false;
        }
          else if( !begin)
        {
            plug_key+= QString("-N ");
            begin = true;
        }
        // A-B C-D R-Q
          ui->Plug_board_monitor->setText(plug_key);

           on_off[abc_to_number['N']] = false;
          ui->N_Button->setEnabled(on_off[abc_to_number['N']]);
    }
}

void EnigDialog::on_M_Button_pressed()
{
    if(input.size()<=20)
    {
        input.push_back('M');

        if(begin)
        {
          plug_key+=QString("M");// начало пары
          begin = false;
        }
          else if( !begin)
        {
            plug_key+= QString("-M ");
            begin = true;
        }
        // A-B C-D R-Q
          ui->Plug_board_monitor->setText(plug_key);

           on_off[abc_to_number['M']] = false;
          ui->M_Button->setEnabled(on_off[abc_to_number['M']]);
    }
}

void EnigDialog::on_L_Button_pressed()
{
    if(input.size()<=20)
    {
        input.push_back('L');

        if(begin)
        {
          plug_key+=QString("L");// начало пары
          begin = false;
        }
          else if( !begin)
        {
            plug_key+= QString("-L ");
            begin = true;
        }
        // A-B C-D R-Q
          ui->Plug_board_monitor->setText(plug_key);

           on_off[abc_to_number['L']] = false;
          ui->L_Button->setEnabled(on_off[abc_to_number['L']]);
    }
}

void EnigDialog::on_clear_panel_pressed()
{
    input.clear();
    plug_key.clear();
    plug_board.clear();

    begin = true;

    ui->Plug_board_monitor->clear();
    for(auto &x : on_off)x = true;

    ui->Q_Button->setEnabled(on_off[abc_to_number['Q']]);
    ui->W_Button->setEnabled(on_off[abc_to_number['W']]);
    ui->E_Button->setEnabled(on_off[abc_to_number['E']]);
    ui->R_Button->setEnabled(on_off[abc_to_number['R']]);
    ui->T_Button->setEnabled(on_off[abc_to_number['T']]);
    ui->Z_Button->setEnabled(on_off[abc_to_number['Z']]);
    ui->U_Button->setEnabled(on_off[abc_to_number['U']]);
    ui->I_Button->setEnabled(on_off[abc_to_number['I']]);
    ui->O_Button->setEnabled(on_off[abc_to_number['O']]);
    //----------------------------------------------------
    ui->A_Button->setEnabled(on_off[abc_to_number['A']]);
    ui->S_Button->setEnabled(on_off[abc_to_number['S']]);
    ui->D_Button->setEnabled(on_off[abc_to_number['D']]);
    ui->F_Button->setEnabled(on_off[abc_to_number['F']]);
    ui->G_Button->setEnabled(on_off[abc_to_number['G']]);
    ui->H_Button->setEnabled(on_off[abc_to_number['H']]);
    ui->J_Button->setEnabled(on_off[abc_to_number['J']]);
    ui->K_Button->setEnabled(on_off[abc_to_number['K']]);

   //----------------------------------------------------
    ui->P_Button->setEnabled(on_off[abc_to_number['P']]);
    ui->Y_Button->setEnabled(on_off[abc_to_number['Y']]);
    ui->X_Button->setEnabled(on_off[abc_to_number['X']]);
    ui->C_Button->setEnabled(on_off[abc_to_number['C']]);
    ui->V_Button->setEnabled(on_off[abc_to_number['V']]);
    ui->B_Button->setEnabled(on_off[abc_to_number['B']]);
    ui->N_Button->setEnabled(on_off[abc_to_number['N']]);
    ui->M_Button->setEnabled(on_off[abc_to_number['M']]);
    ui->L_Button->setEnabled(on_off[abc_to_number['L']]);
}


