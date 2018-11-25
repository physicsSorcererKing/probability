// This program is counting the cost of Ice Flower Charm +0 to MAX(+10).
#include <iostream>
#include <algorithm>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

void ChooseItem();

bool QuickStartMode();

void InputWarning();

void TestIceFlowerCharm();
void TestGuildRing();

void GambleIceFlowerCharm(int*, const int, const int, const double, const double);
void GambleGuildRing(int*, const int, const int, const double);


int main()
{
    //Title
    cout << "Cost Prediction of La Tale Online v1.0.0" << endl
        << "Copyright (C) 2018 PSK(Pilisenk) - All rights reserved." << endl;

    srand( (unsigned)time(NULL) );

    ChooseItem();

    cout << "Good-bye!" << endl;
    system("pause");
    return 0;
}

void ChooseItem(){
    char item_number;
    bool try_again = true;

    while(try_again){
        //Choose what you wnat to test
        cout << "Choose the item you want to test:" << endl
            << "(1)Ice Flower Charm (2)Guild Ring (0)exit" << endl
            << "Ans: ";
        cin >> item_number;

        switch(item_number){
            case '0':
                try_again = false;
                break;
            case '1':
                TestIceFlowerCharm();
                break;
            case '2':
                TestGuildRing();
                break;
            default:
                cout << "Input error! Please try again." << endl << endl;
        }
    }
}

bool QuickStartMode(){
    char c;

    while(true){
        cout << "Use Quick Start Mode?(y/n)" << endl
            << "Ans: ";

        cin >> c;

        switch(c){
            case 'y':
            case 'Y':
                return true;
            case 'n':
            case 'N':
                return false;
            default:
                cout << "Input error! Please try again." << endl << endl;
        }
    }
}

void InputWarning() {
    cout << "[Attention]Input unsuitable value may get the wrnog informations or force this program shut down." << endl;
}

void TestIceFlowerCharm(){
    //cout << "Run: TestIceFlowerCharm()" << endl;

    //Basic Setting
    int upgrade_level;                      //想要的強化階段(請修改0-10)
    double item_cost;                       //每個冰花環的成本(TWD)
    int sample_amount;                      //取樣數量
    const double kProbOneToNine  = 0.55;    //1-9強化成功機率(目前是固定機率，不受藥水稱號裝備寵物等鑲嵌提升手段影響)
    const double kProbMax = 0.1;            //MAX強化成功機率(目前是固定機率，不受藥水稱號裝備寵物等鑲嵌提升手段影響)

    if   (QuickStartMode()) {
        upgrade_level = 10;
        item_cost = 99;
        sample_amount = 100000;
    }
    else {
        InputWarning();

        cout << "Please input upgrade level you want to test:(0-10, 10 means +MAX)" << endl
            << "Ans: ";
        cin >> upgrade_level;

        cout << "Please input the cost(TWD) of one \"Ice Flower Charm\":" << endl
            << "Ans: ";
        cin >> item_cost;

        cout << "Please input how many samples you want to test:(1-500000, may cause error if this value is too high)" << endl
            << "Ans: ";
        cin >> sample_amount;
    }

    cout << "======================Cost of Ice Flower Charm=======================\n"
        << "test level: +" << upgrade_level << " (+10 means MAX)" << endl
        << "cost per item: " << item_cost << " TWD" << endl
        << "sample amount(too high will cause error): " << sample_amount << endl
        << "=====================================================================\n";

    //
    int samples[sample_amount];
    GambleIceFlowerCharm(samples, sample_amount, upgrade_level, kProbOneToNine, kProbMax);

    sort(samples, samples+sample_amount);

    /*//for debug
    cout << "sorted arr: ";
    for  (int i=0; i < sample_amount; ++i) {
        cout << samples[i] << ",";
    }
    cout << endl << endl;*/
    int sample_average = samples[(int)(sample_amount*0.5)];
    int sample_15865 = samples[(int)(sample_amount*0.15865)];
    int sample_84135 = samples[(int)(sample_amount*0.84135)];
    int sample_02275 = samples[(int)(sample_amount*0.02275)];
    int sample_97725 = samples[(int)(sample_amount*0.97725)];
    int sample_00135 = samples[(int)(sample_amount*0.00135)];
    int sample_99865 = samples[(int)(sample_amount*0.99865)];

    //Output the Standard deviation and coverage
    cout << "Result(empirical rule):" << endl
        << "Average cost: " << sample_average << "(" << sample_average * item_cost << " TWD)" << endl
        << "68.27% within: " << sample_15865 << "(" << sample_15865 * item_cost << " TWD)" << " to " << sample_84135 << "(" << sample_84135 * item_cost << " TWD)" << endl
        << "95.45% within: " << sample_02275 << "(" << sample_02275 * item_cost << " TWD)" << " to " << sample_97725 << "(" << sample_97725 * item_cost << " TWD)" << endl
        << "99.73% within: " << sample_00135 << "(" << sample_00135 * item_cost << " TWD)" << " to " << sample_99865 << "(" << sample_99865 * item_cost << " TWD)" << endl
        << "=====================================================================\n";
}

void TestGuildRing(){
    //cout << "Run: TestGuildRing()" << endl;

    //Basic Setting
    int upgrade_level;                      //想要的強化階段(請修改0-10)
    double item_cost;                       //每件公會戒指的成本(TWD)
    int sample_amount;                      //取樣數量
    const double kBasicProb = 0.6;          //基礎強化成功機率
    int buff_prob_percentage;               //Buff強化成功機率(單位: %)(含藥水等所有手段)

    if   (QuickStartMode()) {
        upgrade_level = 9;
        item_cost = 82;
        buff_prob_percentage = 10;
        sample_amount = 100000;
    }
    else {
        InputWarning();

        cout << "Please input upgrade level you want to test:(0-9)" << endl
            << "Ans: ";
        cin >> upgrade_level;

        cout << "Please input the cost(TWD) of one \"Guild Ring\":" << endl
            << "Ans: ";
        cin >> item_cost;

        cout << "Please input your extra probability buff value(%):(0-17)" << endl
            << "Ans: ";
        cin >> buff_prob_percentage;

        cout << "Please input how many samples you want to test:(1-500000, may cause error if this value is too high)" << endl
            << "Ans: ";
        cin >> sample_amount;
    }

    cout << "=========================Cost of Guild Ring==========================\n"
        << "test level: +" << upgrade_level << endl
        << "cost per item: " << item_cost << " TWD" << endl
        << "extra probability buff: +" << buff_prob_percentage << "%" << endl
        << "sample amount(too high will cause error): " << sample_amount << endl
        << "=====================================================================\n";

    int samples[sample_amount];
    GambleGuildRing(samples, sample_amount, upgrade_level, kBasicProb + (double)buff_prob_percentage / 100);

    sort(samples, samples+sample_amount);

    /*//for debug
    cout << "sorted arr: ";
    for  (int i=0; i < sample_amount; ++i) {
        cout << samples[i] << ",";
    }
    cout << endl << endl;*/
    int sample_average = samples[(int)(sample_amount*0.5)];
    int sample_15865 = samples[(int)(sample_amount*0.15865)];
    int sample_84135 = samples[(int)(sample_amount*0.84135)];
    int sample_02275 = samples[(int)(sample_amount*0.02275)];
    int sample_97725 = samples[(int)(sample_amount*0.97725)];
    int sample_00135 = samples[(int)(sample_amount*0.00135)];
    int sample_99865 = samples[(int)(sample_amount*0.99865)];

    //Output the Standard deviation and coverage
    cout << "Result(empirical rule, without the extra buff cost):" << endl
        << "Average cost: " << sample_average << "(" << sample_average * item_cost << " TWD or " << sample_average * 3 << " Days)" << endl
        << "68.27% within: " << sample_15865 << "(" << sample_15865 * item_cost << " TWD or " << sample_15865 * 3 << " Days)" << " to " << sample_84135 << "(" << sample_84135 * item_cost << " TWD or " << sample_84135 * 3 << " Days)" << endl
        << "95.45% within: " << sample_02275 << "(" << sample_02275 * item_cost << " TWD or " << sample_02275 * 3 << " Days)" << " to " << sample_97725 << "(" << sample_97725 * item_cost << " TWD or " << sample_97725 * 3 << " Days)" << endl
        << "99.73% within: " << sample_00135 << "(" << sample_00135 * item_cost << " TWD or " << sample_00135 * 3 << " Days)" << " to " << sample_99865 << "(" << sample_99865 * item_cost << " TWD or " << sample_99865 * 3 << " Days)" << endl
        << "=====================================================================\n";
}

void GambleIceFlowerCharm(int* arr, const int num_arr, const int target_upgrade_level, const double kProbOneToNine, const double kProbMax) {
    int current_upgrade_level = 0;              //目前強化階段
    int current_item_count = 1;                 //目前裝備消耗次數
    double current_upgrade_probability;         //目前強化機率

    for   ( int i=0; i < num_arr; ++i ) {
        while   ( current_upgrade_level < target_upgrade_level )
                {
                    ++current_item_count;
                    current_upgrade_probability = (current_upgrade_level < 9) ? kProbOneToNine : kProbMax;

                    //cout << current_upgrade_level;

                    if   ( (double)rand()/RAND_MAX > current_upgrade_probability ) {//When upgrade failed
                        if   (current_upgrade_level < 2) {
                                current_upgrade_level = 0;
                                //cout << " => " << current_upgrade_level;
                        }
                        if   (current_upgrade_level >= 2 && current_upgrade_level < 9) {
                            if   ( (double)rand()/RAND_MAX > 0.5 ) {
                                --current_upgrade_level;
                                //cout << " - 1 = " << current_upgrade_level;
                            }
                            else {
                                current_upgrade_level -= 2;
                                //cout << " - 2 = " << current_upgrade_level;
                            }
                        }
                    }
                    else {
                        ++current_upgrade_level;
                        //cout << " + 1 = " << current_upgrade_level;
                    }
                    //cout << "; cost: " << current_item_count << endl;
                }
        arr[i] = current_item_count;
        //cout << i << ": " << current_item_count << "Ice Flower used." << endl;//for debug

        //reset current value for next loop
        current_upgrade_level  = 0;
        current_item_count = 1;
    }
}

void GambleGuildRing(int* arr, const int num_arr, const int target_upgrade_level, const double kProb) {
    int current_upgrade_level = 0;              //目前強化階段
    int current_item_count = 1;                 //目前裝備消耗次數

    for   ( int i=0; i < num_arr; ++i ) {
        while   ( current_upgrade_level < target_upgrade_level )
                {
                    ++current_item_count;
                    current_upgrade_level = ((double)rand()/RAND_MAX > kProb) ? 0 : current_upgrade_level+1;
                    //cout << "; cost: " << current_item_count << endl;
                }
        arr[i] = current_item_count;
        //cout << i << ": " << current_item_count << "Guild Ring used." << endl;//for debug

        //reset current value for next loop
        current_upgrade_level  = 0;
        current_item_count = 1;
    }
}
