#include "json.hpp"
#include "tomocreate.h"
#include <fstream>
#include <iostream>
#include <filesystem>
#include <random>
using json = nlohmann::json;
namespace fs = std::filesystem;

int main() {
    fs::path infofile = "info.json";
    fs::create_directories("tomodachis"); 
    std::fstream Info, petCreation;
    json infoObject,petObject;
    /*random generator*/
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1,5);
    /*actual start*/
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
        std::cout << "Seems like you don't have a pet, so lets get you one." << std::endl;
    /*create new pet if one doesnt exist*/
        createtomo();
    }
    createtomo();
    return 0;
}