#include <stdio.h>
#include <string>
#include <bits/stdc++.h>
#include <jsoncpp/json/value.h>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <jsoncpp/json/json.h>

using namespace std;
int fps = 0, startnm = 0;
string imgname = "", filename = "", imgfilenm = "", command = "";
string cconfig = "-cconf", guide = "-custom", help = "-help", json = "-json";
string aarg[] = {};
char a;

int main(int argc, char* argv[])
{
    if(argc == 1)
    {
        cout << "For help use with " + (string)argv[0] + " -help" << endl;
    }
    else if(argc == 2 && argv[1] == help)
    {
        //printing out help
        cout << "\033[1;31m<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<---------------------------------------->>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\033[0m" << endl;
        cout << "\033[1;34mUse " + (string)argv[0] + " -help for help\033[0m" << endl;
        cout << "\033[1;34mUse " + (string)argv[0] + " -cconf to generate config.json file which you can later edit.\033[0m" << endl;
        cout << "\033[1;34mUse " + (string)argv[0] + " -custom to generate video file with description to each step.\033[0m" << endl;
        cout << "\033[1;34mUse " + (string)argv[0] + " -json <ConfigFileName.json> to generate video file with saved preset in config.json file.\033[0m" << endl;
        cout << "\033[1;31m<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<---------------------------------------->>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\033[0m" << endl;
    }
    else if(argc == 2 && argv[1] == guide)
    {
        //get the data from the user when there are no arguments
        cout << "\033[1;36mZadejte počet fps: \033[0m";
        cin >> fps;
        cout << endl << "\033[1;36mZadejte číslo prvního obrázku: \033[0m";
        cin >> startnm;
        cout << endl << "\033[1;36mZadejte název obrázku bez čísla: \033[0m";
        cin >> imgname;
        cout << endl << "\033[1;36mZadejte příponu obrázku: \033[0m";
        cin >> imgfilenm;
        cout << endl << "\033[1;36mZadejte název výstupního videa: \033[0m";
        cin >> filename;
        cout << endl;

        if(fps != 0 && startnm != 0 && imgname != "" && filename != "")
        {
            //assembling command to combine photos, uses ffmpeg
            command = "ffmpeg -framerate " + to_string(fps) + " -start_number " + to_string(startnm) + " -i " + imgname + "%d." + imgfilenm + " -vcodec mpeg4 " + filename + ".avi";
            system(command.c_str());
            cout << endl << "\033[1;31m####################\033[0m" << endl << "\033[1;33mVideo exportováno s těmito parametry:\033[0m" << endl << "\033[1;35m" + to_string(fps) + " FPS\033[0m" << endl << "\033[1;32mJméno prvního obrázku: " + imgname + to_string(startnm) + "." + imgfilenm + "\033[0m" << endl << "\033[1;34mVideo exportováno jako: " + filename + ".avi\033[0m" << endl << "\033[1;31m####################\033[0m" << endl;
        }
        else
        {
            cout << endl << "\033[1;31m####################\033[0m" << endl << "Nebyly vyplněny všechny parametry" << endl << "\033[1;31m####################\033[0m" << endl;
        }
    }
    else if(argc == 2 && argv[1] == cconfig)
    {
        //create basic config file
        ofstream
            BasicConfig("config.json");
            BasicConfig << "{\n";
            BasicConfig << "\"fps\":10,\n";
            BasicConfig << "\"StartingNumber\":1234,\n";
            BasicConfig << "\"ImageName\":\"<name>\",\n";
            BasicConfig << "\"ImageFileExtension\":\"<extension>\",\n";
            BasicConfig << "\"NameOfVideoFile\":\"<name>\"\n";
            BasicConfig << "}";
            BasicConfig.close();
        cout << "\033[1;33mSoubor byl uložen jako config.json.\033[0m" << endl;
    }
    else if(argc == 3 && argv[1] == json)
    {
        ifstream tryfile;
        tryfile.open(argv[2]);

        if(tryfile)
        {
            ifstream ifs(argv[2]);
            Json::Reader reader;
            Json::Value obj;

            reader.parse(ifs, obj);

            fps = obj["fps"].asInt();
            startnm = obj["StartingNumber"].asInt();
            imgname = obj["ImageName"].asString() ;
            imgfilenm = obj["ImageFileExtension"].asString();
            filename = obj["NameOfVideoFile"].asString();

            cout << "\033[1;31m<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<------------------------------------------------------->>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\033[0m" << endl;
            cout << "\033[1;34mFotografie budou zpracovány s následující konfigurací: \033[0m" << endl;
            cout << "\033[1;34mfps: " + to_string(fps) + "\033[1;34m"<< endl;
            cout << "\033[1;34mKompletní název první fotografie: " << imgname + to_string(startnm) + "." + imgfilenm + "\033[1;34m" << endl;
            cout << "\033[1;34mVideo bude exportováno jako: " << filename + ".avi\033[0m" << endl;
            cout << "\033[1;34mPokud jsou tyto parametry správné, zadejte y a stiskněte enter, pokud ne, přerušte tento program stisknutím Ctrl+C.\033[0m" << endl;
            cout << "\033[1;31m<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<------------------------------------------------------->>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\033[0m" << endl;
            cin >> a;

            if((a == 'y' || a == 'Y') && fps != 0 && startnm != 0 && imgname != "" && filename != "")
            {
                command = "ffmpeg -framerate " + to_string(fps) + " -start_number " + to_string(startnm) + " -i " + imgname + "%d." + imgfilenm + " -vcodec mpeg4 " + filename + ".avi";
                system(command.c_str());
                cout << endl << "\033[1;31m################################################################################\033[0m" << endl << "\033[1;33mVideo exportováno s těmito parametry:\033[0m" << endl << "\033[1;35m" + to_string(fps) + " FPS\033[0m" << endl << "\033[1;32mJméno prvního obrázku: " + imgname + to_string(startnm) + "." + imgfilenm + "\033[0m" << endl << "\033[1;34mVideo exportováno jako: " + filename + ".avi\033[0m" << endl << "\033[1;31m################################################################################\033[0m" << endl;
            }
            else
            {
                cout << endl << "\033[1;31m################################################################################\033[0m" << endl << "\033[31mNebyly vyplněny všechny parametry a nebo jste nepotvrdili konfiguraci.\033[0m" << endl << "\033[1;31m################################################################################\033[0m" << endl;
            }

        }

        else
        {
            cout << "\033[1;31mConfiguration file " + (string)argv[2] + " was not found\033[0m" << endl;
        }
    }
}