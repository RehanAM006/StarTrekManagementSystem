#include <iostream>
#include <string>
#include <fstream>
#include <thread>
#include <chrono>
#include <cmath>
#include <cstdlib>  // Add this to your includes for rand()
#include <ctime>    // Add this to your includes for time()
using namespace std;

struct Planet {
    string name;
    string description;
    int population;
    double defenseLevel;
};

void Greeting(){
    const char* asciiArt = R"(
  _   _  _____ _____   ______      _                       _          
| | | |/  ___/  ___| |  ___|    | |                     (_)         
| | | |\ `--.\ `--.  | |__ _ __ | |_ ___ _ __ _ __  _ __ _ ___  ___  
| | | | `--. \`--. \ |  __| '_ \| __/ _ \ '__| '_ \| '__| / __|/ _ \ 
| |_| |/\__/ /\__/ / | |__| | | | ||  __/ |  | |_) | |  | \__ \  __/ 
 \___/ \____/\____/  \____/_| |_|\__\___|_|  | .__/|_|  |_|___/\___| 
                                             | |                     
                                             |_|                     

  ____                                          _   __  __                                   _   
 / ___|___  _ __ ___  _ __ ___   __ _ _ __   __| | |  \/  | __ _ _ __   __ _  __ _  ___ _ __ ___| |_ 
| |   / _ \| '_ ` _ \| '_ ` _ \ / _` | '_ \ / _` | | |\/| |/ _` | '_ \ / _` |/ _` |/ _ \ '_ ` _ \ __|
| |__| (_) | | | | | | | | | | | (_| | | | | (_| | | |  | | (_| | | | | (_| | (_| |  __/ | | | | |_ 
 \____\___/|_| |_| |_|_| |_| |_|\__,_|_| |_|\__,_| |_|  |_|\__,_|_| |_|\__,_|\__, |\___|_| |_| |_|
                                                                            |___/                

  ____            _                 
 / ___| _   _ ___| |_ ___ _ __ ___   
 \___ \| | | / __| __/ _ \ '_ ` _ \  
  ___) | |_| \__ \ ||  __/ | | | | | 
 |____/ \__, |___/\__\___|_| |_| |_| 
        |___/  
)";
    cout << asciiArt << endl;
}

void Login(){
    string user = "Kirk";
    string pass = "Prosper";
    string inputUser, inputPass;
    int attempts = 0;
    int maxAttempts = 3;
    bool loginSuccessful = false;

    while (attempts < maxAttempts && !loginSuccessful)
    {
        cout << "Attempt " << (attempts + 1) << " of " << maxAttempts << endl;
        cout << "Enter username: ";
        cin >> inputUser;
        cout << "Enter password: ";
        cin >> inputPass;

        if (inputUser == user && inputPass == pass)
        {
            cout << "Login successful!" << endl;
            cout << "Welcome Captain Kirk!" << endl;
            loginSuccessful = true;
        }
        else
        {
            attempts++;
            if (attempts < maxAttempts)
            {
                cout << "Login failed. Please try again." << endl;
            }
            else
            {
                cout << "Login failed. Maximum attempts reached. Terminating..." << endl;
            }
        }
    }

    if (!loginSuccessful)
    {
        exit(1); // Terminate the program
    }
}

void PlanetaryDefense(){
    cout << "Initiating planetary defense protocols..." << endl;
    this_thread::sleep_for(chrono::seconds(1));

    cout << "Activating shields and weapons systems." << endl;
    this_thread::sleep_for(chrono::seconds(2));

    cout << "Scanning for potential threats..." << endl;
    this_thread::sleep_for(chrono::seconds(1));

    cout << "Threats detected. Engaging defense systems." << endl;
    this_thread::sleep_for(chrono::seconds(2));

    cout << "Defense systems engaged. All systems operational." << endl;
    this_thread::sleep_for(chrono::seconds(1));

    cout << "Planetary defense system is now active." << endl;
    this_thread::sleep_for(chrono::seconds(2));

    cout << "Captain Kirk, your orders have been executed successfully." << endl;
}

void Planet_logs(){
    int choice;
    cout << "\n=== Planet Logs Management ===" << endl;
    cout << "1. Add new planet" << endl;
    cout << "2. View all planets" << endl;
    cout << "3. Delete a planet" << endl;
    cout << "4. Search/Filter planets" << endl;
    cout << "Enter your choice: ";
    cin >> choice;
    
    switch(choice) {
        case 1: {
            // Add new planet
            cin.ignore(); // Clear the input buffer
            Planet X;
            
            cout << "\n--- Adding New Planet ---" << endl;
            cout << "Enter the name of the planet: ";
            getline(cin, X.name);
            
            cout << "Enter the description of the planet: ";
            getline(cin, X.description);
            
            cout << "Enter the population of the planet: ";
            cin >> X.population;
            
            cout << "Enter the defense level of the planet: ";
            cin >> X.defenseLevel;

            // Save to file
            ofstream file("planets.txt", ios::app);
            
            if (file.is_open()) {
                file << "Planet Name: " << X.name << endl;
                file << "Description: " << X.description << endl;
                file << "Population: " << X.population << endl;
                file << "Defense Level: " << X.defenseLevel << endl;
                file << "------------------------" << endl;
                file.close();
                
                cout << "Planet added successfully and saved to file!" << endl;
            } else {
                cout << "Error: Could not save to file." << endl;
            }
            break;
        }
        
        case 2: {
            // View all planets
            cout << "\n--- Planet Logs ---" << endl;
            ifstream file("planets.txt");
            
            if (file.is_open()) {
                string line;
                if (file.peek() == ifstream::traits_type::eof()) {
                    cout << "No planets in the logs yet." << endl;
                } else {
                    while (getline(file, line)) {
                        cout << line << endl;
                    }
                }
                file.close();
            } else {
                cout << "Error: Could not open file or no planets recorded yet." << endl;
            }
            break;
        }
        
        case 3: {
            // Delete a planet
            cout << "\n--- Delete Planet ---" << endl;
            cin.ignore(); // Clear input buffer
            string planetToDelete;
            cout << "Enter the name of the planet to delete: ";
            getline(cin, planetToDelete);
            
            ifstream inputFile("planets.txt");
            ofstream tempFile("temp.txt");
            
            if (!inputFile.is_open()) {
                cout << "Error: Could not open planets file." << endl;
                break;
            }
            
            string line;
            bool planetFound = false;
            bool skipNext = false;
            int skipCount = 0;
            
            while (getline(inputFile, line)) {
                if (line.find("Planet Name: " + planetToDelete) != string::npos) {
                    planetFound = true;
                    skipNext = true;
                    skipCount = 4; // Skip this line and next 4 lines (description, population, defense, separator)
                    continue;
                }
                
                if (skipNext && skipCount > 0) {
                    skipCount--;
                    continue;
                } else {
                    skipNext = false;
                }
                
                tempFile << line << endl;
            }
            
            inputFile.close();
            tempFile.close();
            
            if (planetFound) {
                remove("planets.txt");
                rename("temp.txt", "planets.txt");
                cout << "Planet '" << planetToDelete << "' deleted successfully!" << endl;
            } else {
                remove("temp.txt");
                cout << "Planet '" << planetToDelete << "' not found in the logs." << endl;
            }
            break;
        }
        
        case 4: {
            // Search/Filter planets
            cout << "\n=== Planet Search & Filter ===" << endl;
            cout << "1. Search by planet name" << endl;
            cout << "2. Filter by population range" << endl;
            cout << "3. Filter by defense level range" << endl;
            cout << "Enter search type: ";
            
            int searchChoice;
            cin >> searchChoice;
            
            ifstream file("planets.txt");
            if (!file.is_open()) {
                cout << "Error: Could not open planets file." << endl;
                break;
            }
            
            string line;
            bool found = false;
            
            switch(searchChoice) {
                case 1: {
                    // Search by name
                    cin.ignore();
                    string searchName;
                    cout << "Enter planet name to search: ";
                    getline(cin, searchName);
                    
                    cout << "\n--- Search Results ---" << endl;
                    while(getline(file, line)) {
                        if(line.find("Planet Name: " + searchName) != string::npos) {
                            found = true;
                            cout << line << endl;
                            // Display next 4 lines (description, population, defense, separator)
                            for(int i = 0; i < 4; i++) {
                                if(getline(file, line)) {
                                    cout << line << endl;
                                }
                            }
                        }
                    }
                    if(!found) {
                        cout << "No planet found with name: " << searchName << endl;
                    }
                    break;
                }
                
                case 2: {
                    // Filter by population
                    int minPop, maxPop;
                    cout << "Enter minimum population: ";
                    cin >> minPop;
                    cout << "Enter maximum population: ";
                    cin >> maxPop;
                    
                    cout << "\n--- Planets with population between " << minPop << " and " << maxPop << " ---" << endl;
                    
                    string planetName, description, popLine, defLine, separator;
                    while(getline(file, planetName) && 
                          getline(file, description) && 
                          getline(file, popLine) && 
                          getline(file, defLine) && 
                          getline(file, separator)) {
                        
                        // Extract population number from "Population: 12345"
                        size_t pos = popLine.find(": ");
                        if(pos != string::npos) {
                            int population = stoi(popLine.substr(pos + 2));
                            if(population >= minPop && population <= maxPop) {
                                found = true;
                                cout << planetName << endl;
                                cout << description << endl;
                                cout << popLine << endl;
                                cout << defLine << endl;
                                cout << separator << endl;
                            }
                        }
                    }
                    if(!found) {
                        cout << "No planets found in that population range." << endl;
                    }
                    break;
                }
                
                case 3: {
                    // Filter by defense level
                    double minDef, maxDef;
                    cout << "Enter minimum defense level: ";
                    cin >> minDef;
                    cout << "Enter maximum defense level: ";
                    cin >> maxDef;
                    
                    cout << "\n--- Planets with defense level between " << minDef << " and " << maxDef << " ---" << endl;
                    
                    string planetName, description, popLine, defLine, separator;
                    while(getline(file, planetName) && 
                          getline(file, description) && 
                          getline(file, popLine) && 
                          getline(file, defLine) && 
                          getline(file, separator)) {
                        
                        // Extract defense level from "Defense Level: 7.5"
                        size_t pos = defLine.find(": ");
                        if(pos != string::npos) {
                            double defenseLevel = stod(defLine.substr(pos + 2));
                            if(defenseLevel >= minDef && defenseLevel <= maxDef) {
                                found = true;
                                cout << planetName << endl;
                                cout << description << endl;
                                cout << popLine << endl;
                                cout << defLine << endl;
                                cout << separator << endl;
                            }
                        }
                    }
                    if(!found) {
                        cout << "No planets found in that defense level range." << endl;
                    }
                    break;
                }
                
                default:
                    cout << "Invalid search option." << endl;
                    break;
            }
            
            file.close();
            break;
        }
        
        default:
            cout << "Invalid choice. Returning to main menu." << endl;
            break;
    }
}

void ShipHealthCheck() {
    cout << "Performing ship health check..." << endl;
    this_thread::sleep_for(chrono::seconds(1));
    
    cout << "Ship systems are operational." << endl;
    this_thread::sleep_for(chrono::seconds(1));
    
    cout << "All systems green. Ready for next mission." << endl;
}

void StarMapNavigation() {
    cout << "\n=== Star Map Navigation System ===" << endl;
    this_thread::sleep_for(chrono::seconds(1));
    
    cout << "Initializing star map..." << endl;
    this_thread::sleep_for(chrono::seconds(1));
    
    // Display the star map
    cout << "\n--- Current Sector Map ---" << endl;
    cout << "    A   B   C   D   E" << endl;
    cout << "1  [*] [ ] [P] [ ] [S]" << endl;
    cout << "2  [ ] [K] [ ] [R] [ ]" << endl;
    cout << "3  [E] [ ] [*] [ ] [P]" << endl;
    cout << "4  [ ] [P] [ ] [*] [ ]" << endl;
    cout << "5  [S] [ ] [ ] [ ] [E]" << endl;
    
    cout << "\nLegend:" << endl;
    cout << "[E] = Enterprise (Your ship)" << endl;
    cout << "[P] = Friendly Planet" << endl;
    cout << "[S] = Star/Sun" << endl;
    cout << "[K] = Klingon Ship" << endl;
    cout << "[R] = Romulan Ship" << endl;
    cout << "[*] = Unexplored Space" << endl;
    cout << "[ ] = Empty Space" << endl;
    
    int navChoice;
    cout << "\nNavigation Options:" << endl;
    cout << "1. Set course to coordinates" << endl;
    cout << "2. Scan nearby sectors" << endl;
    cout << "3. Return to bridge" << endl;
    cout << "Enter your choice: ";
    cin >> navChoice;
    
    switch(navChoice) {
        case 1: {
            cout << "\n--- Set Course ---" << endl;
            char column;
            int row;
            cout << "Enter target coordinates (e.g., A1, B3, E5): ";
            cin >> column >> row;
            
            cout << "Setting course to " << column << row << "..." << endl;
            this_thread::sleep_for(chrono::seconds(1));
            cout << "Engaging warp drive..." << endl;
            this_thread::sleep_for(chrono::seconds(2));
            cout << "Course laid in, Captain. Arriving at " << column << row << endl;
            
            // Simple coordinate validation
            if ((column >= 'A' && column <= 'E') && (row >= 1 && row <= 5)) {
                cout << "Navigation successful!" << endl;
            } else {
                cout << "Warning: Coordinates out of range!" << endl;
            }
            break;
        }
        
        case 2: {
            cout << "\n--- Sensor Scan ---" << endl;
            cout << "Scanning surrounding sectors..." << endl;
            this_thread::sleep_for(chrono::seconds(2));
            
            cout << "Scan results:" << endl;
            cout << "- 3 Friendly planets detected" << endl;
            cout << "- 1 Klingon vessel in sector B2" << endl;
            cout << "- 1 Romulan ship in sector D2" << endl;
            cout << "- 2 Stars providing energy sources" << endl;
            cout << "- 3 Unexplored regions available" << endl;
            break;
        }
        
        case 3:
            cout << "Returning to bridge..." << endl;
            break;
            
        default:
            cout << "Invalid navigation command." << endl;
            break;
    }
}

void WarpDriveCalculator() {
    cout << "\n=== Warp Drive Calculator ===" << endl;
    this_thread::sleep_for(chrono::seconds(1));
    
    cout << "Initializing warp drive calculations..." << endl;
    this_thread::sleep_for(chrono::seconds(1));
    
    int calcChoice;
    cout << "\nWarp Drive Options:" << endl;
    cout << "1. Calculate travel time between coordinates" << endl;
    cout << "2. Calculate fuel consumption" << endl;
    cout << "3. Optimal route planning" << endl;
    cout << "4. Return to bridge" << endl;
    cout << "Enter your choice: ";
    cin >> calcChoice;
    
    switch(calcChoice) {
        case 1: {
            cout << "\n--- Travel Time Calculator ---" << endl;
            char startCol, endCol;
            int startRow, endRow;
            
            cout << "Enter starting coordinates (e.g., A1): ";
            cin >> startCol >> startRow;
            cout << "Enter destination coordinates (e.g., E5): ";
            cin >> endCol >> endRow;
            
            // Calculate distance using coordinate difference
            int colDiff = abs(endCol - startCol);
            int rowDiff = abs(endRow - startRow);
            double distance = sqrt(colDiff * colDiff + rowDiff * rowDiff);
            
            cout << "\nCalculating route..." << endl;
            this_thread::sleep_for(chrono::seconds(1));
            
            cout << "Distance: " << distance << " light years" << endl;
            
            // Calculate time at different warp speeds
            cout << "\nTravel times at different warp speeds:" << endl;
            cout << "Warp 1: " << (distance * 24) << " hours" << endl;
            cout << "Warp 2: " << (distance * 12) << " hours" << endl;
            cout << "Warp 5: " << (distance * 4.8) << " hours" << endl;
            cout << "Warp 9: " << (distance * 2.7) << " hours" << endl;
            
            break;
        }
        
        case 2: {
            cout << "\n--- Fuel Consumption Calculator ---" << endl;
            double distance, warpSpeed;
            
            cout << "Enter distance in light years: ";
            cin >> distance;
            cout << "Enter warp speed (1-9): ";
            cin >> warpSpeed;
            
            cout << "\nCalculating fuel requirements..." << endl;
            this_thread::sleep_for(chrono::seconds(1));
            
            // Fuel consumption increases exponentially with warp speed
            double fuelConsumption = distance * (warpSpeed * warpSpeed * 0.5);
            double dilithiumNeeded = fuelConsumption * 0.1;
            
            cout << "Fuel consumption: " << fuelConsumption << " units" << endl;
            cout << "Dilithium crystals needed: " << dilithiumNeeded << " kg" << endl;
            
            if (warpSpeed > 6) {
                cout << "WARNING: High warp speed detected!" << endl;
                cout << "Recommend reducing speed to conserve fuel." << endl;
            }
            
            break;
        }
        
        case 3: {
            cout << "\n--- Optimal Route Planning ---" << endl;
            cout << "Analyzing current sector for optimal routes..." << endl;
            this_thread::sleep_for(chrono::seconds(2));
            
            cout << "\nRecommended routes:" << endl;
            cout << "1. Shortest distance: A1 -> C3 -> E5" << endl;
            cout << "2. Safest route: A1 -> A5 -> E5 (avoiding hostile sectors)" << endl;
            cout << "3. Fuel efficient: A1 -> B2 -> D4 -> E5 (slower but conserves fuel)" << endl;
            
            cout << "\nCurrent fuel level: 85%" << endl;
            cout << "Recommended: Route 2 (Safest) at Warp 5" << endl;
            
            break;
        }
        
        case 4:
            cout << "Returning to bridge..." << endl;
            break;
            
        default:
            cout << "Invalid option." << endl;
            break;
    }
}

void RandomPlanetDiscovery() {
    cout << "\n=== Planet Discovery Mission ===" << endl;
    this_thread::sleep_for(chrono::seconds(1));
    
    cout << "Initiating deep space scanning..." << endl;
    this_thread::sleep_for(chrono::seconds(2));
    
    int discoveryChoice;
    cout << "\nDiscovery Options:" << endl;
    cout << "1. Scan for new planets" << endl;
    cout << "2. Generate random planet" << endl;
    cout << "3. Discovery mission report" << endl;
    cout << "4. Return to bridge" << endl;
    cout << "Enter your choice: ";
    cin >> discoveryChoice;
    
    // Seed random number generator
    srand(time(0));
    
    switch(discoveryChoice) {
        case 1: {
            cout << "\n--- Deep Space Scan ---" << endl;
            cout << "Scanning unknown sectors..." << endl;
            this_thread::sleep_for(chrono::seconds(3));
            
            int planetsFound = rand() % 4 + 1; // 1-4 planets
            cout << "Scan complete! " << planetsFound << " potentially habitable planets detected!" << endl;
            
            for(int i = 1; i <= planetsFound; i++) {
                cout << "\nPlanet " << i << " detected at coordinates " 
                     << char('A' + rand() % 5) << (rand() % 5 + 1) << endl;
                this_thread::sleep_for(chrono::seconds(1));
            }
            
            cout << "\nWould you like to investigate these planets? (y/n): ";
            char investigate;
            cin >> investigate;
            
            if(investigate == 'y' || investigate == 'Y') {
                cout << "Dispatching exploration teams..." << endl;
                this_thread::sleep_for(chrono::seconds(2));
                cout << "Detailed analysis will be available shortly." << endl;
            }
            break;
        }
        
        case 2: {
            cout << "\n--- Random Planet Generator ---" << endl;
            cout << "Discovering new planet..." << endl;
            this_thread::sleep_for(chrono::seconds(2));
            
            // Arrays of random planet names and descriptions
            string planetNames[] = {
                "Kepler-442b", "Proxima Centauri b", "TRAPPIST-1e", "Gliese 667Cc",
                "HD 40307g", "Kepler-186f", "Wolf 1061c", "Ross 128b",
                "LHS 1140b", "TOI-715b"
            };
            
            string planetTypes[] = {
                "Rocky terrestrial world", "Gas giant with rings", "Desert planet",
                "Ocean world", "Ice planet", "Volcanic world", "Forest planet",
                "Crystal planet", "Storm-covered planet", "Binary planet system"
            };
            
            string descriptions[] = {
                "with abundant water sources", "showing signs of ancient civilization",
                "rich in rare minerals", "with unusual magnetic properties",
                "harboring unique life forms", "with extreme weather patterns",
                "containing valuable energy crystals", "perfect for colonization",
                "with mysterious alien structures", "ideal for scientific research"
            };
            
            // Generate random planet
            Planet newPlanet;
            newPlanet.name = planetNames[rand() % 10];
            newPlanet.description = planetTypes[rand() % 10] + " " + descriptions[rand() % 10];
            newPlanet.population = rand() % 10000000 + 100000; // 100K to 10M
            newPlanet.defenseLevel = (rand() % 100) / 10.0; // 0.0 to 9.9
            
            cout << "\n=== NEW PLANET DISCOVERED ===" << endl;
            cout << "Planet Name: " << newPlanet.name << endl;
            cout << "Description: " << newPlanet.description << endl;
            cout << "Population: " << newPlanet.population << endl;
            cout << "Defense Level: " << newPlanet.defenseLevel << endl;
            
            cout << "\nWould you like to add this planet to your logs? (y/n): ";
            char addToLogs;
            cin >> addToLogs;
            
            if(addToLogs == 'y' || addToLogs == 'Y') {
                // Save to file
                ofstream file("planets.txt", ios::app);
                
                if (file.is_open()) {
                    file << "Planet Name: " << newPlanet.name << endl;
                    file << "Description: " << newPlanet.description << endl;
                    file << "Population: " << newPlanet.population << endl;
                    file << "Defense Level: " << newPlanet.defenseLevel << endl;
                    file << "------------------------" << endl;
                    file.close();
                    
                    cout << "Planet added to your discovery logs!" << endl;
                } else {
                    cout << "Error: Could not save to logs." << endl;
                }
            }
            break;
        }
        
        case 3: {
            cout << "\n--- Discovery Mission Report ---" << endl;
            cout << "Generating mission statistics..." << endl;
            this_thread::sleep_for(chrono::seconds(2));
            
            // Count planets in file
            ifstream file("planets.txt");
            int planetCount = 0;
            string line;
            
            if (file.is_open()) {
                while(getline(file, line)) {
                    if(line.find("Planet Name:") != string::npos) {
                        planetCount++;
                    }
                }
                file.close();
            }
            
            cout << "\n=== MISSION STATISTICS ===" << endl;
            cout << "Total planets discovered: " << planetCount << endl;
            cout << "Exploration sectors covered: " << (planetCount * 2 + 5) << endl;
            cout << "Scientific value: " << (planetCount * 150 + 500) << " credits" << endl;
            cout << "Mission efficiency: " << (planetCount > 5 ? "Excellent" : "Good") << endl;
            
            if(planetCount >= 10) {
                cout << "\n*** ACHIEVEMENT UNLOCKED: Master Explorer! ***" << endl;
            } else if(planetCount >= 5) {
                cout << "\n*** ACHIEVEMENT UNLOCKED: Space Pioneer! ***" << endl;
            }
            break;
        }
        
        case 4:
            cout << "Returning to bridge..." << endl;
            break;
            
        default:
            cout << "Invalid option." << endl;
            break;
    }
}

void ThreatAssessment() {
    cout << "\n=== Threat Assessment & Battle Simulator ===" << endl;
    this_thread::sleep_for(chrono::seconds(1));
    
    cout << "Scanning for hostile vessels..." << endl;
    this_thread::sleep_for(chrono::seconds(2));
    
    int threatChoice;
    cout << "\nThreat Assessment Options:" << endl;
    cout << "1. Scan for enemy ships" << endl;
    cout << "2. Engage in battle simulation" << endl;
    cout << "3. Emergency protocols" << endl;
    cout << "4. Return to bridge" << endl;
    cout << "Enter your choice: ";
    cin >> threatChoice;
    
    // Seed random number generator
    srand(time(0));
    
    switch(threatChoice) {
        case 1: {
            cout << "\n--- Enemy Detection Scan ---" << endl;
            cout << "Long range sensors active..." << endl;
            this_thread::sleep_for(chrono::seconds(2));
            
            string enemies[] = {"Klingon Bird of Prey", "Romulan Warbird", "Borg Cube", "Gorn Vessel", "Orion Pirate Ship"};
            int enemyCount = rand() % 3 + 1; // 1-3 enemies
            
            if(enemyCount == 0) {
                cout << "No hostile vessels detected. All clear, Captain." << endl;
            } else {
                cout << "WARNING: " << enemyCount << " hostile vessel(s) detected!" << endl;
                for(int i = 0; i < enemyCount; i++) {
                    cout << "- " << enemies[rand() % 5] << " at sector " 
                         << char('A' + rand() % 5) << (rand() % 5 + 1) << endl;
                    this_thread::sleep_for(chrono::seconds(1));
                }
                cout << "\nRecommendation: Raise shields and prepare for combat!" << endl;
            }
            break;
        }
        
        case 2: {
            cout << "\n--- Battle Simulation ---" << endl;
            string enemy = "Klingon Bird of Prey";
            int enterpriseHealth = 100;
            int enemyHealth = 80;
            int shieldLevel = 100;
            
            cout << "Engaging " << enemy << " in combat simulation..." << endl;
            this_thread::sleep_for(chrono::seconds(1));
            
            while(enterpriseHealth > 0 && enemyHealth > 0) {
                cout << "\n--- Battle Status ---" << endl;
                cout << "Enterprise Hull: " << enterpriseHealth << "%" << endl;
                cout << "Shield Level: " << shieldLevel << "%" << endl;
                cout << "Enemy Hull: " << enemyHealth << "%" << endl;
                
                cout << "\nChoose your action:" << endl;
                cout << "1. Fire phasers" << endl;
                cout << "2. Fire photon torpedoes" << endl;
                cout << "3. Raise shields" << endl;
                cout << "4. Attempt to retreat" << endl;
                
                int battleChoice;
                cin >> battleChoice;
                
                int damage = 0;
                switch(battleChoice) {
                    case 1:
                        damage = rand() % 20 + 10; // 10-30 damage
                        cout << "Phasers fired! Enemy takes " << damage << " damage!" << endl;
                        enemyHealth -= damage;
                        break;
                    case 2:
                        damage = rand() % 30 + 20; // 20-50 damage
                        cout << "Photon torpedoes launched! Critical hit for " << damage << " damage!" << endl;
                        enemyHealth -= damage;
                        break;
                    case 3:
                        shieldLevel = min(100, shieldLevel + 20);
                        cout << "Shields reinforced! Shield level now " << shieldLevel << "%" << endl;
                        break;
                    case 4:
                        cout << "Attempting tactical retreat..." << endl;
                        if(rand() % 2) {
                            cout << "Retreat successful! Warp drive engaged!" << endl;
                            return;
                        } else {
                            cout << "Retreat failed! Enemy blocks our escape!" << endl;
                        }
                        break;
                }
                
                if(enemyHealth <= 0) {
                    cout << "\n*** VICTORY! Enemy vessel destroyed! ***" << endl;
                    cout << "Excellent tactical decisions, Captain!" << endl;
                    break;
                }
                
                // Enemy attacks
                int enemyDamage = rand() % 25 + 5; // 5-30 damage
                if(shieldLevel > 0) {
                    int shieldAbsorb = min(shieldLevel, enemyDamage);
                    shieldLevel -= shieldAbsorb;
                    enemyDamage -= shieldAbsorb;
                    cout << "Shields absorb " << shieldAbsorb << " damage!" << endl;
                }
                
                if(enemyDamage > 0) {
                    enterpriseHealth -= enemyDamage;
                    cout << "Enterprise takes " << enemyDamage << " hull damage!" << endl;
                }
                
                this_thread::sleep_for(chrono::seconds(2));
            }
            
            if(enterpriseHealth <= 0) {
                cout << "\n*** DEFEAT! Enterprise critically damaged! ***" << endl;
                cout << "Emergency evacuation protocols initiated!" << endl;
            }
            break;
        }
        
        case 3: {
            cout << "\n--- Emergency Protocols ---" << endl;
            cout << "*** RED ALERT! RED ALERT! ***" << endl;
            this_thread::sleep_for(chrono::seconds(1));
            
            cout << "All hands to battle stations!" << endl;
            cout << "- Shields raised to maximum" << endl;
            cout << "- Weapons systems armed" << endl;
            cout << "- Emergency power activated" << endl;
            cout << "- Damage control teams standing by" << endl;
            this_thread::sleep_for(chrono::seconds(2));
            
            cout << "\nEmergency protocols activated, Captain!" << endl;
            break;
        }
        
        case 4:
            cout << "Returning to bridge..." << endl;
            break;
            
        default:
            cout << "Invalid option." << endl;
            break;
    }
}

struct CrewMember {
    string name;
    string position;
    int health;
    int experience;
    string specialty;
};

void CrewManagement() {
    cout << "\n=== Crew Management & Mission Assignments ===" << endl;
    this_thread::sleep_for(chrono::seconds(1));
    
    // Initialize crew
    CrewMember crew[6] = {
        {"Spock", "Science Officer", 95, 90, "Logic & Analysis"},
        {"McCoy", "Chief Medical Officer", 88, 85, "Medical & Biology"},
        {"Scotty", "Chief Engineer", 92, 95, "Engineering & Repairs"},
        {"Uhura", "Communications Officer", 90, 80, "Languages & Diplomacy"},
        {"Sulu", "Helmsman", 89, 75, "Navigation & Piloting"},
        {"Chekov", "Navigator", 85, 70, "Tactical & Weapons"}
    };
    
    int crewChoice;
    cout << "\nCrew Management Options:" << endl;
    cout << "1. View crew roster" << endl;
    cout << "2. Assign away team mission" << endl;
    cout << "3. Crew performance review" << endl;
    cout << "4. Emergency crew assignments" << endl;
    cout << "5. Return to bridge" << endl;
    cout << "Enter your choice: ";
    cin >> crewChoice;
    
    switch(crewChoice) {
        case 1: {
            cout << "\n--- Current Crew Roster ---" << endl;
            cout << "========================================" << endl;
            for(int i = 0; i < 6; i++) {
                cout << crew[i].name << " - " << crew[i].position << endl;
                cout << "Health: " << crew[i].health << "% | Experience: " << crew[i].experience << "%" << endl;
                cout << "Specialty: " << crew[i].specialty << endl;
                cout << "----------------------------------------" << endl;
            }
            break;
        }
        
        case 2: {
            cout << "\n--- Away Team Mission Assignment ---" << endl;
            cout << "Mission briefing: Investigate unknown alien structure on planet surface." << endl;
            cout << "\nSelect crew members for away team (choose 3):" << endl;
            
            for(int i = 0; i < 6; i++) {
                cout << (i+1) << ". " << crew[i].name << " (" << crew[i].specialty << ")" << endl;
            }
            
            int selections[3];
            cout << "\nEnter 3 crew member numbers: ";
            for(int i = 0; i < 3; i++) {
                cin >> selections[i];
                selections[i]--; // Convert to array index
            }
            
            cout << "\n--- Away Team Selected ---" << endl;
            for(int i = 0; i < 3; i++) {
                if(selections[i] >= 0 && selections[i] < 6) {
                    cout << crew[selections[i]].name << " - " << crew[selections[i]].specialty << endl;
                }
            }
            
            cout << "\nTransporting away team to planet surface..." << endl;
            this_thread::sleep_for(chrono::seconds(2));
            
            // Mission outcome based on crew selection
            bool hasScience = false, hasMedical = false, hasEngineering = false;
            for(int i = 0; i < 3; i++) {
                if(selections[i] == 0) hasScience = true;    // Spock
                if(selections[i] == 1) hasMedical = true;    // McCoy
                if(selections[i] == 2) hasEngineering = true; // Scotty
            }
            
            cout << "\n--- Mission Results ---" << endl;
            if(hasScience && hasEngineering) {
                cout << "MISSION SUCCESS! The team successfully analyzed the alien technology!" << endl;
                cout << "Spock's analysis and Scotty's engineering skills proved invaluable!" << endl;
            } else if(hasScience) {
                cout << "Partial success. Spock gathered valuable scientific data." << endl;
            } else if(hasEngineering) {
                cout << "Partial success. Scotty managed to interface with alien systems." << endl;
            } else {
                cout << "Mission encountered difficulties. Recommend including science officer next time." << endl;
            }
            break;
        }
        
        case 3: {
            cout << "\n--- Crew Performance Review ---" << endl;
            
            for(int i = 0; i < 6; i++) {
                cout << "\n" << crew[i].name << " - Performance Analysis:" << endl;
                
                if(crew[i].name == "Spock") {
                    cout << "Logical analysis: Exceptional" << endl;
                    cout << "Problem solving: Outstanding" << endl;
                    cout << "Recommendation: Continue current duties" << endl;
                } else if(crew[i].name == "McCoy") {
                    cout << "Medical expertise: Excellent" << endl;
                    cout << "Crew morale support: High" << endl;
                    cout << "Recommendation: Consider xenobiology training" << endl;
                } else if(crew[i].name == "Scotty") {
                    cout << "Engineering efficiency: Miraculous" << endl;
                    cout << "Emergency repairs: Legendary" << endl;
                    cout << "Recommendation: Promote to Senior Engineer" << endl;
                } else {
                    cout << "Performance: " << (crew[i].experience > 80 ? "Excellent" : "Good") << endl;
                    cout << "Recommendation: Continue professional development" << endl;
                }
            }
            break;
        }
        
        case 4: {
            cout << "\n--- Emergency Crew Assignments ---" << endl;
            cout << "*** EMERGENCY SITUATION DETECTED ***" << endl;
            this_thread::sleep_for(chrono::seconds(1));
            
            string emergencies[] = {
                "Warp core breach imminent!",
                "Alien virus detected in sickbay!",
                "Unknown ship requesting assistance!",
                "Hostile boarding party detected!"
            };
            
            string emergency = emergencies[rand() % 4];
            cout << emergency << endl;
            
            cout << "\nAutomatic crew assignments:" << endl;
            if(emergency.find("Warp core") != string::npos) {
                cout << "Scotty - Emergency engineering repairs" << endl;
                cout << "Spock - Technical analysis and solutions" << endl;
            } else if(emergency.find("virus") != string::npos) {
                cout << "McCoy - Medical emergency response" << endl;
                cout << "Spock - Scientific analysis of pathogen" << endl;
            } else if(emergency.find("assistance") != string::npos) {
                cout << "Uhura - Establish communications" << endl;
                cout << "Spock - Diplomatic consultation" << endl;
            } else {
                cout << "Chekov - Security and tactical response" << endl;
                cout << "Sulu - Defensive maneuvers" << endl;
            }
            
            cout << "\nCrew assignments completed. Emergency response initiated!" << endl;
            break;
        }
        
        case 5:
            cout << "Returning to bridge..." << endl;
            break;
            
        default:
            cout << "Invalid option." << endl;
            break;
    }
}

int main(){
    Greeting();
    Login();
    int choice;
    
    do {
        cout << "\nHow would you like to proceed, Captain Kirk?" << endl;
        cout << "1. Activate planetary defense system" << endl;
        cout << "2. Manage planet logs" << endl;
        cout << "3. Perform ship health check" << endl;
        cout << "4. Star map navigation" << endl;
        cout << "5. Warp drive calculator" << endl;
        cout << "6. Random planet discovery" << endl;
        cout << "7. Threat assessment & battle simulator" << endl;
        cout << "8. Crew management & mission assignments" << endl;
        cout << "9. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            PlanetaryDefense();
            break;
        case 2:
            Planet_logs();
            break;
        case 3:
            ShipHealthCheck();
            break;
        case 4:
            StarMapNavigation();
            break;
        case 5:
            WarpDriveCalculator();
            break;
        case 6:
            RandomPlanetDiscovery();
            break;
        case 7:
            ThreatAssessment();
            break;
        case 8:
            CrewManagement();
            break;
        case 9:
            cout << "\n*** Mission Complete ***" << endl;
            cout << "Thank you for commanding the USS Enterprise, Captain Kirk!" << endl;
            cout << "Live long and prosper! 🖖" << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
        }
    } while(choice != 9);

    cout << "\nProgram ended. Press Enter to close terminal..." << endl;
    cin.ignore();
    cin.get();
    return 0;
}
