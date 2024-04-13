#include <iostream>
#include <fstream>
#include <vector>
#include <string>

// This is a loop that occurs with every instance of RPM sent by the CAN board
// For every value of RPM, this will iterate and set each bar to the correct value

int main() {
    int RPMVal = 135; // // Have rmp brought down from 13,500 --> 135 (so divided by 100)
    std::vector<std::string> rpmBars = {"j0", "j1", "j2", "j3", "j4", "j5", "j6", "j7", "j8", "j9", "j10", "j11", "j12", "j13", "j14", "j15", "j16", "j17", "j18", "j19", "j20", "j21", "j22", "j23", "j24", "j25", "j26"};
    std::cout << "THIS IS PRINTING" << std::endl;
    int RPMBarVal;
    for (size_t i = 0; i < rpmBars.size(); ++i) {
        std::cout << i << std::endl;
        //std::cout << RPMVal << std::endl;
        int low = (i*5);
        int high = (low + 5);
        std::cout << low << std::endl;
        std::cout << high << std::endl;
        if ((RPMVal > low)) { //& (RPMVal <= high)
            RPMBarVal = 100;
        } else {
            RPMBarVal = 0;
        }
        std::cout << rpmBars[i] + ".val=" + std::to_string(RPMBarVal) << std::endl;
        //write(0xff); write(0xff); write(0xff);
    }
}

// RPM2 = 27x Progress Bars
  
  // Ranges:
  // {0, 1, 2, 3, 4, 5...}
  // {0-5, 6-10, 11-15...}