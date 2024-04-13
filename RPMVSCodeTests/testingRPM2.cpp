#include <iostream>
#include <fstream>
#include <vector>
#include <string>

int main() {
    // RPM1 = 2x Progress Bars
    int RPMVal = 135; // Have rmp brought down from 13,500 --> 135 (so divided by 100)
    if (RPMVal <= 100) { // GREEN Progress Bar
        std::cout << "p1.val=" + std::to_string(RPMVal) << std::endl;
        std::cout << "p2.val=0" << std::endl;
        //Serial.print("p1.val=" + String(RPMVal));
        //Serial.write(0xff); Serial.write(0xff); Serial.write(0xff);
    } else if (RPMVal > 100) { // RED
        int RPMP2 = (RPMVal % 100); 
        std::cout << std::to_string(RPMP2) << std::endl;
        std::cout << std::to_string(RPMP2) << std::endl;
        //std::cout << std::to_string(RPMVal) << std::endl;
        int RPMP1 = (RPMVal - RPMP2);
        RPMP2 = (RPMP2 * 100) / 35;
        std::cout << "p1.val=" + std::to_string(RPMP1) << std::endl;
        //Serial.print("p1.val=" + String(RPMP2)); 
        //Serial.write(0xff); Serial.write(0xff); Serial.write(0xff);
        std::cout << "p2.val=" + std::to_string(RPMP2) << std::endl;
        //Serial.print("p2.val=" + String(RPMP2));
        //Serial.write(0xff); Serial.write(0xff); Serial.write(0xff);
    }
}

