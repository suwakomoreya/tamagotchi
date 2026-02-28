#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>
#include <filesystem>
using json = nlohmann::json;
namespace fs = std::filesystem;

int main(){
    std::cout << "Tamagotchi"<< std::endl;
    std::string answer;
    
    fs::path check = "tomodachis/info.json";
    std::cout << check;
    if(!fs::exists("info.json")){
        json test{R"({
            "existing": 0,
            "alive"
            })"_json};

        std::fstream Info;
        Info.open(R"(/home/Tzunem/Desktop/tamagotchi/tamagotchi/info.json)",std::ios::out);
        Info << test;
        Info.close();
    }
    if(fs::is_empty("tomodachis")){
        json tomotemplate{R"({
            "alive": true,
            "Health": 100,
            "Hunger": [{
                "Thirst": 25,
                "Hungery: 25
            }],
            "Entertainment": 50,
            })"_json};
        std::cout << "Name: ";
        json pet{json::parse(tomotemplate)}
        std::fstream Name;
        Name.open(R"(/home/Tzunem/Desktop/tamagotchi/tamagotchi/tomodachi/pet.json)",std::ios::out);
        Name << tomotemplate;
        Name.close();
    }
    std::cout << "-----------";
    std::cout << "Newfile: c " << std::endl;
    std::cin >> answer;
    
    return 0;
}