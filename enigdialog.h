#ifndef ENIGDIALOG_H
#define ENIGDIALOG_H

#include <QDialog>

namespace Ui {
class EnigDialog;
}

class EnigDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EnigDialog(QWidget *parent = 0);
    ~EnigDialog();

private slots:

// шифрование без учета коммутационной панели

    void on_slow_rotor_button_plus_pressed();

    void on_slow_rotor_button_minus_pressed();

    void on_middle_rotor_button_plus_pressed();

    void on_middle_rotor_button_minus_pressed();

    void on_fast_rotor_button_plus_pressed();

    void on_fast_rotor_button_minus_pressed();

    void on_Encrypt_Button_pressed();

    void on_pushButton_2_pressed();
//--------------------------------------------------


    void on_slow_rotor_letter_textEdited(const QString &arg1);

    void on_slow_rotor_letter_textChanged(const QString &arg1);

    void on_middle_rotor_letter_textEdited(const QString &arg1);

    void on_middle_rotor_letter_textChanged(const QString &arg1);

    void on_fast_rotor_letter_textEdited(const QString &arg1);

    void on_fast_rotor_letter_textChanged(const QString &arg1);
//---------------------------------------------------------------

    void on_Q_Button_pressed();

    void on_W_Button_pressed();

    void on_E_Button_pressed();

    void on_R_Button_pressed();

    void on_Delete_button_pressed();

    void on_T_Button_pressed();

    void on_Z_Button_pressed();

    void on_U_Button_pressed();

    void on_I_Button_pressed();

    void on_O_Button_pressed();

    void on_A_Button_pressed();

    void on_S_Button_pressed();

    void on_D_Button_pressed();

    void on_F_Button_pressed();

    void on_G_Button_pressed();

    void on_H_Button_pressed();

    void on_J_Button_pressed();

    void on_K_Button_pressed();

    void on_P_Button_pressed();

    void on_Y_Button_pressed();

    void on_X_Button_pressed();

    void on_C_Button_pressed();

    void on_V_Button_pressed();

    void on_B_Button_pressed();

    void on_N_Button_pressed();

    void on_M_Button_pressed();

    void on_L_Button_pressed();

    void on_clear_panel_pressed();

private:
    Ui::EnigDialog *ui;
};


#endif // ENIGDIALOG_H
