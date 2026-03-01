#include "json.hpp"
#include <fstream>
#include <iostream>
#include <filesystem>

using json = nlohmann::json;
namespace fs = std::filesystem;

int main() {
    fs::path infofile = "info.json"; 
    std::fstream Info;
    json infoObject;
    std::cout << "Tamagotchi" << std::endl;
    std::cout << "Current Path: " << fs::current_path() << std::endl;
    /*make sure general info exists*/
    if (!fs::exists(infofile)) {
        json createInformation = { {"existingTomos", 0} };
        Info.open(infofile, std::ios::out);
        Info << createInformation.dump(4);  
        Info.close();
    }
    /*check how many pets are saved*/
    if(!fs::is_empty("tomodachis")){
        Info.open(infofile, std::ios::in | std::ios::out);
        Info >> infoObject;
        infoObject["existingTomos"] = 0;
        for(auto i : fs::directory_iterator("tomodachis"))
            infoObject["existingTomos"] = infoObject.value("existingTomos", 0) + 1;
        Info.seekp(0);
        Info << infoObject.dump(4);  
        Info.close();
    }
    else{
        std::string petname;
        
        std::cout << "Seems like you don't have a pet, so lets get you one." << std::endl;
        std::cout << "What should be the name of your friend?: ";
        std::cin >> petname;
        
        
    }
    /*create new pet if one doesnt exist*/

    return 0;
}