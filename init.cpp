#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>
#include <filesystem>
using json = nlohmann::json;
namespace fs = std::filesystem;

int main(){
    std::cout << "Tamagotchi"<< std::endl;
    
    fs::path check = "tomodachis/info.json";
    std::cout << "Current Path: " << std::filesystem::current_path() << std::endl;

    if(!exists(check)){
        json test{R"({
            "listed": 0
            })"_json};
        std::fstream Info;
        Info.open(R"(/home/tzunem/Desktop/tamagotchi/tamagotchi/tomodachis/info.json)",std::ios::out);
        Info << test;
        Info.close();
    }
        
    return 0;
}